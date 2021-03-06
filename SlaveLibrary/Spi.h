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
 * @addtogroup     usci
 * @{
 * @addtogroup     SPI Serial Periphrial Interface
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

/// SPI clock modes
namespace SpiClockMode{
	/// The different possible SPI clock modes
	enum SpiClockMode{
		/// The SPI clock idles to low and latches in bits on the clocks falling edge.
		IdleLowFallingEdge = 0,
		/// The SPI clock idles to low and latches in bits on the clocks rising edge.
		IdleLowRisingEdge = BIT7,
		/// The SPI clock idles to high and latches in bits on the clocks rising edge.
		IdleHighRisingEdge = BIT6,
		/// The SPI clock idles to high and latches in bits on the clocks falling edge.
		IdleHighFallingEdge = BIT6 | BIT7
	};
}

/// SPI data directions
namespace SpiDataDirection{
	/// The posible directions for the SPI to operate in
	enum SpiDataDirection{
		/// Shift in/out data least significant bit first
		LsbFirst = 0,
		/// Shift in/out data most significant bit first
		MsbFirst = BIT5
	};
}

/// SPI symbol length
namespace SpiSymbolLength{
	/// The symbol length used by the SPI module
	enum SpiSymbolLength{
		/// A symbol is 8 bits long
		Length8Bit = 0,
		/// A symbol is 7 bits long
		Length7Bit = BIT4
	};
}

/// SPI master/slave mode
namespace SpiMasterMode{
	/// If the SPI is operating in master or slave mode
	enum SpiMasterMode{
		/// The SPI is operating in slave mode
		Slave = 0,
		/// The SPI is operating in master mode
		Master = BIT3
	};
}

/// SPI operating modes
namespace SpiMode{
	/// The mode the SPI is operating in
	enum SpiMode{
		/// Operate in three pin mode.  Slave select line is ignored.
		SpiThreePinMode = 0,
		/// Operate in four pin mode.  Device selected when slave select line high.
		SpiSlaveSsActiveHigh = BIT1,
		/// Operate in four pin mode.  Device selected when slave select line low.
		SpiSlaveSsActiveLow = BIT2
	};
}

/// SPI clock sources
namespace SpiClockSource{
	/// The posible clock sources for the SPI
	enum SpiClockSource{
		/// SPI clocked from the ACLK
		Aclk = BIT6,
		/// SPI clocked from the SMCLK
		Smclk = BIT7
	};
}

/**
 * Serial periphrial interface device.
 * @details   The Spi class represents a USCI used in SPI mode.
 */
class Spi : protected ucube::Usci
{
public:
	/// Create a new SPI protocol on the given channel.
	Spi(UsciChannel::UsciChannel channel,
			SpiMasterMode::SpiMasterMode master_mode,
			SpiMode::SpiMode mode,
			SpiClockSource::SpiClockSource clock_source,
			SpiDataDirection::SpiDataDirection data_direction,
			SpiSymbolLength::SpiSymbolLength character_length,
			SpiClockMode::SpiClockMode clock_mode,
			unsigned short baud_rate);
	/// Clean up resources used by the SPI
	virtual ~Spi();
	/// Start a transmission
	/// @todo make this better/remove
	void StartTransmission(unsigned char byte);
	/// Send a buffer of data on the SPI module.
	void SendBuffer(char const * buf, unsigned int size);
	/// Get if the previously started transmission is finished.
	bool IsTransmissionDone() {return Spi::isTransmissionDone;} ;

protected:

	/**
	 * Get the next byte to send on the SPI bus
	 * @param      byte
	 *                  Return the next byte to transmit
	 * @return     true to send next byte, false to end transmitting.
	 */

	virtual bool OnSendByte(unsigned char * byte) = 0;
	/**
	 * Handle the byte received from the SPI bus
	 * @param      byte
	 *                  The byte received
	 */
	virtual void OnRecieveByte(unsigned char byte) = 0;

private:
	void OnSerialRx();
	void OnSerialTx();
	volatile bool isTransmissionDone;
};

} /* namespace ucube */

#endif /* SPIBUS_H_ */

/// @}
/// @}

