/*
 * SerialInterrupt.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: vens
 */

#include <msp430.h>
#include <stdlib.h>
#include "SerialInterrupt.h"

namespace ucube{

SerialInterrupt* SerialInterrupt::usciACallbacks = NULL;
SerialInterrupt* SerialInterrupt::usciBCallbacks = NULL;

void SerialInterrupt::RegisterSerialIsr(UsciChannel::UsciChannel source)
{
	switch(source)
	{
	case UsciChannel::USCIA:
		SerialInterrupt::usciACallbacks = this;
		break;
	case UsciChannel::USCIB:
		SerialInterrupt::usciBCallbacks = this;
		break;
	}
	this->usciChannel = source;
}

inline unsigned char SerialInterrupt::SerialReadByte(void)
{
	switch(this->usciChannel)
	{
	case UsciChannel::USCIA:
		return UCA0RXBUF;
	case UsciChannel::USCIB:
		return UCB0RXBUF;
	default:
		return 0;
	}
}

inline void SerialInterrupt::SerialSendByte(unsigned char byte)
{
	switch(this->usciChannel)
	{
	case UsciChannel::USCIA:
		UCA0TXBUF = byte;
		return;
	case UsciChannel::USCIB:
		UCB0TXBUF = byte;
		return;
	}
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
	if(IFG2 & UCA0RXIFG && SerialInterrupt::usciACallbacks)
		SerialInterrupt::usciACallbacks->OnSerialRx(UsciChannel::USCIA);
	if(IFG2 & UCB0RXIFG && SerialInterrupt::usciBCallbacks)
		SerialInterrupt::usciBCallbacks->OnSerialRx(UsciChannel::USCIB);
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
	if(IFG2 & UCA0TXIFG && SerialInterrupt::usciACallbacks)
		SerialInterrupt::usciACallbacks->OnSerialTx(UsciChannel::USCIA);
	if(IFG2 & UCB0TXIFG && SerialInterrupt::usciBCallbacks)
		SerialInterrupt::usciBCallbacks->OnSerialTx(UsciChannel::USCIB);

}

}
