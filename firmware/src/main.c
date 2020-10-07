#include "main.h"
#include "timer.h"
#include "display.h"

void interrupt() {
    tmr_interrupt_handler();
    disp_interrupt_handler();
}

void main() {
    OSCCON |= 0b01110000; // 8MHz INTOSC
    INTCON = 0x00;        // Disable all interupts
    
    ANSEL = 0x00;         // All pins
    ANSELH = 0x00;        // are digital I/O

    TRISB = 0b00000111;
    PORTB = 0x00;

    tmr_init();
    disp_init();
    
    INTCON.GIE = 1;       // Enable global interrupts
    
    while(true) {
        tmr_run();
        disp_show();
    }
}