#include "xtime.h"

void xtime_inc(xTime *time) {
    if(++time->sec >= 60) {
        time->sec = 0;

        if(++time->min >= 60) {
            time->min = 0;
        }
    }
}

void xtime_dec(xTime *time) {
    if(--time->sec >= 60) {
        time->sec = 59;
        
        if(--time->min >= 60) {
            time->min = 59;
        }
    }
}

bool xtime_is_zero(xTime *time) {
    return time->min == 0 && time->sec == 0;
}