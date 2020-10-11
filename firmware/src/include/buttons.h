#ifndef BUTTONS_H
#define BUTTONS_H

#include "defs.h"

#define BUTTONS_TIMER_VALUE TMR1H

/*
 * If buttons timer overflow interrupt occurs every X[ms],
 * then debouncing time will be X * BUTTONS_ACCEPTABLE_CONFIDENCE_LVL [ms]
 */
#define BUTTONS_ACCEPTABLE_CONFIDENCE_LVL 4
#define BUTTONS_BURST_THRESHOLD 123

typedef struct {
    bool enabled;
    uint8_t pin;
    uint8_t confidence_lvl;
    bool is_pressed;
    bool is_burst_mode_enabled;
    uint8_t burst_delay_counter;
    void (**callback)();
} Button;

extern void (*buttons_up_callback)();
extern void (*buttons_down_callback)();
extern void (*buttons_start_stop_callback)();

extern bool buttons_timer_overflow_flag;

#define buttons_interrupt_handler() {\
        buttons_timer_overflow_flag = true;\
    }

void buttons_init();

void buttons_disable_up_down();
void buttons_enable_up_down();

/*
 * This function should be called in infinity loop inside of main function
 */
void buttons_read();

#endif