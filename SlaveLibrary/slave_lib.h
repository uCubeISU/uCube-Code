/*
 * slave_lib.h
 *
 *  Created on: Apr 20, 2015
 *      Author: vens
 */

#ifndef SLAVE_LIB_H_
#define SLAVE_LIB_H_

#include <stdint.h>

typedef struct CAP_TOUCH_DATA_STRUCT
{
	unsigned short timestamp;
	unsigned short value;
}cap_touch_data_t;

typedef union SHARED_MEM_UNION
{
	struct SHARED_MEM_STRUCT
	{
		uint32_t system_time;				// 4 bytes
		cap_touch_data_t cap_touch_data[9];	// 36 bytes
		// 16 bytes free here

	}data;
	unsigned char raw_data[56];
}shared_mem_t;


#endif /* SLAVE_LIB_H_ */
