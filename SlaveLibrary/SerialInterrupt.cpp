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

SerialInterrupt* SerialInterrupt::UsciACallbacks = NULL;
SerialInterrupt* SerialInterrupt::UsciBCallbacks = NULL;

void SerialInterrupt::RegisterSerialIsr(IsrSource::SerialIsrSource source)
{
	switch(source)
	{
	case IsrSource::USCIA:
		SerialInterrupt::UsciACallbacks = this;
		break;
	case IsrSource::USCIB:
		SerialInterrupt::UsciBCallbacks = this;
		break;
	}
}


#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIAB0RX_ISR(void)
{
	if(IFG2 & UCA0RXIFG && SerialInterrupt::UsciACallbacks)
		SerialInterrupt::UsciACallbacks->OnSerialRx(IsrSource::USCIA);
	if(IFG2 & UCB0RXIFG && SerialInterrupt::UsciBCallbacks)
		SerialInterrupt::UsciBCallbacks->OnSerialRx(IsrSource::USCIB);
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIAB0TX_ISR(void)
{
	if(IFG2 & UCA0TXIFG && SerialInterrupt::UsciACallbacks)
		SerialInterrupt::UsciACallbacks->OnSerialTx(IsrSource::USCIA);
	if(IFG2 & UCB0TXIFG && SerialInterrupt::UsciBCallbacks)
		SerialInterrupt::UsciBCallbacks->OnSerialTx(IsrSource::USCIB);

}

}
