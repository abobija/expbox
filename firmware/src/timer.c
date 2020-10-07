#include "timer.h"

uint16_t tmr_ticks = 0;
bool tmr_one_sec_flag = LOW;
void (*tmr_one_sec_callback)() = NULL;

void tmr_init() {
                        // TIMER1:
    T1CON = 0b00000001; // No prescaler; source: Fosc/4; enable tmr1
    PIE1.TMR1IE = 1;    // Enable tmr1 overflow interrupt
    INTCON.PEIE = 1;    // Enable peripheral interrupts for tmr1
    TMR1H = TMR1L = 0;  // Reset tmr1
}

void tmr_run() {
    if(tmr_one_sec_flag) {
        tmr_one_sec_flag = LOW;

        if(tmr_one_sec_callback) {
            tmr_one_sec_callback();
        }
    }
}