#include "display.h"

/*  ---------------------------------------
 *  DISP: | . | g | f | e | d | c | b | a |
 *  ---------------------------------------
 *  PORT: | 7 | 6 | 5 | 4 | 3 | 2 | 1 | 0 |
 *  ---------------------------------------
 */
uint8_t disp_nums[] = {
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

uint8_t disp_port at PORTC;

sbit disp_mod_1 at PORTA.B0;
sbit disp_mod_2 at PORTA.B1;
sbit disp_mod_3 at PORTA.B2;
sbit disp_mod_4 at PORTA.B3;

uint8_t disp_min = 13;
uint8_t disp_sec = 37;

uint8_t disp_mux_ticks = 0;
bool disp_mux_flag = HIGH;

void disp_tmr0_ofw_handler() {
    if(++disp_mux_ticks > DISP_ONE_MUX_TICKS) {
        disp_mux_ticks = 0;
        disp_mux_flag = HIGH;
    }
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