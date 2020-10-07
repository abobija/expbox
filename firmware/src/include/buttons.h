#ifndef BUTTONS_H
#define BUTTONS_H

#include "defs.h"

typedef struct {
    uint8_t pin;
    uint8_t confidence_lvl;
} Button;

#define buttons_interrupt_handler()\
    if(TMR2IF_bit) {\
        TMR2IF_bit = 0;\
    }

void buttons_init();

/*
 * This function should be called in infinity loop inside of main function
 */
void buttons_read();

#endif