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
 * @addtogroup usci
 * @{
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

#include <stdint.h>
#include "Usci.h"

namespace ucube {
/// Namespace for the I2cMode enum.
namespace I2cMode{
	/// Enum of the current mode of the device, master or slave.
	enum I2cMode{
		SLAVE,
		MASTER,
	};
}

/// Namespace for the I2cRxTx
namespace I2cRxTx{
	/// Enum of the current state of the device, transmission or receiving.
	enum I2cRxTx{
		RX,
		TX,
	};
}

class I2c: private Usci {
public:
	/**
	 * @brief     Constructor for I2C on the MSP430.
	 * @details   Initializes the I2C bus by enabling the chosen I2C module. Resets
	 *            the module, enables the slave module, uses the system clock,
	 *            and sets the data transfer rate. Also puts the state to slave mode.
	 */
	I2c(uint8_t my_address);
	virtual ~I2c();
	/**
	 * @brief     Recieve function for I2C as master.
	 * @details   Sets the state machine to master TX mode initially.
	 *            Then recieves data from the Tiva through the FRAM by transmitting the address
	 *            of the slave as well as the latch address. Then switches the state machine to
	 *            RX mode and receives the data from the FRAM storing it in a buffer.
	 */
	unsigned char volatile * ReceiveFrom(uint8_t slave_address, char *array, uint16_t latch, int length);
	/**
	 * @brief     Transmit function for I2C as master.
	 * @details   Sets the state machine to master TX mode. Selects the slave address
	 *            and enables the TX interrupt. Then sends a start condition and sends
	 *            the latch address for where to send the data to.
	 */
	void TransmitTo(uint8_t slave_address, uint8_t data, uint16_t latch_address, int length);

private:
	/// Flag determining whether device has finished receiving data.
	volatile unsigned char flag;
	/// Buffer holding the received data in master mode.
	volatile char* buffer;
	/// Number of bytes currently sent by the function.
	volatile unsigned char number_bytes;
	/// The latch address of the device stating where to obtain data from or send data to within the slave.
	volatile uint16_t latch_addr;
	/// The slave address of the device to send to or receive from.
	volatile uint8_t slave_addr;
	/// 1 byte value containing the data to be transmitted.
	volatile uint8_t TxData;
	/// Length of data in bytes you would like to send.
	int length;
	/// Mode of the device, master or slave.
	I2cMode::I2cMode mode;
	/// State of the device, transmission or receiving.
	I2cRxTx::I2cRxTx RxTx;

	void OnSerialRx();
	void OnSerialTx();
};

} /* namespace ucube */

#endif /* I2C_H_ */

/// @}
/// @}

