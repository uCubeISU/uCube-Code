/**
 * @addtogroup usci USCI
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
	/**
	 * Create a new serial port on the given channel
	 * @details    Create a new USCI protocol on the given channel
	 * @param      channel
	 *                  The USCI channel to attach this serial protocol to
	 */
	Usci(UsciChannel::UsciChannel channel);
	/// Clean up the USCI
	~Usci();
protected:
	/**
	 * Callback for new Rx data interrupt fired
	 * @details    After registering with the RegisterSerialIsr() this callback
	 *             will be called on each RX interrupt.
	 * @param      source
	 *                 The source of the interrupt
	 */
	virtual void OnSerialRx(UsciChannel::UsciChannel source) = 0;
	/**
	 * Callback for new Tx data interrupt fired
	 * @details    After registering with the RegisterSerialIsr() this callback
	 *             will be called on each TX interrupt.
	 * @param      source
	 *                 The source of the interrupt
	 */
	virtual void OnSerialTx(UsciChannel::UsciChannel source) = 0;
	/**
	 * Read a byte from the USCI RX register.
	 * @return     The byte read from the RX register
	 */
	unsigned char SerialReadByte();
	/**
	 * Write the byte to the USCI TX register.
	 * @param      byte
	 *                  The byte to write to the TX register
	 */
	void SerialSendByte(unsigned char byte);

	/**
	 * Set the state of the software reset bit
	 * @param      reset
	 *                  The value to set the reset bit to.  True=reset
	 */
	void SetUsciResetMode(bool reset);

	/**
	 * Write the USCI control 0 register
	 * @param      value
	 *                  The value to write to the register
	 */
	void SetUsciControl0(unsigned char value);

	/**
	 * Write the USCI control 1 register
	 * @param      value
	 *                  The value to write to the register
	 */
	void SetUsciControl1(unsigned char value);

	/**
	 * Write the USCI Baud registers
	 * @param      value
	 * 					The value to write to the registers
	 */
	void SetUsciBaud(unsigned short value);

	/**
	 * The USCI that this serial object is connected to
	 */
	UsciChannel::UsciChannel usciChannel;
private:
	/**
	 * The object registered to receive callbacks from USCIA
	 */
	static Usci* usciACallbacks;
	/**
	 * The object registered to receive callbacks from USCIB
	 */
	static Usci* usciBCallbacks;
	/// RX interrupt vector ISR
	friend void USCIAB0RX_ISR(void);
	/// TX interrupt vector ISR
	friend void USCIAB0TX_ISR(void);

};

} /* namespace ucube */

#endif /* SERIALINTERRUPT_H_ */

/// @}
