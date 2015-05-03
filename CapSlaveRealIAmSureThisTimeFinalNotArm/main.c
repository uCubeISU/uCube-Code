#include <msp430.h> 


volatile unsigned char value = 0;
volatile unsigned char buffer[36];

volatile unsigned char rxindex = 0;
volatile unsigned char txindex = 1;

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
	//UCA0BR0 |= 0x02;                          // /2
	//UCA0BR1 = 0;                              //
	//UCB0MCTL = 0;                             // No modulation
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	__enable_interrupt();
	IFG2 = 0;
	IE2 =  UCA0TXIE | UCA0RXIE;				 // enable interrupt
	UCA0TXBUF = buffer[0];


	while (1)
	{
	//	while(IFG2 & UCA0TXIFG == 0);
		//UCA0TXBUF = 0xCC;
		P2OUT ^= 0xC0;								// Toggle LED on and off
		_delay_cycles(1000000);
		if(P1IN & BIT5)
		{
			rxindex = 0;
			txindex = 1;
		}
	}
	return 0;
}


//volatile unsigned char index = 0;

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIA0RX_ISR(void)
{
	if(IFG2 & UCA0RXIFG)
	{
		buffer[rxindex] = UCA0RXBUF;
		rxindex = (rxindex+1)%36;
	}
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIA0TX_ISR(void)
{
	if(IFG2 & UCA0TXIFG)
	{
		UCA0TXBUF = buffer[txindex]; //UCA0RXBUF;
		txindex = (txindex+1)%36;
	}
}
