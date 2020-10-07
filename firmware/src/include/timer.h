#ifndef TIMER_H
#define TIMER_H

#include "defs.h"

#define TMR_TICKS_INCREMENTER 2048

/*
 * TMR_ONE_SEC_TICKS = ((__FOSC__ * 1e3) / 4) / (65536 / TICKS_INCREMENT)
 */
#if(__FOSC__ == 8000)
    #define TMR_ONE_SEC_TICKS 62500
#elif(__FOSC__ == 4000)
    #define TMR_ONE_SEC_TICKS 31250
#elif(__FOSC__ == 2000)
    #define TMR_ONE_SEC_TICKS 15625
#endif

extern uint16_t tmr_ticks;
extern bool tmr_one_sec_flag;
extern void (*tmr_one_sec_callback)();

#define tmr_interrupt_handler()\
    if(TMR1IF_bit) {\
      tmr_ticks += TMR_TICKS_INCREMENTER;\
      \
      if(tmr_ticks > TMR_ONE_SEC_TICKS) {\
          tmr_ticks -= TMR_ONE_SEC_TICKS;\
          tmr_one_sec_flag = HIGH;\
      }\
      \
      TMR1IF_bit = LOW;\
    }

void tmr_init();

/*
 * This function should be called in infinity loop inside of main function
 */
void tmr_run();

#endif