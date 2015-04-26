/**
 * @addtogroup     usci
 * @{
 * @addtogroup     SPI
 * @{
 * @file      Spi.h
 * @author    Jeramie Vens
 * @date      April 25, 2015: Created
 * @brief     SPI serial protocol of USCI
 */

#ifndef SPIBUS_H_
#define SPIBUS_H_

/// @todo add RecordError define
#define RecordError(msg)

#include <msp430.h>
#include "Usci.h"

namespace ucube {

namespace SpiClockMode{
	enum SpiClockMode{
		IdleLowFallingEdge = 0,
		IdleLowRisingEdge = BIT7,
		IdleHighRisingEdge = BIT6,
		IdleHighFallingEdge = BIT6 | BIT7
	};
}

namespace SpiDataDirection{
	enum SpiDataDirection{
		LsbFirst = 0,
		MsbFirst = BIT5
	};
}

namespace SpiCharacterLength{
	enum SpiCharacterLength{
		Length8Bit = 0,
		Length7Bit = BIT4
	};
}

namespace SpiMasterMode{
	enum SpiMasterMode{
		Slave = 0,
		Master = BIT3
	};
}

namespace SpiMode{
	enum SpiMode{
		SpiThreePinMode = 0,
		SpiSlaveSsActiveHigh = BIT1,
		SpiSlaveSsActiveLow = BIT2
	};
}

namespace SpiClockSource{
	enum SpiClockSource{
		Aclk = BIT6,
		Smclk = BIT7
	};
}

class Spi : protected ucube::Usci
{
public:
	Spi(UsciChannel::UsciChannel channel,
			SpiMasterMode::SpiMasterMode master_mode,
			SpiMode::SpiMode mode,
			SpiClockSource::SpiClockSource clock_source,
			SpiDataDirection::SpiDataDirection data_direction,
			SpiCharacterLength::SpiCharacterLength character_length,
			SpiClockMode::SpiClockMode clock_mode,
			unsigned short baud_rate);
	virtual ~Spi();
	void StartTransmission(unsigned char byte);
	void SendBuffer(char const * buf, unsigned int size);
	bool IsTransmissionDone() {return Spi::isTransmissionDone;} ;

protected:

	/**
	 * Get the next byte to send on the SPI bus
	 * @param      out byte
	 *                  Return the next byte to transmit
	 * @return     true to send next byte, false to end transmitting.
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

/// @}
/// @}

