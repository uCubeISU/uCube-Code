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
 * @file      SpiMaster.h
 *
 *  Created on: Apr 26, 2015
 *      Author: vens
 */

#ifndef SPIMASTER_H_
#define SPIMASTER_H_

#include "Spi.h"

namespace ucube {
using namespace ucube;

class SpiMaster : protected Spi{
public:
	SpiMaster(UsciChannel::UsciChannel channel,
			unsigned short baud_rate,
			SpiClockSource::SpiClockSource clock_source = SpiClockSource::Smclk,
			SpiClockMode::SpiClockMode clock_mode = SpiClockMode::IdleLowRisingEdge,
			SpiDataDirection::SpiDataDirection data_direction = SpiDataDirection::MsbFirst,
			SpiSymbolLength::SpiSymbolLength character_length = SpiSymbolLength::Length8Bit);
	~SpiMaster();

	bool OnSendByte(unsigned char * byte);

	void OnRecieveByte(unsigned char byte);
protected:

};

} /* namespace ucube */

#endif /* SPIMASTER_H_ */

/// @}

