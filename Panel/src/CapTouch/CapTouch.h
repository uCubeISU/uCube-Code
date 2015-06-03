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
 * @addtogroup CapTouch Capacitive Touch
 * @author    Jeramie Vens
 * @date      June 1, 2015 - Created
 * @brief     The main Capacitive Touch module and code
 * @details   The Cap Touch is the method of detecting touching of the panel.
 *            This module measures the raw touch data periodically and stores
 *            the results in the capTouch array.  On each update of the cap
 *            touch data a callback function can be called for gesture
 *            recognition or other uses.
 * @{
 * @file      CapTouch.h
 * @author    Jeramie Vens
 * @date      June 1, 2015 - Created
 * @brief     Only include file needed for the Cap Touch.
 */

#ifndef CAPTOUCH_H_
#define CAPTOUCH_H_

#include "SysClk/SysClk.h"

#ifndef NULL
#define NULL ((void *) 0)
#endif

/// @def The number of edges to detect
#define CAP_TOUCH_NUMBER_EDGES 1
/// @def Conversion from time to result
#define CAP_TIME_TO_RESULT(time) (time >> 8)

void CapTouchInit(unsigned short update_period, SysClkUnit unit);
void CapTouchRegisterOnUpdate(void volatile (*onUpdate)(unsigned char age));

/// The result from a capacitive touch sensor
struct CapTouchResult{
	/// The value where 0 is no touch and 255 is a full press
	unsigned char value;
	/// The timestamp of the oldest update to the sensor
	unsigned char age;
};

/// Array of all of the capacitance touch sensors results
extern struct CapTouchResult capTouch[5][5];

#endif /* CAPTOUCH_H_ */

/// @}
