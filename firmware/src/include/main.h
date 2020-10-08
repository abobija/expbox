#ifndef MAIN_H
#define MAIN_H

#if(__FOSC__ != 8000 && __FOSC__ != 4000 && __FOSC__ != 2000)
    #error Choose another oscillator frequency. Supported ones are: 8MHz, 4MHz and 2MHz.
#endif

#include "defs.h"
#include "xtime.h"
#include "timer.h"
#include "buttons.h"
#include "display.h"

void interrupt();
void start_countdown();
void stop_countdown();
void one_sec_tick();
void button_up_handler();
void button_down_handler();
void button_start_stop_handler();

#endif