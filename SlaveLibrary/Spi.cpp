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
 * @addtogroup SPI
 * @{
 * @file Spi.cpp
 * @author Jeramie Vens
 * @date Apr 21, 2015
 * @copyright GNU Public License v3
 * @brief     The class implementation of the Spi class.
 * @details
 */

#include <msp430.h>
#include "Spi.h"

namespace ucube {

using namespace ucube;

/*
 * MISO: P1.1
 * MOSI: P1.2
 * CLK:  P1.4
 * TLC_SS: P2.3
 * TLC_BLANK: P1.5
 */
/**
 * @details   Construct a new SPI protocol for the USCI module.
 * @param     channel
 *                 The USCI channel this SPI is connected to.
 * @param     master_mode
 *                 If this SPI is a master or slave on the SPI bus.
 * @param     mode
 *                 The Mode of the SPI protocol.
 * @param     clock_source
 *                 The clock source used by the SPI.
 * @param     data_direction
 *                 The direction the data is clocked out of / into the SPI.
 * @param     character_length
 *                 The symbol length of the SPI data.
 * @param     clock_mode
 *                 The mode of the SPI clock.
 * @param     baud_rate
 *                 The value to save to the baud rate register.  The frequency
 *                 of the bit clock is \f$f_{BitClock}=\frac{f_{ClockSource}}{\texttt{baud_rate}}\f$
 */
Spi::Spi(UsciChannel::UsciChannel channel,
		SpiMasterMode::SpiMasterMode master_mode,
		SpiMode::SpiMode mode,
		SpiClockSource::SpiClockSource clock_source,
		SpiDataDirection::SpiDataDirection data_direction,
		SpiSymbolLength::SpiSymbolLength character_length,
		SpiClockMode::SpiClockMode clock_mode,
		unsigned short baud_rate)
	: Usci(channel)
{
	// put the USCI into reset mode
	SetUsciResetMode(true);
	// Set the control registers
	SetUsciControl0(clock_mode | data_direction | character_length | master_mode | mode | UsciSynchronousMode::Synchronous);
	SetUsciControl1(clock_source);
	// set the baud rate
	SetUsciBaud(baud_rate);

	// configure the pins and interrupts
	switch(channel)
	{
	case UsciChannel::USCIA:
		P1SEL |= BIT1 | BIT2 | BIT4;		// Set pins to SPI Mode
		P1SEL2 |= BIT1 | BIT2 | BIT4;		//
		if(SpiMode::SpiSlaveSsActiveHigh == mode || SpiMode::SpiSlaveSsActiveLow == mode)
		{
			P1SEL |= BIT5;					// set slave select mode
			P1SEL2 |= BIT5;					//
		}
		IFG2 &= ~(UCA0RXIFG | UCA0TXIFG);	// clear the interrupt flags
		IE2 |= UCA0RXIE | UCA0TXIE;			// enable interrupt
	case UsciChannel::USCIB:
		P1SEL |= BIT5 | BIT6 | BIT7;		// Set pins to SPI Mode
		P1SEL2 |= BIT5 | BIT6 | BIT7;		//
		if(SpiMode::SpiSlaveSsActiveHigh == mode || SpiMode::SpiSlaveSsActiveLow == mode)
		{
			P1SEL |= BIT4;					// set slave select mode
			P1SEL2 |= BIT4;					//
		}
		IFG2 & ~(UCB0RXIFG | UCB0TXIFG);	// clear the interrupt flags
		IE2 |= UCB0RXIE | UCB0TXIE;			// enable interrupts
	}

	// release USCI from reset mode
	SetUsciResetMode(false);
}

/**
 * Clean up resources used by SPI
 */
Spi::~Spi() {
	// TODO Auto-generated destructor stub
}

/**
static unsigned char byte_to_send;

void Spi::StartTransmission(unsigned char byte)
{
	Spi::isTransmissionDone = false;
	P1OUT &= (~BIT3); // Select Device
	byte_to_send = byte;
	UCA0TXBUF = byte_to_send; //buffer[0];// tlc_data.data[0];	// Send first byte
	return;
}*/

/**
 * @details   This callback is called each time the Tx buffer is ready to
 *            receive a new byte of data.  It calls the OnSendByte callback
 *            which determins if a new byte should be sent.  If no new byte
 *            should be sent the transmission finished flag is raised and the
 *            OnTransmissionDone callback is called.
 */
void Spi::OnSerialTx()
{
	unsigned char byte;
	if(this->OnSendByte(&byte))
	{
		SerialSendByte(byte);
	}
	else
	{
		isTransmissionDone = true;
		//this->OnTransmissionDone();
	}
//	static int i = 1;
//	if(i < 36*3+1)
//	{
//		_delay_cycles(100);
//		UCA0TXBUF = byte_to_send;//buffer[i];
//		i++;
//	}
//	else
//	{
//		IFG2 = 0;
//		_delay_cycles(100);
//		P1OUT |= (BIT3); // Unselect Device
//		i = 1;
//		isTransmissionDone = true;
//	}
}

/**
 * @details   This callback is called each time the Rx buffer receives a new
 *            byte of data.  It calls the OnRecieveByte callback passing the
 *            new data recieved.
 */
void Spi::OnSerialRx()
{
	unsigned char byte;
	byte = this->SerialReadByte();
	this->OnRecieveByte(byte);
}

} /* namespace ucube */

/// @}
