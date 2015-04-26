/*
 * SerialInterrupt.h
 *
 *  Created on: Apr 25, 2015
 *      Author: vens
 */

#ifndef USCI_H_
#define USCI_H_

void test_fn(void);

namespace ucube {

/// ISR Sources for the ucube
namespace UsciChannel {
	enum UsciChannel
	{
		/// The ISR source is the USCI A
		USCIA,
		/// The ISR source is the USCI B
		USCIB
	};
}

/**
 * Abstract interface for USCI serial bus classes.
 * @details     On the MSP430 the USCIA and USCIB share interrupt vectors.  This
 *              interface determines the correct source of the interrupt and
 *              calls the callback of the registered object.
 */
class Usci {
public:
	/**
	 * A UCSI object
	 * @details    Once configured the ISRs will call the appropriate
	 *             SerialInterrupt::OnSerialRx() and SerialInterrupt::OnSerialTx()
	 *             callback methods.
	 * @param      channel
	 *                  The USCI channel to attach this serial interrupt to
	 */
	Usci(UsciChannel::UsciChannel channel);
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
	 */
	unsigned char SerialReadByte();
	/**
	 * Write the byte to the USCI TX register.
	 */
	void SerialSendByte(unsigned char byte);
private:
	/**
	 * The object registered to receive callbacks from USCIA
	 */
	static Usci* usciACallbacks;
	/**
	 * The object registered to receive callbacks from USCIB
	 */
	static Usci* usciBCallbacks;
	/**
	 * The USCI that this serial object is connected to
	 */
	UsciChannel::UsciChannel usciChannel;
	/// RX interrupt vector ISR
	friend void USCIAB0RX_ISR(void);
	/// TX interrupt vector ISR
	friend void USCIAB0TX_ISR(void);

};

} /* namespace ucube */

#endif /* SERIALINTERRUPT_H_ */
