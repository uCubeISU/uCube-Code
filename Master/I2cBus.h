/*
 * I2cBus.h
 *
 *  Created on: Apr 20, 2015
 *      Author: vens
 */

#ifndef I2CBUS_H_
#define I2CBUS_H_

namespace ucube {

class I2cBus {
public:
	I2cBus(uint32_t base_addr);
	virtual ~I2cBus();
private:
	uint32_t base_addr;
};

} /* namespace ucube */

#endif /* I2CBUS_H_ */
