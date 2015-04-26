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
 * @addtogroup I2C
 * @{
 * @file      I2c.h
 * @author    Iowa State University uCube team
 * @author    Andy Snawerdt
 * @author    Jeramie Vens
 * @author    Kris Burney
 * @date      Mar 28, 2015
 * @brief     I2C header file
 * @copyright Copyright (C) 2015 ISU uCube team
 * @details   This file contains the I2c constructor and methods including
 *            transmission and recieving in both master and slave mode.
 */


#ifndef I2C_H_
#define I2C_H_

namespace ucube {

class I2c {
public:
	/**
	 * @brief     Initialization for I2C on the MSP430.
	 * @details   Initializes the I2C bus by enabling the chosen I2C module. Resets
	 *            the module, enables the master module, uses the system clock,
	 *            and sets the data transfer rate.
	 */
	I2c();
	virtual ~I2c();
	/**
	 * @brief     Recieve function for I2C as slave.
	 * @details   Multi-master system. Recieves data from the Tiva through the FRAM
	 *            by selecting the address of the slave and enabling an interrupt which
	 *            contains a state machine dealing with whether certain portions of the
	 *            recieve function.
	 */
	unsigned char volatile * I2c::ReceiveFrom(uint8_t slave_address, char *array, uint16_t latch);
};

} /* namespace ucube */

#endif /* I2C_H_ */

/// @}
