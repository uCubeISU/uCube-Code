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
 * @addtogroup SysClk
 * @{
 * @file      SysClk.c
 * @author    Jeramie Vens
 * @date      June 1, 2015 - Created
 * @date      June 2, 2015 - Changed the method of using units.
 * @brief     Main source code for handeling the system clock.
 */

#include <msp430.h>
#include <intrinsics.h>
#include "SysClk.h"
#include "debug/debug.h"
#include "string.h"

#define SYS_CLK_NUM_CHANNELS 7

/**
 * A system clock callback.
 * The system clock can call the registered callback functions in the requested
 * periods using the Timer B0 module of the MCU.
 */
struct SysClkCallback
{
	/// Function to call
	SysClkCallback function;
	/// Number of time the function has been called since being registered
	unsigned long long time;
	/// The current overflow count
	unsigned short num_overflows;
	/// The number of overflows that must occure before the time has elapsed
	unsigned short overflows;
	/// The time between each overflow in microseconds
	unsigned short period;
	/// The period register associated with this callback
	volatile unsigned int * period_register;
	/// The control register associated with this callback
	volatile unsigned int * control_register;
};

/**
 * Internal data for the system clock system.
 */
struct SysClkData
{
	/// List of all periodic callbacks
	struct SysClkCallback callbacks[SYS_CLK_NUM_CHANNELS];
	/// The current timer overflow count
	unsigned long long overflow_count;
	/// Callback to be called on the timer overflow every 62.536ms.
	SysClkCallback onOverflow;
};

/// Local data for the SysClk module
static volatile struct SysClkData sysClkData;

// Assuming SMCLK is running at 16MHz, the timer will run at 1MHz

/**
 * Helper function to convert a peiod and unit to a period and overflow.
 * @param     period
 *                 How often the callback should be called.
 * @param     unit
 *                 The units of period
 * @param     cb
 *                 The callback object to save the result to
 */
void SysClkSetPeriod(unsigned short period, SysClkUnit unit, volatile struct SysClkCallback *cb)
{
	switch(unit)
	{
	case usec:
		cb->period = period;
		cb->overflows = 0;
		break;
	case msec:
		// if less than 65 we can use the number in terms of msec
		if(period < 65)
		{
			cb->period = period * 1000;
			cb->overflows = 0;
		}
		// if not, interrupt every 1msec for period times
		else
		{
			cb->period = 1000;
			cb->overflows = period;
		}
		break;
	case sec:
		// interrupt every 50 msec for 20*period times
		cb->period = 50000;
		cb->overflows = period * 20;
		break;
	}
}

/**
 * Initialized the system clock system.
 * @param     period
 *                 How often the main on tick callback should be called
 * @param     unit
 *                 The units of period
 * @param     onTick
 *                 The function to call
 * @remark    This does not actually start the system clock.  That must
 *            be done by calling SysClkStart().
 * @resource  Timer B0
 */
void SysClkInit(unsigned short period, SysClkUnit unit, SysClkCallback onTick)
{
	// clear all callback data
	memset((void*)sysClkData.callbacks, 0, sizeof(sysClkData.callbacks));
	sysClkData.overflow_count = 0;
	sysClkData.onOverflow = NULL;
	// set all the period registers
	sysClkData.callbacks[0].period_register = &TB0CCR0;
	sysClkData.callbacks[1].period_register = &TB0CCR1;
	sysClkData.callbacks[2].period_register = &TB0CCR2;
	sysClkData.callbacks[3].period_register = &TB0CCR3;
	sysClkData.callbacks[4].period_register = &TB0CCR4;
	sysClkData.callbacks[5].period_register = &TB0CCR5;
	sysClkData.callbacks[6].period_register = &TB0CCR6;
	// set all the control registersData.callbacks));
	// set all the period registers
	sysClkData.callbacks[0].control_register = &TB0CCTL0;
	sysClkData.callbacks[1].control_register = &TB0CCTL1;
	sysClkData.callbacks[2].control_register = &TB0CCTL2;
	sysClkData.callbacks[3].control_register = &TB0CCTL3;
	sysClkData.callbacks[4].control_register = &TB0CCTL4;
	sysClkData.callbacks[5].control_register = &TB0CCTL5;
	sysClkData.callbacks[6].control_register = &TB0CCTL6;
	// save the onTick callback
	sysClkData.callbacks[0].function = onTick;
	SysClkSetPeriod(period, unit, &sysClkData.callbacks[0]);
	// Init the timer control
	TB0CTL = TBSSEL__SMCLK | ID__8 | MC__STOP | TBCLR; // divide by 8
	// set extra clock divider
	TB0EX0 = 1; // divide by 2
	// set the first period
	TB0CCR0 = sysClkData.callbacks[0].period;
	// enable the interrupt on the main system clock
	TB0CCTL0 = CCIE;
}

/**
 * Start the system clock running.
 */
void SysClkStart(void)
{
	TB0CTL |= MC__CONTINUOUS;
}

/**
 * Register a new callback function to be called periodically.
 * @param     period
 *                 How often the callback should be called.
 * @param     unit
 *                 The unit of period.
 * @param     callback
 *                 The function to call periodically.
 * @return    -1 if the callback could not be registered.
 * @return    handle (>0) to the callback that can be used to edit it in the future.
 */
signed char SysClkRegisterCallback(unsigned short period, SysClkUnit unit, SysClkCallback callback)
{
	unsigned char i;
	// search for an unused channel
	for(i=1; (i < SYS_CLK_NUM_CHANNELS) || (i=0); i++) // ignore the warning, this line is correct
	{
		if(sysClkData.callbacks[i].function)
		{
			break;
		}
	}
	// if all channels are in use
	if(i==0)
	{
		debug("ERROR : ALL TIMER B0 CHANNELS USED\n\r");
		return -1;
	}
	// save the callback data
	sysClkData.callbacks[i].function = callback;
	SysClkSetPeriod(period, unit, &sysClkData.callbacks[i]);
	// set the period
	*sysClkData.callbacks[i].period_register = TB0R + sysClkData.callbacks[i].period;
	// enable the interrupt
	*sysClkData.callbacks[i].control_register |= CCIE;
	return i;
}

/**
 * Handle an on tick event due to a compare event happening.
 * @param     number
 *                 The callback number that coresponds to this event.
 */
inline void SysClkOnTick(unsigned char number)
{
	// advance the period register
	*sysClkData.callbacks[number].period_register += sysClkData.callbacks[number].period;
	// increment the number of overflows
	sysClkData.callbacks[number].num_overflows ++;
	// if we have overflowed enough times
	if(sysClkData.callbacks[number].num_overflows > sysClkData.callbacks[0].overflows)
	{
		// reset the overflow count
		sysClkData.callbacks[number].num_overflows = 0;
		// advance the time
		sysClkData.callbacks[number].time ++;
		// todo make sure the callback is not already running and add debuging info about how much time we spend in the callback.
		// re-enable interrupts
		__enable_interrupt();
		// call the callback
		sysClkData.callbacks[number].function(sysClkData.callbacks[0].time);
	}
}

/**
 * ISR called on capture 0 event.
 */
#pragma vector=TIMER0_B0_VECTOR
void TimerB0Cc0Isr(void)
{
	SysClkOnTick(0);
}

/**
 * ISR called on all Timer B0 events except capture 0
 */
#pragma vector=TIMER0_B1_VECTOR
void TimerB0CcxIsr(void)
{
	switch(TB0IV)
	{
	case 0x02:
		SysClkOnTick(1);
		break;
	case 0x04:
		SysClkOnTick(2);
		break;
	case 0x06:
		SysClkOnTick(3);
		break;
	case 0x08:
		SysClkOnTick(4);
		break;
	case 0x0A:
		SysClkOnTick(5);
		break;
	case 0x0C:
		SysClkOnTick(6);
		break;
	case 0x0E:
		sysClkData.overflow_count ++;
		if(sysClkData.onOverflow)
		{
			__enable_interrupt();
			sysClkData.onOverflow(sysClkData.overflow_count);
		}
		break;
	}
}

/// @}
