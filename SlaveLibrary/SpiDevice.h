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
 * @file SpiBus.h
 * @author Sprog
 * @date Apr 21, 2015
 * @copyright GNU Public License v3
 * @brief
 * @details
 */

#ifndef SPIBUS_H_
#define SPIBUS_H_

#define RecordError(msg)

#include "Usci.h"

namespace ucube {


class SpiDevice : protected ucube::Usci
{
public:
	SpiDevice();
	virtual ~SpiDevice();
	void StartTransmission(unsigned char byte);
	void SendBuffer(char const * buf, unsigned int size);
	bool IsTransmissionDone() {return SpiDevice::isTransmissionDone;} ;

protected:

	/**
	 * Get the next byte to send on the SPI bus
	 * @param      out byte
	 *                  Return the next byte to transmit
	 * @return     true to send next byte, false to end trasmitting.
	 */

	virtual bool OnSendByte(unsigned char * byte) = 0;
	/**
	 * Handle the byte received from the SPI bus
	 * @param      The byte received
	 */
	virtual void OnRecieveByte(unsigned char byte) = 0;

private:
	void OnSerialRx(ucube::UsciChannel::UsciChannel source);
	void OnSerialTx(ucube::UsciChannel::UsciChannel source);
	volatile bool isTransmissionDone;
};

} /* namespace ucube */

#endif /* SPIBUS_H_ */

