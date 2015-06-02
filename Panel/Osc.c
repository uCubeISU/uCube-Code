/*
 * Osc.c
 *
 *  Created on: Jun 1, 2015
 *      Author: vens
 */

#include <msp430.h>

#define OSC_PASSWORD 0xA500

void OscInit()
{
	// SET THE PORT PINS FOR THE HFXOSC
	PJSEL0 |= BIT5 | BIT6;
	PJSEL1 &= ~(BIT5 | BIT6);
	// UNLOCK THE OSC REGISTERS
	CSCTL0 = OSC_PASSWORD;
	// ACLK=VLOCLK, SMCLK=HFXTCLK, MCLK=HFXTCLK
	CSCTL2 = 0x0155;
	// ACLK=/1, SMCLK=/1, MCLK=/1
	CSCTL3 = 0x0000;
	// HFXTDRIVE=LOWEST CURRENT, HFXTBYPASS=EXTERNAL CRYSTAL, HFFREQ=16MHz, HFXTOFF=ON
	// LFXTDRIVE=LOWEST CURRENT, LFXTBYPASS=EXTERNAL CYRSTAL, VLOOFF=ON, SMCLKOFF=ON, LFXTOFF=OFF
	CSCTL3 = 0x0801;
	// LOCK THE OSC REGISTERS
	CSCTL0_H = 0x00;
}