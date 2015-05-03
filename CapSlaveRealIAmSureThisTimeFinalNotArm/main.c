#include <msp430.h>
#include "CapSens/CTS_Layer.h"
#include <stdint.h>

#define TRUNK_VALUE(x, min, max) (x = x < min ? min: x > max ? max : x)

/*
 * main.c
 */
int main(void) {
	WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	P2DIR = 0xFF;									// Initialize port 2 pin 6 to output
	P2SEL = 0;
	P2SEL2 = 0;
	P2OUT = 0;										// initializing the port pin to 0
	//__bis_SR_register(/*CPUOFF + */GIE);          // Enter LPM0 w/ interrupts
	P2OUT = 0x40;


	P1SEL = BIT1 | BIT2 | BIT4 | BIT5;	//Port 1 pin 5: System Clock pin 6: Serial in pin 7: Serial out
	P1SEL2 = BIT1 | BIT2 | BIT4 | BIT5;// Port 1 pin 5, pin 6, pin 7 UCA0CTL1 = UCSWRST;

	UCA0CTL0 |= UCCKPL + UCMSB + UCSYNC + 4;  // 4-pin, 8-bit SPI slave
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	__enable_interrupt();
	IFG2 = 0;
	IE2 =  UCA0TXIE | UCA0RXIE;				 // enable interrupt
	UCA0TXBUF = 0xCC;



	uint16_t cap_raw_value[16];
	uint8_t cap_value[5][5];
	int i, j;
	for(i=0;i<5;i++)for(j=0;j<5;j++)
		cap_value[i][j] = 0;










	while (1)
	{
		TI_CAPT_Raw(&sensor_1,cap_raw_value);

		/*Puts raw capacitive touch value into correct place in the 5x5 panel*/
		cap_value[0][0] = 255-((TRUNK_VALUE(cap_raw_value[0], 6000, 14191) - 6000) >> 5);
		cap_value[0][1] = 255-((TRUNK_VALUE(cap_raw_value[1], 6000, 14191) - 6000) >> 5);
		cap_value[0][2] = 255-((TRUNK_VALUE(cap_raw_value[2], 6000, 14191) - 6000) >> 5);
		cap_value[0][3] = 255-((TRUNK_VALUE(cap_raw_value[3], 6000, 14191) - 6000) >> 5);
		cap_value[0][4] = 255-((TRUNK_VALUE(cap_raw_value[4], 6000, 14191) - 6000) >> 5);
		cap_value[1][0] = 255-((TRUNK_VALUE(cap_raw_value[5], 6000, 14191) - 6000) >> 5);
		cap_value[1][1] = 255-((TRUNK_VALUE(cap_raw_value[6], 6000, 14191) - 6000) >> 5);
		cap_value[1][2] = 255-((TRUNK_VALUE(cap_raw_value[7], 6000, 14191) - 6000) >> 5);
		cap_value[1][3] = 255-((TRUNK_VALUE(cap_raw_value[8], 6000, 14191) - 6000) >> 5);
		cap_value[1][4] = 255-((TRUNK_VALUE(cap_raw_value[9], 6000, 14191) - 6000) >> 5);
		cap_value[2][1] = 255-((TRUNK_VALUE(cap_raw_value[10], 6000, 14191) - 6000) >> 5);
		cap_value[2][2] = 255-((TRUNK_VALUE(cap_raw_value[11], 6000, 14191) - 6000) >> 5);
		cap_value[2][3] = 255-((TRUNK_VALUE(cap_raw_value[12], 6000, 14191) - 6000) >> 5);
		cap_value[2][4] = 255-((TRUNK_VALUE(cap_raw_value[13], 6000, 14191) - 6000) >> 5);
		cap_value[3][3] = 255-((TRUNK_VALUE(cap_raw_value[14], 6000, 14191) - 6000) >> 5);
		cap_value[3][4] = 255-((TRUNK_VALUE(cap_raw_value[15], 6000, 14191) - 6000) >> 5);


		int x, y;
		for(i=0;i<5;i++){
			for(j=0;j<4;j++){
				if(cap_value[i][j] != 0 && cap_value[i][j+1]){
					x = ((j<<7) + 64 + (cap_value[i][j+1]>>2) - (cap_value[i][j]>>2));
				}
			}
		}

		for(i=0;i<4;i++){
			for(j=0;j<5;j++){
				if(cap_value[i][j] != 0 && cap_value[i+1][j]){
					y = ((i<<7) + 64 + (cap_value[i+1][j]>>2) - (cap_value[i][j]>>2));
				}
			}
		}

		P2OUT ^= 0xC0;								// Toggle LED on and off
		_delay_cycles(1000000);
	}
	return 0;
}


volatile unsigned char value = 0;
volatile unsigned char buffer[36];
//volatile unsigned char index = 0;

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIA0RX_ISR(void)
{
	static unsigned char index = 0;
	unsigned char tmp;
	if(IFG2 & UCA0RXIFG)
	{
		buffer[index] = UCA0RXBUF;
		index = (index+1)%36;
	}
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIA0TX_ISR(void)
{
	static unsigned char index = 1;
	if(IFG2 & UCA0TXIFG)
	{
		UCA0TXBUF = buffer[index]; //UCA0RXBUF;
		index = (index+1)%36;
	}
}
