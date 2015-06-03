#include <msp430.h> 

#include "Osc/Osc.h"
#include "SysClk/SysClk.h"
#include "CapTouch/CapTouch.h"


void MainLoop(unsigned long long time);

int main(void) {
    WDTCTL = WDTPW | WDTHOLD;	// Stop watchdog timer

    OscInit();
    SysClkInit(50, msec, MainLoop);
    CapTouchInit(10, msec);


    SysClkStart();
    while(1);
}

// This will be called every 50ms
void MainLoop(unsigned long long time)
{

}
