#include "piezo.h"

bool piezo_is_on = false;

void piezo_init() {
    TRISC.B2 = 0;
    PORTC.B2 = 0;
    PWM1_Init(9000); // Hz
    PWM1_Set_Duty(128); // 50%
    PWM1_Stop();
}

void piezo_on() {
    if(piezo_is_on)
        return;

    PWM1_Start();
    piezo_is_on = true;
}

void piezo_off() {
    if(! piezo_is_on)
        return;

    PWM1_Stop();
    piezo_is_on = false;
}