/*
 * PinInterrupt.h
 *
 *  Created on: May 2, 2015
 *      Author: vens
 */

#ifndef PININTERRUPT_H_
#define PININTERRUPT_H_

namespace ucube {

namespace PinInterruptSource{
	enum PinInterruptSource{
		HighToLow,
		LowToHigh,
		Both
	};
}

namespace PinInterruptPort{
	enum PinInterruptPort{
		Port1 = 1,
		Port2 = 2
	};
}

namespace PinInterruptPin{
	enum PinInterruptPin{
		Pin0 = 0,
		Pin1 = 1,
		Pin2 = 2,
		Pin3 = 3,
		Pin4 = 4,
		Pin5 = 5,
		Pin6 = 6,
		Pin7 = 7
	};
}


class PinInterrupt {
public:
	PinInterrupt();
	virtual ~PinInterrupt();

	typedef void (*PinInterruptCallback)(void* obj,
			ucube::PinInterruptPort::PininterruptPort port,
			ucube::PinInterruptPin::PinInterruptPin pin,
			ucube::PinInterruptSource::PinInterruptSource source);

	void RegisterCallback(ucube::PinInterruptPort::PinInterruptPort port,
			ucube::PinInterruptPin::PinInterruptPin pin,
			ucube::PinInterruptSource::PinInterruptSource source,
			PinInterruptCallback cb, void* obj);
protected:

private:
	struct Callback{
		PinInterruptCallback callback;
		void* object;
	};

	static ucube::PinInterrupt::Callback callbacks[2][8];
	friend void PORT1_ISR(void);
	friend void PORT2_ISR(void);

};

} /* namespace ucube */

#endif /* PININTERRUPT_H_ */
