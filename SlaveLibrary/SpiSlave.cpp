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
 * @file      SpiSlave.cpp
 *
 *  Created on: Apr 26, 2015
 *      Author: vens
 */

#include "SpiSlave.h"

namespace ucube {

/**
 * @details   Create a new SPI slave protocol on the given channel
 * @param     channel
 *                 The USCI channel to attache to.
 * @param     mode
 *                 The slave select mode to use the SPI in.
 * @param     clock_mode
 *                 The clock mode that the SPI expects.
 * @param     data_direction
 *                 The direction the SPI data is shifted in/out.
 * @param     character_length
 *                 The number of bits each symbol is.
 */
SpiSlave::SpiSlave(UsciChannel::UsciChannel channel,
		SpiMode::SpiMode mode,
		SpiClockMode::SpiClockMode clock_mode,
		SpiDataDirection::SpiDataDirection data_direction,
		SpiSymbolLength::SpiSymbolLength character_length)
	: Spi(channel, SpiMasterMode::Slave, mode, SpiClockSource::Smclk, data_direction, character_length, clock_mode, 0)
{
/// @todo implement this
}

SpiSlave::~SpiSlave() {

}

/**
 * @details   This callback is called when the slave select line is asserted in
 *            four pin mode.
 */
void SpiSlave::OnSlaveSelected()
{

}

/**
 * @details   This callback is called when the slave select line is deserted in
 *            four pin mode.
 */
void SpiSlave::OnSlaveReleased()
{

}

} /* namespace ucube */

/// @}

