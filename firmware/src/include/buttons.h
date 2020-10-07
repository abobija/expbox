#ifndef BUTTONS_H
#define BUTTONS_H

#include "defs.h"

#define buttons_interrupt_handler() {};

void buttons_init();

/*
 * This function should be called in infinity loop inside of main function
 */
void buttons_scan();

#endif