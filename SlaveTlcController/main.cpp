#include <msp430.h> 
#include "slave_lib.h"
#include "SpiDevice.h"

#define NUM_TLC 6
#define LEDS_PER_TLC 6

typedef union PIXEL_UNION
{
	struct PIXEL_STRUCT
	{
		unsigned red : 5;
		unsigned green : 6;
		unsigned blue : 5;
	}color;
	unsigned short value;
}pixel_t;

struct SPI_DATA_STRUCT
{
	pixel_t frame[NUM_TLC][LEDS_PER_TLC];
	shared_mem_t slave_data;
}data;

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    long m;
    //ucube::SpiBus tlc_bus;


	unsigned char i = 0;
    while(1)
	{
		//tlc_bus.StartTransmission(i);
		//while(!tlc_bus.IsTransmissionDone());
		P1OUT &= ~BIT5;  // release blank signal
		//BYTE_SEND += 1;
		//BYTE_SEND = 0xCC;
		i++;
		for(m=0; m<40000 ; m++);
	}
	while(1);


	return 0;
}
