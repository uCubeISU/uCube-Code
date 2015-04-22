#include <msp430.h> 
#include "slave_lib.h"
#include "SpiBus.h"


/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    long m;
    ucube::SpiBus tlc_bus;


	unsigned char i = 0;
    while(1)
	{
		tlc_bus.StartTransmission(i);
		while(!tlc_bus.IsTransmissionDone);
		P1OUT &= ~BIT5;  // release blank signal
		//BYTE_SEND += 1;
		//BYTE_SEND = 0xCC;
		i++;
		for(m=0; m<40000 ; m++);
	}
	while(1);


	return 0;
}
