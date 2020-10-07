#include "display.h"

/*  ---------------------------------------
 *  DISP: | . | g | f | e | d | c | b | a |
 *  ---------------------------------------
 *  PORT: | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 *  ---------------------------------------
 */
static uint8_t disp_nums[] = {
    0b00111111,
    0b00000110,
    0b01011011,
    0b01001111,
    0b01100110,
    0b01101101,
    0b01111101,
    0b00000111,
    0b01111111,
    0b01101111
};

static uint8_t disp_port at PORTC;

static sbit disp_mod_1 at PORTA.B0;
static sbit disp_mod_2 at PORTA.B1;
static sbit disp_mod_3 at PORTA.B2;
static sbit disp_mod_4 at PORTA.B3;

static uint8_t disp_min = 13;
static uint8_t disp_sec = 37;

bool disp_mux_flag = HIGH;

void disp_init() {
    TRISA &= 0xF0;       // <0:3> are outputs
    PORTA &= 0xF0;       // <0:3> off
    TRISC  = 0x00;
    PORTC  = 0x00;
                         // TIMER0:
    OPTION_REG.T0CS = 0; // TMR0 source: Fosc/4
    OPTION_REG.PSA = 0;  // Assign prescaler to tmr0
    
                         // Set prescaler
#if(__FOSC__ == 8000)
    OPTION_REG.PS2 = 0;  //
    OPTION_REG.PS1 = 1;  //
    OPTION_REG.PS0 = 1;  // 1:16
#elif(__FOSC__ == 4000)
    OPTION_REG.PS2 = 0;  //
    OPTION_REG.PS1 = 1;  //
    OPTION_REG.PS0 = 0;  // 1:8
#elif(__FOSC__ == 2000)
    OPTION_REG.PS2 = 0;  //
    OPTION_REG.PS1 = 0;  //
    OPTION_REG.PS0 = 1;  // 1:4
#endif

    TMR0 = 0;            // Reset tmr0
    INTCON.TMR0IE = 1;   // Enable tmr0 interrupt
}

void disp_show() {
    if(disp_mux_flag) {
        disp_mux_flag = LOW;
        disp_port = OFF;
        
        if(disp_mod_1) {
            disp_mod_1 = OFF;
            disp_mod_2 = ON;
        } else if(disp_mod_2) {
            disp_mod_2 = OFF;
            disp_mod_3 = ON;
        } else if(disp_mod_3) {
            disp_mod_3 = OFF;
            disp_mod_4 = ON;
        } else {
            disp_mod_4 = OFF;
            disp_mod_1 = ON;
        }
    }

    if(disp_mod_1) {
        disp_port = disp_nums[disp_min / 10];
    } else if(disp_mod_2) {
        disp_port = disp_nums[disp_min % 10];
    } else if(disp_mod_3) {
        disp_port = disp_nums[disp_sec / 10];
    } else if(disp_mod_4) {
        disp_port = disp_nums[disp_sec % 10];
    } else {
        disp_port = OFF;
    }
}