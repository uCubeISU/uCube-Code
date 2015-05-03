#include <msp430.h> 
#include "slave_lib.h"
#include "SpiMaster.h"
#include "Tlc.h"

#define NUM_TLC 6
#define LEDS_PER_TLC 6

using namespace ucube;

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
    long m;
    //ucube::SpiBus tlc_bus;


    SpiMaster spi_bus(UsciChannel::USCIA,
    		1,
			SpiClockSource::Smclk,
			SpiClockMode::IdleLowRisingEdge,
			SpiDataDirection::MsbFirst,
			SpiSymbolLength::Length8Bit);

    Tlc tlcs(&spi_bus);

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
