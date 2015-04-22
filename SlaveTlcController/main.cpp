#include <msp430.h> 
#include "slave_lib.h"


/*
 * main.c
 */
int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer
	int i = test(12);
	return 0;
}
