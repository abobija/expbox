#include "main.h"
#include "timer.h"
#include "buttons.h"
#include "display.h"

void interrupt() {
    tmr_interrupt_handler();
    buttons_interrupt_handler();
    disp_interrupt_handler();
}

void main() {
    OSCCON |= 0x70; // 8MHz INTOSC
    INTCON = 0x00;  // Disable all interupts
    
    ANSEL = 0x00;   // All pins
    ANSELH = 0x00;  // are digital I/O

    TRISB.B7 = 0;   // One second indication LED
    PORTB.B7 = 0;

    tmr_init();
    buttons_init();
    disp_init();
    
    INTCON.GIE = 1; // Enable global interrupts
    
    while(true) {
        tmr_run();
        buttons_scan();
        disp_show();
    }
}