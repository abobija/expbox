#include "main.h"
#include "timer.h"
#include "buttons.h"
#include "display.h"

void main() {
    // Set the internal oscillator frequency
#if(__FOSC__ == 8000)
    OSCCON |= 0x70; // 8 MHz
#elif(__FOSC__ == 4000)
    OSCCON |= 0x60; // 4 MHz
#elif(__FOSC__ == 2000)
    OSCCON |= 0x50; // 2 MHz
#endif

    INTCON = 0x00;  // Disable all interupts
    
    ANSEL = 0x00;   // All pins
    ANSELH = 0x00;  // are digital I/O

    TRISB.B7 = 0;   // One second indication LED
    PORTB.B7 = 0;
    
    TRISB.B6 = 0;   // Button debug LED
    PORTB.B6 = 0;

    tmr_init();
    tmr_one_sec_callback = &one_sec_tick;
    
    buttons_init();
    buttons_up_callback = &button_up_handler;
    buttons_down_callback = &button_down_handler;
    buttons_start_stop_callback = &button_start_stop_handler;
    
    disp_init();
    
    INTCON.GIE = 1; // Enable global interrupts
    
    while(true) {
        tmr_run();
        buttons_read();
        disp_show();
    }
}

void interrupt() {
    tmr_interrupt_handler();
    buttons_interrupt_handler();
    disp_interrupt_handler();
}

void one_sec_tick() {
   PORTB.B7 = ~PORTB.B7;
}

void button_up_handler() {

}

void button_down_handler() {

}

void button_start_stop_handler() {
    PORTB.B6 = ~PORTB.B6;
}