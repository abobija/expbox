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

#endif