/*
 * SerialInterrupt.cpp
 *
 *  Created on: Apr 25, 2015
 *      Author: vens
 */

#include <msp430.h>
#include <stdlib.h>
#include "Usci.h"

namespace ucube{

Usci* Usci::usciACallbacks = NULL;
Usci* Usci::usciBCallbacks = NULL;

Usci::Usci(UsciChannel::UsciChannel channel)
{
	switch(channel)
	{
	case UsciChannel::USCIA:
		Usci::usciACallbacks = this;
		break;
	case UsciChannel::USCIB:
		Usci::usciBCallbacks = this;
		break;
	}
	this->usciChannel = channel;
}

Usci::~Usci()
{
	switch(this->usciChannel)
	{
	case UsciChannel::USCIA:
		Usci::usciACallbacks = NULL;
		break;
	case UsciChannel::USCIB:
		Usci::usciBCallbacks = NULL;
		break;
	}
}

inline unsigned char Usci::SerialReadByte(void)
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

inline void Usci::SerialSendByte(unsigned char byte)
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

inline void Usci::SetUsciResetMode(bool reset)
{
	switch(this->usciChannel)
	{
	case UsciChannel::USCIA:
		if(reset)
			UCA0CTL1 |= UCSWRST;
		else
			UCA0CTL1 &= ~UCSWRST;
		break;
	case UsciChannel::USCIB:
		if(reset)
			UCB0CTL1 |= UCSWRST;
		else
			UCB0CTL1 &= ~UCSWRST;
		break;

	}
}

inline void Usci::SetUsciControl0(unsigned char value)
{
	switch(this->usciChannel)
	{
	case UsciChannel::USCIA:
		UCA0CTL0 = value;
		break;
	case UsciChannel::USCIB:
		UCB0CTL0 = value;
		break;
	}
}

inline void Usci::SetUsciControl1(unsigned char value)
{
	switch(this->usciChannel)
	{
	case UsciChannel::USCIA:
		UCA0CTL1 = value | (UCA0CTL1 & UCSWRST);
		break;
	case UsciChannel::USCIB:
		UCB0CTL1 = value | (UCB0CTL1 & UCSWRST);
		break;
	}
}

inline void Usci::SetUsciBaud(unsigned short value)
{
	switch(this->usciChannel)
	{
	case UsciChannel::USCIA:
		UCA0BR0 = value;
		UCA0BR1 = value >> 8;
		break;
	case UsciChannel::USCIB:
		UCB0BR0 = value;
		UCB0BR1 = value >> 8;
		break;
	}
}

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
	if(IFG2 & UCA0RXIFG && Usci::usciACallbacks)
		Usci::usciACallbacks->OnSerialRx(UsciChannel::USCIA);
	if(IFG2 & UCB0RXIFG && Usci::usciBCallbacks)
		Usci::usciBCallbacks->OnSerialRx(UsciChannel::USCIB);
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
	if(IFG2 & UCA0TXIFG && Usci::usciACallbacks)
		Usci::usciACallbacks->OnSerialTx(UsciChannel::USCIA);
	if(IFG2 & UCB0TXIFG && Usci::usciBCallbacks)
		Usci::usciBCallbacks->OnSerialTx(UsciChannel::USCIB);

}

}
