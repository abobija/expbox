#ifndef BUTTONS_H
#define BUTTONS_H

#include "defs.h"

/*
 * If buttons timer overflow interrupt occurs every X[ms],
 * then debouncing time will be X * BUTTONS_ACCEPTABLE_CONFIDENCE_LVL [ms]
 */
#define BUTTONS_ACCEPTABLE_CONFIDENCE_LVL 4

typedef struct {
    uint8_t pin;
    uint8_t confidence_lvl;
    bool is_pressed;
    void (**callback)();
} Button;

extern void (*buttons_up_callback)();
extern void (*buttons_down_callback)();
extern void (*buttons_start_stop_callback)();

extern bool buttons_confidence_check_flag;

#define buttons_interrupt_handler()\
    if(TMR2IF_bit) {\
        buttons_confidence_check_flag = HIGH;\
        TMR2IF_bit = 0;\
    }

void buttons_init();

/*
 * This function should be called in infinity loop inside of main function
 */
void buttons_read();

#endif