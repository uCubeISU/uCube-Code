/*
 * SpiSlave.h
 *
 *  Created on: Apr 26, 2015
 *      Author: vens
 */

#ifndef SPISLAVE_H_
#define SPISLAVE_H_

#include "Spi.h"

namespace ucube {

class SpiSlave: protected ucube::Spi {
public:
	SpiSlave(UsciChannel::UsciChannel channel,
			SpiMode::SpiMode mode = SpiMode::SpiThreePinMode,
			SpiClockMode::SpiClockMode clock_mode = SpiClockMode::IdleLowRisingEdge,
			SpiDataDirection::SpiDataDirection data_direction = SpiDataDirection::MsbFirst,
			SpiCharacterLength::SpiCharacterLength character_length=SpiCharacterLength::Length8Bit);
	virtual ~SpiSlave();
};

} /* namespace ucube */

#endif /* SPISLAVE_H_ */
