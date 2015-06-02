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
 * @file      CapTouchSensors.h
 * @author    Jeramie Vens
 * @date      June 1, 2015 - Created
 * @brief     The main sensor arrays for each channel
 */

#ifndef CAPTOUCHSENSORS_H_
#define CAPTOUCHSENSORS_H_

#include "CapTouchTypes.h"

//-------------//
//-- DEFINES --//
//-------------//
/// @def Number of cap touch connected to channel A
#define CAP_TOUCH_NUM_A 13
/// @def Number of cap touch connected to channel B
#define CAP_TOUCH_NUM_B 12

//----------------------//
//-- GLOBAL VARIABLES --//
//----------------------//
extern const struct CapTouchSensor capTouchPinsA[];
extern const struct CapTouchSensor capTouchPinsB[];

#endif /* CAPTOUCHSENSORS_H_ */

/// @}
