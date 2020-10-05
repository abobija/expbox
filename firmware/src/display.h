#ifndef DISPLAY_H
#define DISPLAY_H

#include "defs.h"

/*
 * DISP_ONE_MUX_TICKS serves for tuning multiplexing rate.
 * Multiplexing is attached to the Timer0 which means that display module
 * will be shifted every DISP_ONE_MUX_TICKS's of Timer0 overflow.
 *
 * Ex: If Timer0 overflow occurs every 128us, and DISP_ONE_MUX_TICKS is 15,
 *     in that case multiplexing rate will be 15 * 128us = 1.92ms
 */
#define DISP_ONE_MUX_TICKS 15

extern uint8_t disp_nums[];
extern uint8_t disp_port;
extern sbit disp_mod_1;
extern sbit disp_mod_2;
extern sbit disp_mod_3;
extern sbit disp_mod_4;
extern uint8_t disp_min;
extern uint8_t disp_sec;
extern uint8_t disp_mux_ticks;
extern bool disp_mux_flag;

/*
 * This function should be called in TMR0 overflow interrupt
 */
void disp_tmr0_ofw_handler();

/*
 * This function should be called in infinity loop inside of main function
 */
void disp_show();

#endif