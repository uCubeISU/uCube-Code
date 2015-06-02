/*
 *     uCube is a motion controlled interactive LED cube.
 *     Copyright (C) 2014  Jeramie Vens
 *
 *     This program is free software: you can redistribute it and/or modify
 *     it under the terms of the GNU General Public License as published by
 *     the Free Software Foundation, either version 3 of the License, or
 *     (at your option) any later version.
 *
 *     This program is distributed in the hope that it will be useful,
 *     but WITHOUT ANY WARRANTY; without even the implied warranty of
 *     MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *     GNU General Public License for more details.
 *
 *     You should have received a copy of the GNU General Public License
 *     along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
/**
 * @addtogroup CapTouch
 * @{
 * @file      CapTouch.c
 * @author    Jeramie Vens
 * @date      June 1, 2015 - Created
 * @brief     The main code for the Cap Touch controller.
 */

#include <msp430.h>
#include "CapTouch.h"
#include "CapTouchTypes.h"
#include "CapTouchSensors.h"
#include "SysClk.h"
#include "debug.h"

//----------------------//
//-- GLOBAL VARIABLES --//
//----------------------//
// The array holding the capacitance touch results
struct CapTouchResult capTouch[5][5];

/// Global capacitance touch data
static volatile struct CapTouchData capTouchData =
{
	.updateFinished = 0,
	.mostRecentAge = 0,
	.onUpdateFinished = NULL,
	.channelA =
	{
		.number_sensors = CAP_TOUCH_NUM_A,
		.capture_register = &TA2CCR0,
		.ctl_register = &TA2CTL,
		.cctl_register = &TA2CCTL0,
		.captio_register = &CAPTIO0CTL,
		.sensors = capTouchPinsA
	},
	.channelB =
	{
		.number_sensors = CAP_TOUCH_NUM_B,
		.capture_register = &TA3CCR0,
		.ctl_register = &TA3CTL,
		.cctl_register = &TA3CCTL0,
		.captio_register = &CAPTIO1CTL,
		.sensors = capTouchPinsB
	}
};

//-------------------------//
//-- FUNCTION PROTOTYPES --//
//-------------------------//
void CapTouchOnUpdate(unsigned char source);
void CapTouchInitChannel(volatile struct CapTouchChannel * channel);
void CapTouchOnChannelFinished(void);
void CapTouchOnEdge(volatile struct CapTouchChannel * channel);
void CapTouchIsrA(void);
void CapTouchIsrB(void);

//---------------//
//-- FUNCTIONS --//
//---------------//

/**
 * Initialize the capacitive touch system.
 * @param     update_frequency
 *                 The frequency the capacitive touch should update in terms
 *                 of clock cycles of Timer B0.
 * @remark    This system requires the ACLK to be running at 10kHz.
 * @resource  Timer A2
 * @resource  Timer A3
 * @resource  Timer B0.3
 * @resource  Cap Touch 0
 * @resource  Cap Touch 1
 */
void CapTouchInit(unsigned short update_frequency)
{
	debug("INIT : CAP TOUCH\n\r");
	//-- TIMER A2.0 --//
	CapTouchInitChannel(&capTouchData.channelA);

	//-- TIMER A3.0 --//
	CapTouchInitChannel(&capTouchData.channelB);

	//-- TIMER B0.3--//
	// CAPTURE COMPARE INPUT = GND
	TB0CCTL3 = CCIS_2;
	// SET THE UPDATE FREQUENCY
	TB0CCR3 = update_frequency;
	// REGISTER THE CALLBACK HANDLER
	SysClkRegisterCallback(3, CapTouchOnUpdate); // register the callback for the clock
	// START THE CAPACATIVE TOUCH SYSTEM
	// ENABLE INTERRUPT
	TB0CCTL3 |= CCI;
}

/**
 * Initialize a channel of the capacitive touch
 * @param     channel
 *                 The channel to init
 */
void CapTouchInitChannel(volatile struct CapTouchChannel * channel)
{
	// CLOCK SOURCE = CAPACITANCE CIRCUIT
	// INPUT DIVIDER = /1
	// MODE CONTROL = STOPED
	// CLEAR THE TIMER
	*channel->ctl_register = TASSEL__INCLK | ID__1 | MC__STOP | TACLR;
	// CAPTURE MODE = RISING EDGE
	// CAPTURE SOURCE = CCI0B = ACLK
	// CAPTURE SYNCHRONIZED
	// CAPTURE MODE
	// INTERRUPT ENABLED
	*channel->cctl_register = CM_1 | CCIS_1 | SCS | CAP | CCI;
	// CLEAR THE CAPUTURE/COMPARE REGISTER
	*channel->capture_register = 0;
	// update local channel variables
	channel->current_age = 0;
	channel->current_sensor_number = 0;
	channel->edge_number = 0;
	channel->first_edge_time = 0;
	channel->last_edge_time = 0;
	channel->update_finished = 0;
}

/**
 * Register a callback function to be called each time the the cap touch is updated
 * @param     onUpdate
 *                 Callback to be called each time the entire pannel has been updated
 */
void CapTouchRegisterOnUpdate(void volatile (*onUpdate)(unsigned char age))
{
	capTouchData.onUpdateFinished = onUpdate;
}

/**
 * Called whenever one of the channels is finished with its update.
 * @details   When all of the channels have finished and called this
 *            function the onUpdate callback will be called.
 */
void CapTouchOnChannelFinished(void)
{
	if(capTouchData.channelA.update_finished && capTouchData.channelB.update_finished)
	{
		// update the main age flag
		capTouchData.mostRecentAge = capTouchData.channelA.current_age;
		// set the main update finished flag
		capTouchData.updateFinished = 1;
		// clear the update finished flags
		capTouchData.channelA.update_finished = 0;
		capTouchData.channelB.update_finished = 0;
		// if a callback is registered
		if(capTouchData.onUpdateFinished)
		{
			// call the callback
			capTouchData.onUpdateFinished(capTouchData.mostRecentAge);
		}
	}
}

/**
 * Handle an edge event form one of the channels
 * @param     channel
 *                 The channel that generated the event
 */
void CapTouchOnEdge(volatile struct CapTouchChannel * channel)
{
	// if this is the first edge detected
	if(channel->edge_number == 0)
	{
		// save the time
		channel->first_edge_time = *channel->capture_register;
		// advance edge number
		channel->edge_number ++;
		return;
	}
	// if this is not first edge and not the number of edges we are looking for
	else if(channel->edge_number < CAP_TOUCH_NUMBER_EDGES)
	{
		// advance the edge number
		channel->edge_number ++;
		return;
	}
	// we have detected enough edges
	else
	{
		// turn off the timer
		*channel->ctl_register &= ~0x0030;
		// save the time
		channel->last_edge_time = *channel->capture_register;
		// calculate the resulting touch
		channel->sensors[channel->current_sensor_number].result->value = CAP_TIME_TO_RESULT(channel->last_edge_time - channel->first_edge_time);
		// save the update age
		channel->sensors[channel->current_sensor_number].result->age = channel->current_age;
		// advance to the next sensor
		channel->current_sensor_number++;
		// clear the timer
		*channel->ctl_register |= TACLR;
		// reset the edge count
		channel->edge_number = 0;
		// if there are more sensors
		if(channel->current_sensor_number < channel->number_sensors)
		{
			// set the cap touch to the next sensor
			*channel->captio_register = 0x0100 | channel->sensors[channel->current_sensor_number].sensor;
			// Turn the timer back on
			*channel->ctl_register |= MC__CONTINUOUS;
		}
		// if this was the last sensor
		else
		{
			// reset back to the first channel
			channel->current_sensor_number = 0;
			// show we are done
			channel->update_finished = 1;
			CapTouchOnChannelFinished();
		}
		return;
	}
}

/**
 * Called periodically as a callback by the Timer B0.3.  Update all cap touch data.
 * @param     source
 *                 Always 3, not needed by us.
 */
void CapTouchOnUpdate(unsigned char source)
{
	if(capTouchData.updateFinished == 0)
	{
		debug("ERROR : Cap Touch Still In Progress\n\r");
		// todo, may need to handle this case better.
		return;
	}
	debug("DEBUG : UPDATING CAP TOUCH\n\r");
	// clear the update finished flag
	capTouchData.updateFinished = 0;
	// reset back to the first sensor
	capTouchData.channelA.current_sensor_number = 0;
	capTouchData.channelB.current_sensor_number = 0;
	// increment the age value
	capTouchData.channelA.current_age ++;
	capTouchData.channelB.current_age ++;
	// set the cap touch pin selection
	*capTouchData.channelA.captio_register = 0x0100 | capTouchData.channelA.sensors[0].sensor;
	*capTouchData.channelB.captio_register = 0x0100 | capTouchData.channelB.sensors[0].sensor;
	// turn on the timers
	*capTouchData.channelA.ctl_register |= MC__CONTINUOUS;
	*capTouchData.channelB.ctl_register |= MC__CONTINUOUS;
}

/**
 * ISR called on an edge event by Timer A2.0
 */
#pragma vector=TIMER2_A0_VECTOR
void CapTouchIsrA(void)
{
	// handle the edge event
	CapTouchOnEdge(&capTouchData.channelA);
}

/**
 * ISR called on an edge event by timer A3.0
 */
#pragma vector=TIMER3_A0_VECTOR
void CapTouchIsrB(void)
{
	// handle the edge event
	CapTouchOnEdge(&capTouchData.channelB);
}


/// @}
