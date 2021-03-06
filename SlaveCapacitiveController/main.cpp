#include <msp430.h> 

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
    	UCA0TXBUF = 0xCC;


    	while (1)
    	{
    	//	while(IFG2 & UCA0TXIFG == 0);
    		//UCA0TXBUF = 0xCC;
    		P2OUT ^= 0xC0;								// Toggle LED on and off
    		_delay_cycles(1000000);
    	}
	return 0;
}

volatile unsigned char value = 0;

#pragma vector=USCIAB0RX_VECTOR
__interrupt void USCIA0RX_ISR(void)
{
	unsigned char tmp;
	if(IFG2 & UCA0RXIFG)
	{
		tmp = UCA0RXBUF;
		//while (!(IFG2 & UCA0TXIFG));
		//UCA0TXBUF = value;
		value = tmp;
	}
}

#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIA0TX_ISR(void)
{
	if(IFG2 & UCA0TXIFG)
	{
		UCA0TXBUF = value; //UCA0RXBUF;
	}
}
