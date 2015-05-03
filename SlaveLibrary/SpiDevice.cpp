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
 * @file      SpiDevice.cpp
 *
 *  Created on: Apr 28, 2015
 *      Author: vens
 */

#include "SpiDevice.h"

namespace ucube {

SpiDevice::SpiDevice(ucube::SpiMaster *spi_master)
	: master(spi_master)
{
	// TODO Auto-generated constructor stub

}

SpiDevice::~SpiDevice() {
	// TODO Auto-generated destructor stub
}


} // namespace ucube
/// @}

