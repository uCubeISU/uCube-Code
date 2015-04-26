/*
 * SpiSlave.cpp
 *
 *  Created on: Apr 26, 2015
 *      Author: vens
 */

#include "SpiSlave.h"

namespace ucube {

SpiSlave::SpiSlave(UsciChannel::UsciChannel channel,
		SpiMode::SpiMode mode,
		SpiClockMode::SpiClockMode clock_mode,
		SpiDataDirection::SpiDataDirection data_direction,
		SpiCharacterLength::SpiCharacterLength character_length)
	: Spi(channel, SpiMasterMode::Slave, mode, SpiClockSource::Smclk, data_direction, character_length, clock_mode, 0)
{

}

SpiSlave::~SpiSlave() {

}

} /* namespace ucube */
