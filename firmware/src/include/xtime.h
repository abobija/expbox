#ifndef XTIME_H
#define XTIME_H

#include "defs.h"

typedef struct {
    uint8_t min;
    uint8_t sec;
} xTime;

void xtime_inc(xTime*);
void xtime_dec(xTime*);
bool xtime_is_zero(xTime*);
void xtime_copy(xTime*, xTime*);
bool xtime_is_same_as(xTime*, xTime*);

#endif