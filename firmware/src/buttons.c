#include "buttons.h"

void buttons_init() {
    TRISB |= 0b00000111; // Set corresponding pins as input
    
                         // TIMER2:
                         // Set prescaler and enable Tmr2
#if(__FOSC__ == 8000)
    T2CON = 0b01111111;  // prescaler = 1:16; postscaler = 1:16
#elif(__FOSC__ == 4000)
    T2CON = 0b00111111;  // prescaler = 1:16; postscaler = 1:8
#elif(__FOSC__ == 2000)
    T2CON = 0b00011111;  // prescaler = 1:16; postscaler = 1:4
#endif

    INTCON.PEIE = 1;     // Enable peripheral interrupts for tmr2
    PIE1.TMR2IE = 1;     // Enable TMR2:PR2 match interrupt
    PR2 = 0xFF;          // Set Tmr2 threshold to max (255)
    TMR2 = 0;            // Reset Tmr2
}

void buttons_read() {

}