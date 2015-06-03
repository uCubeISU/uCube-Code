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
 * @addtogroup SysClk System Clock
 * @author    Jeramie Vens
 * @date      June 1, 2015 - Created
 * @date      June 2, 2015 - Documented and cleaned
 * @brief     A system clock which can periodically call functions at different time intervals.
 * @details   The system clock makes use of Timer B0 to call functions at
 *            periodic intervals.  Currently all functions are equal priority
 *            and can interrupt each other.  Therefore, care must be taken
 *            to make the periodic functions finish in the real system before
 *            they are called again.  Failure to do so could lead to stack leaks
 *            and system crashes.
 * @{
 * @file      SysClk.h
 * @author    Jeramie Vens
 * @date      June 1, 2015 - Created with basic skeleton code
 * @date      June 2, 2015 - Majority of code written
 * @brief     The only header file needed to add they system clock functionality.
 */
#ifndef SYSCLK_H_
#define SYSCLK_H_

#define FTB0 	1000000

/*
#define usec 	(1ul)
#define msec 	(1000ul)
#define sec		(1000000ul)
*/

/**
 * Units the system clock can use for the period
 */
typedef enum SysClkUnits
{
	/// Period measured in microseconds.  Min value = 1msec, Max value = 65.536msec
	usec,
	/// Period measured in milliseconds.  Min value = 1msec, Max value = 56.536sec
	msec,
	/// Period measured in seconds. Min value = 1 second, Max value = 47.1 minutes
	sec,
} SysClkUnit;

typedef void (*SysClkCallback)(unsigned long long time);

void SysClkInit(unsigned short period, SysClkUnit unit, SysClkCallback onTick);
void SysClkStart(void);
signed char SysClkRegisterCallback(unsigned short period, SysClkUnit unit, SysClkCallback callback);
void SysClkRegisterOverflowCallback(SysClkCallback callback);

#endif /* SYSCLK_H_ */

/// @}
