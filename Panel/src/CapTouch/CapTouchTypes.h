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
 * @file      CapTouchTypes.h
 * @author    Jeramie Vens
 * @date      June 1, 2015 - Created
 * @brief     Internal types used by the Cap Touch
 */

#ifndef CAPTOUCHTYPES_H_
#define CAPTOUCHTYPES_H_

//-------------------//
//-- DEFINED TYPES --//
//-------------------//
/**
 * A capacitive touch sensor connected to the MCU pin
 */
struct CapTouchSensor{
	union{
		struct{
			/// The port of the touch sensor
			unsigned port : 4;
			/// The pin of the touch sensor
			unsigned pin  : 3;
			unsigned : 1;
		};
		/// The touch sensor to measure
		unsigned char sensor;
	};
	/// Location to store the result of this touch sensor
	struct CapTouchResult * const result;
};

/**
 * A capacitive touch channel in the module
 */
struct CapTouchChannel
{
	/// The number of the sensor currently being sampled
	unsigned char current_sensor_number;
	/// The time stamp of the currently underway update
	unsigned char current_age;
	/// The number of sensors on this channel
	const unsigned char number_sensors;
	/// The number of edges seen by the current sensor
	unsigned char edge_number;
	/// The timer time of the first detected edge
	unsigned char first_edge_time;
	/// The timer time of the last detected edge
	unsigned char last_edge_time;
	/// Flag set to 1 when this channel has updated all sensors
	unsigned char update_finished;
	/// Register for the timer capture
	volatile unsigned int * const capture_register;
	/// Timer control register
	volatile unsigned int * const ctl_register;
	/// Timer caputre control register
	volatile unsigned int * const cctl_register;
	/// Capacitive touch IO register
	volatile unsigned int * const captio_register;
	/// Array of connected sensors
	struct CapTouchSensor const * const sensors;
};

/**
 * Main global capacitive touch module data
 */
struct CapTouchData
{
	/// True if the data has been updated and a update is not in progress
	volatile unsigned char updateFinished;
	/// The time stamp value of the most recent full update
	volatile unsigned char mostRecentAge;
	/// Callback called when all of the sensors have been sammpled
	volatile void (*onUpdateFinished)(unsigned char age);
	/// Channel A data
	volatile struct CapTouchChannel channelA;
	/// Channel B data
	volatile struct CapTouchChannel channelB;
};

#endif /* CAPTOUCHTYPES_H_ */

/// @}

