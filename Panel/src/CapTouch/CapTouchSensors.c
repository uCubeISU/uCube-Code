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
 * @file      CapTouchSensors.c
 * @author    Jeramie Vens
 * @date      June 1, 2015 - Created
 * @brief     The pin maping for the cap touch sensors
 */

#include "CapTouch.h"
#include "CapTouchTypes.h"
#include "CapTouchSensors.h"

/// The capacitance touch sensors connected to CapTouchA
const struct CapTouchSensor capTouchPinsA[CAP_TOUCH_NUM_A] =
{
	{.port = 3, .pin = 7, .result = &capTouch[0][0]},
	{.port = 9, .pin = 1, .result = &capTouch[0][2]},
	{.port = 9, .pin = 5, .result = &capTouch[0][4]},
	{.port = 3, .pin = 6, .result = &capTouch[1][1]},
	{.port = 9, .pin = 4, .result = &capTouch[1][3]},
	{.port = 3, .pin = 4, .result = &capTouch[2][0]},
	{.port = 9, .pin = 3, .result = &capTouch[2][2]},
	{.port = 0, .pin = 4, .result = &capTouch[2][4]},
	{.port = 2, .pin = 7, .result = &capTouch[3][1]},
	{.port = 4, .pin = 0, .result = &capTouch[3][3]},
	{.port = 5, .pin = 0, .result = &capTouch[4][0]},
	{.port = 1, .pin = 4, .result = &capTouch[4][2]},
	{.port = 4, .pin = 1, .result = &capTouch[4][4]}
};

/// The capacitance touch sensors connected to CapTouchB
const struct CapTouchSensor capTouchPinsB[CAP_TOUCH_NUM_B] =
{
	{.port = 1, .pin = 2, .result = &capTouch[0][1]},
	{.port = 9, .pin = 2, .result = &capTouch[0][3]},
	{.port = 3, .pin = 5, .result = &capTouch[1][0]},
	{.port = 1, .pin = 3, .result = &capTouch[1][2]},
	{.port = 9, .pin = 6, .result = &capTouch[1][4]},
	{.port = 3, .pin = 3, .result = &capTouch[2][1]},
	{.port = 9, .pin = 7, .result = &capTouch[2][3]},
	{.port = 5, .pin = 1, .result = &capTouch[3][0]},
	{.port = 4, .pin = 3, .result = &capTouch[3][2]},
	{.port = 0, .pin = 5, .result = &capTouch[3][4]},
	{.port = 1, .pin = 5, .result = &capTouch[4][1]},
	{.port = 4, .pin = 2, .result = &capTouch[4][3]}
};

/// @}
