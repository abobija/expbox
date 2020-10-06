#ifndef DISPLAY_H
#define DISPLAY_H

#include "defs.h"

/*
 * DISP_ONE_MUX_TICKS serves for tuning multiplexing rate.
 * Multiplexing is attached to the TIMER module which means 
 * that display module will be shifted every 
 * DISP_ONE_MUX_TICKS's of TIMER overflow.
 *
 * Ex: If TIMER overflow occurs every 128us, and DISP_ONE_MUX_TICKS is 15,
 *     in that case multiplexing rate will be 15 * 128us = 1.92ms
 */
#define DISP_ONE_MUX_TICKS 15

extern uint8_t disp_mux_ticks;
extern bool disp_mux_flag;

#define disp_interrupt_handler()\
    if(TMR0IF_bit) {\
        if(++disp_mux_ticks > DISP_ONE_MUX_TICKS) {\
            disp_mux_ticks = 0;\
            disp_mux_flag = HIGH;\
        }\
        \
        TMR0IF_bit = LOW;\
    }
    
void disp_init();

/*
 * This function should be called in infinity loop inside of main function
 */
void disp_show();

#endif