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
 * @addtogroup usci Universal Serial Common Interface
 * @{
 * @file      Usci.h
 * @author    Jeramie Vens
 * @date      April 25, 2015: Created
 * @brief     The main USCI include file
 * @details   The USCI on the MSP430 is a universal serial interface which
 *            several different modes of operations.
 */

#ifndef USCI_H_
#define USCI_H_


#include <msp430.h>
namespace ucube {

/// USCI channels available on the MSP430
namespace UsciChannel {
	/// All possible USCI channels available on the MSP430
	enum UsciChannel
	{
		/// The ISR source is the USCI A
		USCIA,
		/// The ISR source is the USCI B
		USCIB
	};
}

/// USCI synchronous or asynchronous operation mode
namespace UsciSynchronousMode{
	/// Settings if the USCI should operate in asynchronous or synchronous mode.
	enum UsciSynchronousMode{
		/// operate asynchronously
		Asynchronous = 0,
		/// operate synchronously
		Synchronous = BIT0
	};
}

/**
 * Abstract interface for USCI serial classes
 * @details     The USCI is the universal serial communication interface on the
 *              MSP430.  It provides several different serial protocols in
 *              shared hardware which contains many similarities.  This is the
 *              top level implementation of the USCI serial modes.
 */
class Usci {
public:
	/// Create a new USCI on the given channel
	Usci(UsciChannel::UsciChannel channel);
	/// Clean up the USCI
	~Usci();
protected:
	/// Read a byte from the USCI RX register.
	unsigned char SerialReadByte();
	/// Write a byte to the USCI TX register.
	void SerialSendByte(unsigned char byte);

	/// Set the state of the software reset bit.
	void SetUsciResetMode(bool reset);

	/// Write the USCI control 0 register.
	void SetUsciControl0(unsigned char value);
	/// Write the USCI control 1 register.
	void SetUsciControl1(unsigned char value);

	/// Write the USCI Baud registers.
	void SetUsciBaud(unsigned short value);

	/// The USCI that this serial object is connected to.
	const UsciChannel::UsciChannel usciChannel;

	/**
	 * @name Callbacks
	 * @{
	 */
	/**
	 * Callback for new Rx data interrupt fired
	 * @details    This method is called anytime new serial data is received
	 *             and the Rx interrupt has been triggered.
	 */
	virtual void OnSerialRx() = 0;
	/**
	 * Callback for new Tx data interrupt fired
	 * @details    This method is called anytime the Tx buffer is ready to
	 *             receive new data and the Tx interrupt has been triggered.
	 */
	virtual void OnSerialTx() = 0;
	/// @}

private:
	/// The object registered to receive callbacks from USCIA
	static Usci* usciACallbacks;
	/// The object registered to receive callbacks from USCIB
	static Usci* usciBCallbacks;
	/// RX interrupt vector ISR
	friend void USCIAB0RX_ISR(void);
	/// TX interrupt vector ISR
	friend void USCIAB0TX_ISR(void);
};

} /* namespace ucube */

#endif /* SERIALINTERRUPT_H_ */

/// @}
