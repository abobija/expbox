#include "buttons.h"

void buttons_init() {
    TRISB |= 0b00000111; // Set corresponding pins as input
    
                         // TIMER2:
    T2CON = 0b01111111;  // 1:16 prescaler; Tmr2 ON; 1:16 postscaler
    PIE1.TMR2IE = 1;     // Enable TMR2:PR2 match interrupt
    PR2 = 0xFF;          // Set Tmr2 threshold to max (255)
    TMR2 = 0;            // Reset Tmr2
}

void buttons_scan() {

}