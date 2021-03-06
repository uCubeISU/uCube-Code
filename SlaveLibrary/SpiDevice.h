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
 * @file      SpiDevice.h
 *
 *  Created on: Apr 28, 2015
 *      Author: vens
 */

#ifndef SPIDEVICE_H_
#define SPIDEVICE_H_

#include "SpiMaster.h"

namespace ucube {

class SpiDevice {
public:
	SpiDevice(ucube::SpiMaster *spi_master);
	virtual ~SpiDevice();

private:
	const ucube::SpiMaster * master;
};

} // namespace ucube
#endif /* SPIDEVICE_H_ */

/// @}

