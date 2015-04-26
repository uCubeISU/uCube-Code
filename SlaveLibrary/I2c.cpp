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
 * @addtogroup I2C
 * @{
 * @file      I2c.cpp
 * @author    Iowa State University uCube team
 * @author    Andy Snawerdt
 * @author    Jeramie Vens
 * @author    Kris Burney
 * @date      Mar 28, 2015
 * @brief     I2C C file
 * @copyright Copyright (C) 2015 ISU uCube team
 * @details   This file contains the I2c constructor and methods including
 *            transmission and recieving in both master and slave mode.
 */


#include <msp430.h>
#include "I2c.h"

namespace ucube {
using namespace ucube;

int TxFlag = 0;

I2c::I2c() {
	// TODO Auto-generated constructor stub
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	P1SEL |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	P1SEL2|= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	UCB0CTL1 |= UCSWRST;                      // Enable SW reset
	UCB0CTL0 = UCMODE_3 + UCSYNC;     		  // I2C Master, synchronous mode
	UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
    UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
    UCB0BR1 = 0;

    this->RegisterSerialIsr(IsrSource::USCIB);
}

unsigned char volatile * I2c::ReceiveFrom(uint8_t slave_address, char *array, uint16_t latch, int length) //Left Justified
{
	mode = I2cMode::MASTER;
	RxTx = I2cRxTx::TX;
	UCB0CTL0 = UCMST;						  // Swap to Master Mode

	this->length = length;

	slave_addr = slave_address & 0xFE;
	UCB0I2CSA = slave_addr;                   // Slave Address Selected
	UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation

	UCB0CTL1 |= UCTR + UCTXSTT;               // I2C start condition

	IE2 |= UCB0TXIE;						  // Enable TX interrupt
	latch_addr = latch;
	UCB0TXBUF = latch_addr >> 8;			  // Sends latch address MSB

	buffer = array;
	flag = 0;
	bytesread = 0;
	TxFlag = 0;

	return &flag;
}

I2c::~I2c() {
	// TODO Auto-generated destructor stub
}

void I2c::OnSerialTx(IsrSource::SerialIsrSource source)
{
	switch (mode){
		case I2cMode::MASTER:
			switch (RxTx){
				case I2cRxTx::TX:
					if(TxFlag == 0)
					{
						UCB0TXBUF = latch_addr & 0x00FF;		  // Send the LSB of the latch location
						TxFlag++;
					}
					else if(TxFlag)
					{
						UCB0CTL1 |= UCTR + UCTXSTT;               // I2C start condition
						UCB0I2CSA = slave_addr | 0x01;            // Slave Address Selected
						IE2 &= ~UCB0TXIE;                         // Disable TX interrupt
						IE2 |= UCB0RXIE;                          // Enable RX interrupt
					}
				break;
			}
		break;
		case I2cMode::SLAVE:
			switch (RxTx){
				case I2cRxTx::TX:
					//TODO
				break;
			}
		break;
	}

}

void I2c::OnSerialRx(IsrSource::SerialIsrSource source)
{
	switch (mode){
			case I2cMode::MASTER:
				switch (RxTx){
					case I2cRxTx::RX:
						bytesread++;
						if(bytesread > this->length)
						{
							bytesread = 0;
							flag = 1;
							IE2 &= ~UCB0RXIE;                     // Disable RX interrupt
							UCB0CTL1 |= UCTXSTP;                  // I2C stop condition
						}
						*buffer++ = UCB0RXBUF;                    // Get RX data
					break;
				}
			break;
				case I2cMode::SLAVE:
					switch (RxTx){
						case I2cRxTx::RX:
							//TODO
						break;
					}
				break;

	}
}

} /* namespace ucube */

/// @}
