#ifndef MAIN_H
#define MAIN_H

#define ONE_SEC_TICKS (__FOSC__ * 1e3 / 4)

typedef unsigned char uint8_t;
typedef unsigned long uint16_t;

#ifndef bool
#define bool uint8_t
#endif

#ifndef true
#define true 1
#endif

#ifndef false
#define false 0
#endif

#endif