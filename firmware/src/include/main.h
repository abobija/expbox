#ifndef MAIN_H
#define MAIN_H

#if(__FOSC__ != 8000 && __FOSC__ != 4000 && __FOSC__ != 2000)
    #error Choose another oscillator frequency. Supported ones are: 8MHz, 4MHz and 2MHz.
#endif

#include "defs.h"

#endif