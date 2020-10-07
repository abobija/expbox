#include "buttons.h"

void buttons_init() {
    TRISB |= 0b00000111; // Set corresponding pins as input
}

void buttons_scan() {

}