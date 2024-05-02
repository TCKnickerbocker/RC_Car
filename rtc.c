#include "newxc8_header.h"

// Setup periodic interrupts
void init_RTC(){
    while (RTC.STATUS > 0){;}
    // A liberal interrupt pace for reads from and writes to I2C peripherals:
    RTC.PER = 102; 

    RTC.CLKSEL = RTC_CLKSEL_INT32K_gc;
    RTC.DBGCTRL |= RTC_DBGRUN_bm;   
    // 32 prescaler, ran in standy mode
    RTC.CTRLA = RTC_PRESCALER_DIV32_gc  | RTC_RTCEN_bm  | RTC_RUNSTDBY_bm; 
    // Enable Overflow Interrupt 
    RTC.INTCTRL |= RTC_OVF_bm;
}


