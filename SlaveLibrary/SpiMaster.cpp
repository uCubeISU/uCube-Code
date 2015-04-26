/**
 * @addtogroup SPI
 * @{
 * @file      SpiMaster.cpp
 *
 *  Created on: Apr 26, 2015
 *      Author: vens
 */

#include <msp430.h>
#include "SpiMaster.h"

namespace ucube {
using namespace ucube;

SpiMaster::SpiMaster(UsciChannel::UsciChannel channel,
		unsigned short baud_rate,
		SpiClockSource::SpiClockSource clock_source,
		SpiClockMode::SpiClockMode clock_mode,
		SpiDataDirection::SpiDataDirection data_direction,
		SpiCharacterLength::SpiCharacterLength character_length)
	: Spi(channel,SpiMasterMode::Master, SpiMode::SpiThreePinMode, clock_source, data_direction, character_length, clock_mode, baud_rate)
{
	// SS
	P1OUT |= BIT3;							// XLAT Port 3 Pin 0
	P1DIR |= BIT3;							// XLAT PORT 3 Pin 0
	// Blank
	P1OUT |= BIT5;							// Port 2 pin 5
	P1DIR |= BIT5;							// Port 2 pin 5

	//UCA0CTL1 = UCSWRST;
	//	UCA0CTL0 |= UCCKPH + UCMSB + UCMST + UCSYNC;  // 3-pin, 8-bit SPI master
//		UCA0CTL1 |= UCSSEL_2;                     // SMCLK
//		UCA0BR0 |= 0x02;                          // /2
//		UCA0BR1 = 0;                              //
//		UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**


}

SpiMaster::~SpiMaster() {
	// TODO Auto-generated destructor stub
}

} /* namespace ucube */

/// @}

