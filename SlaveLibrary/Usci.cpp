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
 * @file      Usci.cpp
 * @brief     The class implementation of the Usci class.
 * @author    Jeramie Vens
 * @date      April 25, 2015: Created
 */

#include <msp430.h>
#include <stdlib.h>
#include "Usci.h"

namespace ucube{

Usci* Usci::usciACallbacks = NULL;
Usci* Usci::usciBCallbacks = NULL;

/**
 * @details    Create a new USCI protocol attached to the given channel.
 * 	           The USCI protocol will register the callback methods for the
 * 	           Rx and Tx events on the channel.
 * @param      channel
 *                  The USCI channel to attach this serial protocol to
 */
Usci::Usci(UsciChannel::UsciChannel channel)
	: usciChannel(channel) // set the value of this->usciChannel
{
	switch(usciChannel)
	{
	case UsciChannel::USCIA:
		Usci::usciACallbacks = this;
		break;
	case UsciChannel::USCIB:
		Usci::usciBCallbacks = this;
		break;
	}
}

/**
 * @details   Remove the callbacks from the ISR handler and clean up other
 *            allocated resources.
 */
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

/**
 * @details    Read the current value from the USCI Rx register.
 * @return     The byte read from the RX register
 */
unsigned char Usci::SerialReadByte(void)
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

/**
 * @details   Write a byte to the USCI Tx register initiating a serial transfer.
 * @param     byte
 *                 The byte to write to the TX register
 */
void Usci::SerialSendByte(unsigned char byte)
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

/**
 * @details   The software reset bit is used to reset the USCI module during
 *            during configuration.  All configuration should be done with
 *            the USCI in software reset and then the software reset should
 *            be released by passing false to this method.
 * @param     reset
 *                 The value to set the reset bit to.  True=reset
 */
void Usci::SetUsciResetMode(bool reset)
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

/**
 * @details   Set the USCI control 0 register to the given value.
 * @param     value
 *                 The value to write to the register.
 */
void Usci::SetUsciControl0(unsigned char value)
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

/**
 * @details    Set the USCI control 1 register to the given value.
 * @param      value
 *                  The value to write to the register.
 * @remark     This call will NOT effect the state of the software
 *             reset bit.  That bit is only effected by calling
 *             Usci::SetUsciResetMode().
 */
void Usci::SetUsciControl1(unsigned char value)
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

/**
 * @details    Set the value of the USCI Baud registers.
 * @param      value
 * 					The value to write to the registers
 */
void Usci::SetUsciBaud(unsigned short value)
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

/**
 * @details   The interrupt service routine for the USCI Rx interrupt for both
 *            channels A and B.  This ISR calls the appropriate callback if they
 *            exist based on the interrupt source.
 */
#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
	if(IFG2 & UCA0RXIFG && Usci::usciACallbacks)
		Usci::usciACallbacks->OnSerialRx();
	if(IFG2 & UCB0RXIFG && Usci::usciBCallbacks)
		Usci::usciBCallbacks->OnSerialRx();
}

/**
 * @details   The interrupt service routine for the USCI Tx interrupt for both
 *            channels A and B.  This ISR calls the appropriate callbacks if they
 *            exist based on the interrupt source.
 */
#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
	if(IFG2 & UCA0TXIFG && Usci::usciACallbacks)
		Usci::usciACallbacks->OnSerialTx();
	if(IFG2 & UCB0TXIFG && Usci::usciBCallbacks)
		Usci::usciBCallbacks->OnSerialTx();

}

}

/// @}
