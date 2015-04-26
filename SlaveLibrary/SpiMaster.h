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
			SpiCharacterLength::SpiCharacterLength character_length = SpiCharacterLength::Length8Bit);
	~SpiMaster();
};

} /* namespace ucube */

#endif /* SPIMASTER_H_ */

/// @}

