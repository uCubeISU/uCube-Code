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

I2c::I2c(uint8_t my_address)
	: Usci(UsciChannel::USCIB)
{
	// TODO Auto-generated constructor stub
	WDTCTL = WDTPW + WDTHOLD;                 // Stop WDT
	P1SEL |= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	P1SEL2|= BIT6 + BIT7;                     // Assign I2C pins to USCI_B0
	UCB0CTL1 |= UCSWRST;                      // Enable SW reset
	UCB0CTL0 = UCMODE_3 + UCSYNC;     		  // I2C Slave, synchronous mode
	UCB0CTL1 = UCSSEL_2 + UCSWRST;            // Use SMCLK, keep SW reset
    UCB0BR0 = 12;                             // fSCL = SMCLK/12 = ~100kHz
    UCB0BR1 = 0;
    UCB0I2COA = my_address;					  // Selects your device address
    mode = I2cMode::SLAVE;

}

unsigned char volatile * I2c::ReceiveFrom(uint8_t slave_address, char *array, uint16_t latch_address, int length) // LEFT JUSTIFIED
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
	latch_addr = latch_address;
	SerialSendByte(latch_addr >> 8);		  // Sends latch address MSB

	buffer = array;
	flag = 0;
	number_bytes = 0;
	TxFlag = 0;

	return &flag;
}

void I2c::TransmitTo(uint8_t slave_address, uint8_t data, uint16_t latch_address, int length)
{
	mode = I2cMode::MASTER;
	RxTx = I2cRxTx::TX;
	UCB0CTL0 = UCMST;						  // Swap to Master Mode

	slave_addr = slave_address & 0xFE;
	UCB0I2CSA = slave_addr;					  // Slave Address Selected
	UCB0CTL1 &= ~UCSWRST;                     // Clear SW reset, resume operation

	UCB0CTL1 |= UCTR + UCTXSTT;               // I2C start condition

	IE2 |= UCB0TXIE;						  // Enable TX interrupt
	latch_addr = latch_address;
	SerialSendByte(latch_addr >> 8);		  // Sends latch address MSB

	TxData = data;
	number_bytes = 0;
	flag = 1;
	TxFlag = 0;
}

void I2c::OnSerialTx()
{
	switch (mode){
		case I2cMode::MASTER:
			switch (RxTx){
				case I2cRxTx::TX:
					if(TxFlag)
					{

						if (flag == 1)
						{
							UCB0CTL1 |= UCTR + UCTXSTT;             // I2C start condition
							UCB0I2CSA = slave_addr | 0x01;          // Slave Address Selected
							flag++;
						}
						else if (flag == 2)
						{
							SerialSendByte(TxData);					// Send Data
							number_bytes++;
							if(number_bytes > this->length)
							{
								number_bytes = 0;
								UCB0CTL1 |= UCTXSTP;                // I2C stop condition
								IE2 &= ~UCB0TXIE;                   // Disable TX interrupt
								UCB0CTL0 &= ~UCMST;					// Swap to Slave Mode
								mode = I2cMode::SLAVE;
							}
						}
						else
						{
							IE2 &= ~UCB0TXIE;                       // Disable TX interrupt
							IE2 |= UCB0RXIE;                        // Enable RX interrupt
							RxTx = I2cRxTx::RX;						// Swap to RX mode
						}
					}
					else
					{
						SerialSendByte(latch_addr & 0x00FF);		// Send the LSB of the latch location
						TxFlag++;
					}
				break;
			}
		break;
		case I2cMode::SLAVE:
			//unsigned char byte;
			//SerialSendByte(byte);
		break;
	}

}

void I2c::OnSerialRx()
{
	switch (mode){
			case I2cMode::MASTER:
				switch (RxTx){
					case I2cRxTx::RX:
						number_bytes++;
						if(number_bytes > this->length)
						{
							number_bytes = 0;
							flag = 1;
							IE2 &= ~UCB0RXIE;                     // Disable RX interrupt
							UCB0CTL1 |= UCTXSTP;                  // I2C stop condition
							UCB0CTL0 &= ~UCMST;					  // Swap to Slave Mode
							mode = I2cMode::SLAVE;
						}
						*buffer++ = SerialReadByte();             // Get RX data
					break;
				}
			break;
				case I2cMode::SLAVE:
					//unsigned char byte;
					//byte = this->SerialReadByte();
				break;

	}
}

I2c::~I2c() {
	// TODO Auto-generated destructor stub
}

} /* namespace ucube */

/// @}
