#include "main.h"
#include "display.h"

uint16_t tmr0_ticks = 0;
bool one_sec_flag = LOW;

void interrupt() {
    tmr0_ticks += TICKS_INCREMENTER;
    
    if(tmr0_ticks > ONE_SEC_TICKS) {
        tmr0_ticks -= ONE_SEC_TICKS;
        one_sec_flag = HIGH;
    }
    
    disp_tmr0_ofw_handler();
    
    INTCON.TMR0IF = 0;
}

void main() {
    ANSEL = 0x00;
    ANSELH = 0x00;

    TRISA = 0x00;
    PORTA = 0x00;
    TRISB = 0x00;
    PORTB = 0x00;

    OSCCON |= 0b01110000; // 8MHz INTOSC

    INTCON = 0b10100000;  // Interrupts: Global, TMR0
    OPTION_REG.T0CS = 0;  // TMR0 source: Fosc/4
    OPTION_REG.PSA = 1;   // No prescaler for TMR0

    TMR0 = 0;
    
    while(true) {
        if(one_sec_flag) {
            one_sec_flag = LOW;
        }
        
        disp_show();
    }
}