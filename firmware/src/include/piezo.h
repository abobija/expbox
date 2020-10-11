#ifndef PIEZO_H
#define PIEZO_H

#include "defs.h"

extern bool piezo_is_on;

void piezo_init();
void piezo_on();
void piezo_off();

#endif