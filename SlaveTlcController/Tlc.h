/*
 * Tlc.h
 *
 *  Created on: Apr 28, 2015
 *      Author: vens
 */

#ifndef TLC_H_
#define TLC_H_

#include "SpiMaster.h"
#include "SpiDevice.h"

class Tlc: public ucube::SpiDevice {
public:
	Tlc(ucube::SpiMaster *spi_master);
	virtual ~Tlc();
private:

	struct pixle
	{
		unsigned red : 5;
		unsigned green : 6;
		unsigned blue : 5;
	};

	struct pixle frame[6][6];
};

#endif /* TLC_H_ */
