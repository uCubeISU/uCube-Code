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
 * @file      SpiSlave.h
 * @author    Jeramie Vens
 * @brief     A SPI slave USCI protocol
 */

#ifndef SPISLAVE_H_
#define SPISLAVE_H_

#include "Spi.h"
#include "PinInterrupt.h"
namespace ucube {

/**
 * A USCI channel used as an SPI slave device.
 */
class SpiSlave: protected ucube::Spi{
public:
	/// Create a new USCI SPI slave protocol on the given channel.
	SpiSlave(UsciChannel::UsciChannel channel,
			SpiMode::SpiMode mode = SpiMode::SpiThreePinMode,
			SpiClockMode::SpiClockMode clock_mode = SpiClockMode::IdleLowRisingEdge,
			SpiDataDirection::SpiDataDirection data_direction = SpiDataDirection::MsbFirst,
			SpiSymbolLength::SpiSymbolLength character_length=SpiSymbolLength::Length8Bit);
	/// Clean up resources used by the class.
	virtual ~SpiSlave();

	/**
	 * @name Callbacks
	 * @{
	 */
	/// Callback when the slave select line is asserted in four pin mode
	virtual void OnSlaveSelected();
	/// Callback when the slave select line is deserted in four pin mode
	virtual void OnSlaveReleased();
	/// @}
};



} /* namespace ucube */

#endif /* SPISLAVE_H_ */

/// @}

