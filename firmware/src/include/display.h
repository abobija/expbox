#ifndef DISPLAY_H
#define DISPLAY_H

#include "defs.h"

extern bool disp_mux_flag;

#define disp_interrupt_handler()\
    if(TMR0IF_bit) {\
        disp_mux_flag = HIGH;\
        TMR0IF_bit = LOW;\
    }
    
void disp_init();

/*
 * This function should be called in infinity loop inside of main function
 */
void disp_show();

#endif