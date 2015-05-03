#include <msp430.h> 
#include <stdint.h>
//#include <intrinsics.h>

volatile unsigned short values[24];
void start_transmition();
void led_to_buffer(void);
volatile unsigned char sending_done = 0;
volatile unsigned char data = 0xAA;
void pixel_print(uint16_t val, uint16_t val2, uint16_t val3);


volatile unsigned short val0, val1, val2, val3;

/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	
    int i=0,j=0,k=1, dir=1;
    long m = 0;

    P1OUT |= BIT3;				//XLAT Port 3 Pin 0
    P1DIR |= BIT3;				//XLAT PORT 3 Pin 0
    P1SEL = BIT1 | BIT2 | BIT4;	//Port 1 pin 5: System Clock pin 6: Serial in pin 7: Serial out
    P1SEL2 = BIT1 | BIT2 | BIT4;// Port 1 pin 5, pin 6, pin 7
    P1OUT |= BIT5;				// Port 2 pin 5
    P1DIR |= BIT5;				// Port 2 pin 5

    UCA0CTL1 = UCSWRST;
    UCA0CTL0 |= UCCKPL + UCMSB + UCMST + UCSYNC;  // 3-pin, 8-bit SPI master
	UCA0CTL1 |= UCSSEL_2;                     // SMCLK
	UCA0BR0 |= 0x04;                          // /2
	UCA0BR1 = 0;                              //
	//UCB0MCTL = 0;                             // No modulation
	UCA0CTL1 &= ~UCSWRST;                     // **Initialize USCI state machine**
	__enable_interrupt();
	IFG2 = 0;
	IE2 = 0x02;//UCB0TXIE;						  	// enable interrupt

    P1OUT &= ~BIT5;

    val0 = 0;//x0F00; // filler
    val1 = 0;//x0FFF; // blue
    val2 = 0x03FF; // green
    val3 = 0x0FFF; // red

	while(1)
	{
		start_transmition();
		while(!sending_done);
		sending_done = 0;
		_delay_cycles(5000);
		P1OUT |= (BIT3); // Unselect Device
		data ++;
		for(m=0; m<40000 ; m++);
	}
	while(1);

	return 0;
}

void start_transmition(void)
{
	P1OUT &= (~BIT3); // Select Device
	UCA0TXBUF = val0 >> 4;;// tlc_data.data[0];	// Send first byte
	return;
}


#pragma vector=USCIAB0TX_VECTOR
__interrupt void USCIA0TX_ISR(void)
{
	static int val_num = 1;
	static int i = 1;
	int color= 0;
	//unsigned char d = i & 0x01 ? (tlc_data.data[i] << 4) | ((tlc_data.data[i] >> 4) & 0x0F) : tlc_data.data[i];

	if(i==36*7)
	{

		IFG2 = 0;
		//_delay_cycles(500);
		sending_done = 1;
		//P1OUT |= (BIT3); // Unselect Device
		i = 1;
		val_num = 1;
		color ++;
		if(color == 3) color = 0;
	}
	else
	{
		_delay_cycles(500);

		switch(val_num)
		{
		case 0:
			UCA0TXBUF = val0 >> 4;
			break;
		case 1:
			UCA0TXBUF = (val0 << 4) | (val1 >> 8);
			break;
		case 2:
			UCA0TXBUF = val1;
			break;
		case 3:
			UCA0TXBUF = val2 >> 4;
			break;
		case 4:
			UCA0TXBUF = (val2 << 4) | (val3 >> 8);
			break;
		case 5:
			UCA0TXBUF = val3;
			break;
		}
		val_num = (val_num+1)%6;
		i++;
	}
}

void pixel_print(uint16_t val, uint16_t val2, uint16_t val3)
{
	unsigned char a;
	a = val >> 2*4;
	UCA0TXBUF = a;
	_delay_cycles(100);
	UCA0TXBUF = a;
	_delay_cycles(100);
	a = val2 >> 2*4;
	UCA0TXBUF = a;
	_delay_cycles(100);
	UCA0TXBUF = a;
	_delay_cycles(100);
	a = val3 >> 2*4;
	UCA0TXBUF = a;
	_delay_cycles(100);
	UCA0TXBUF = a;


}
