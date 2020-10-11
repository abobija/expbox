#ifndef MAIN_H
#define MAIN_H

/*#if(__FOSC__ != 8000 && __FOSC__ != 4000 && __FOSC__ != 2000)
    #error Choose another oscillator frequency. Supported ones are: 8MHz, 4MHz and 2MHz.
#endif*/

#if(__FOSC__ != 8000)
    #error Only 8MHz oscillator is supported.
#endif

#include "defs.h"
#include "xtime.h"
#include "timer.h"
#include "buttons.h"
#include "display.h"
#include "piezo.h"

#define EEPROM_ADDR_MINUTES 0x00
#define EEPROM_ADDR_SECONDS 0x01

void interrupt();
void start_countdown();
void stop_countdown();
void one_sec_tick();
void button_up_handler();
void button_down_handler();
void button_start_stop_handler();
void save_time_to_eeprom();
void read_time_from_eeprom();

#endif