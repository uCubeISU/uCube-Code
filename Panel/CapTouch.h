/*
 * CapTouch.h
 *
 *  Created on: Jun 1, 2015
 *      Author: vens
 */

#ifndef CAPTOUCH_H_
#define CAPTOUCH_H_

#ifndef NULL
#define NULL ((void *) 0)
#endif

/// @def The number of edges to detect
#define CAP_TOUCH_NUMBER_EDGES 1
/// @def Conversion from time to result
#define CAP_TIME_TO_RESULT(time) (time >> 8)

void CapTouchInit(unsigned short update_frequency);
void CapTouchRegisterOnUpdate(void volatile (*onUpdate)(unsigned char age));

/// The result from a capacitive touch sensor
struct CapTouchResult{
	/// The value where 0 is no touch and 255 is a full press
	unsigned char value;
	/// The timestamp of the oldest update to the sensor
	unsigned char age;
};

/// Array of all of the capacitance touch sensors results
extern struct CapTouchResult capTouch[5][5];



#endif /* CAPTOUCH_H_ */
