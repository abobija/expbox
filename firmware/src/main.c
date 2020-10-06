#include "main.h"
#include "display.h"

uint16_t tmr1_ticks = 0;
bool one_sec_flag = LOW;

void interrupt() {
    if(TMR1IF_bit) {
      tmr1_ticks += TICKS_INCREMENTER;

      if(tmr1_ticks > ONE_SEC_TICKS) {
          tmr1_ticks -= ONE_SEC_TICKS;
          one_sec_flag = HIGH;
      }

      TMR1IF_bit = LOW;
    }
    
    disp_interrupt_handler();
}

void main() {
    OSCCON |= 0b01110000; // 8MHz INTOSC
    INTCON = 0x00;        // Disable all interupts
    
    ANSEL = 0x00;         // All pins
    ANSELH = 0x00;        // are digital I/O

    TRISB = 0b00000111;
    PORTB = 0x00;

    disp_init();
    
                          // TIMER1:
    T1CON = 0b00000001;   // No prescaler; source: Fosc/4; enable tmr1
    PIE1.TMR1IE = 1;      // Enable tmr1 overflow interrupt
    INTCON.PEIE = 1;      // Enable peripheral interrupts for tmr1
    TMR1H = TMR1L = 0;    // Reset tmr1
    
    INTCON.GIE = 1;       // Enable global interrupts
    
    while(true) {
        if(one_sec_flag) {
            one_sec_flag = LOW;
            PORTB.B7 = ~PORTB.B7;
        }
        
        disp_show();
    }
}