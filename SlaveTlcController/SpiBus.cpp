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
 * @addtogroup SlaveTlcController
 * @{
 * @file SpiBus.cpp
 * @author Sprog
 * @date Apr 21, 2015
 * @copyright GNU Public License v3
 * @brief
 * @details
 */

#include <msp430.h>
#include "SpiBus.h"

namespace ucube {

volatile bool SpiBus::IsTransmissionDone = true;

SpiBus::SpiBus() {
	// TODO Auto-generated constructor stub
	P1OUT |= BIT3;							//XLAT Port 3 Pin 0
	P1DIR |= BIT3;							//XLAT PORT 3 Pin 0
	P1SEL = BIT1 | BIT2 | BIT4;				//Port 1 pin 5: System Clock pin 6: Serial in pin 7: Serial out
	P1SEL2 = BIT1 | BIT2 | BIT4;			// Port 1 pin 5, pin 6, pin 7
	P1OUT |= BIT5;							// Port 2 pin 5
	P1DIR |= BIT5;							// Port 2 pin 5

	UCA0CTL1 = UCSWRST;
	UCA0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;  // 3-pin, 8-bit SPI master
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	UCA0BR0 |= 0x02;                          // /2
	UCA0BR1 = 0;                              //
	//UCB0MCTL = 0;                             // No modulation
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	__enable_interrupt();
	IFG2 = 0;
	IE2 = 0x02;//UCB0TXIE;						  	// enable interrupt

   // P1OUT &= ~BIT5;
}

SpiBus::~SpiBus() {
	// TODO Auto-generated destructor stub
}

static unsigned char byte_to_send;

void SpiBus::StartTransmission(unsigned char byte)
{
	SpiBus::IsTransmissionDone = false;
	P1OUT &= (~BIT3); // Select Device
	byte_to_send = byte;
	UCA0TXBUF = byte_to_send; //buffer[0];// tlc_data.data[0];	// Send first byte
	return;
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIA0TX_ISR(void)
{
	static int i = 1;
	if(i < 36*3+1)
	{
		_delay_cycles(100);
		UCA0TXBUF = byte_to_send;//buffer[i];
		i++;
	}
	else
	{
		IFG2 = 0;
		_delay_cycles(100);
		P1OUT |= (BIT3); // Unselect Device
		i = 1;
		SpiBus::IsTransmissionDone = true;
	}
}


} /* namespace ucube */

