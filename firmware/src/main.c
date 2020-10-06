#include "main.h"
#include "display.h"

uint16_t tmr0_ticks = 0;
bool one_sec_flag = LOW;

void interrupt() {
    if(TMR0IF_bit) {
      tmr0_ticks += TICKS_INCREMENTER;

      if(tmr0_ticks > ONE_SEC_TICKS) {
          tmr0_ticks -= ONE_SEC_TICKS;
          one_sec_flag = HIGH;
      }

      disp_tmr0_ofw_handler();

      TMR0IF_bit = LOW;
    }
}

void main() {
    ANSEL = 0x00;         // All pins
    ANSELH = 0x00;        // are digital I/O

    TRISA = 0x00;
    PORTA = 0x00;
    TRISC = 0x00;
    PORTC = 0x00;

    OSCCON |= 0b01110000; // 8MHz INTOSC
    
    INTCON = 0x00;        // Disable all interupts

    OPTION_REG.T0CS = 0;  // TMR0 source: Fosc/4
    OPTION_REG.PSA = 1;   // No prescaler for tmr0
    TMR0 = 0;             // Reset tmr0
    INTCON.TMR0IE = 1;    // Enable tmr0 interrupt
    
    INTCON.GIE = 1;       // Enable global interrupts
    
    while(true) {
        if(one_sec_flag) {
            one_sec_flag = LOW;
        }
        
        disp_show();
    }
}