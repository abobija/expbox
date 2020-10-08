#include "buttons.h"

static uint8_t buttons_tris at TRISB;
static uint8_t buttons_port at PORTB;

bool buttons_confidence_check_flag = LOW;

void (*buttons_up_callback)() = NULL;
void (*buttons_down_callback)() = NULL;
void (*buttons_start_stop_callback)() = NULL;

static Button buttons[] = {
    { true, 0, 0, false, true, 0, &buttons_up_callback },
    { true, 1, 0, false, true, 0, &buttons_down_callback },
    { true, 2, 0, false, false, 0, &buttons_start_stop_callback }
};

static const uint8_t buttons_len = 3;

void buttons_init() {
    // Set corresponding pins as input
    buttons_tris |= 0b00000111;
    
                         // TIMER2:
                         // Set prescaler and enable Tmr2
#if(__FOSC__ == 8000)
    T2CON = 0b01111101;  // prescaler = 1:4; postscaler = 1:16
#elif(__FOSC__ == 4000)
    T2CON = 0b00111101;  // prescaler = 1:4; postscaler = 1:8
#elif(__FOSC__ == 2000)
    T2CON = 0b00011101;  // prescaler = 1:4; postscaler = 1:4
#endif

    INTCON.PEIE = 1;     // Enable peripheral interrupts for tmr2
    PIE1.TMR2IE = 1;     // Enable TMR2:PR2 match interrupt
    PR2 = 0xFF;          // Set Tmr2 threshold to max (255)
    TMR2 = 0;            // Reset Tmr2
}

void buttons_disable_up_down() {
    buttons[0].enabled = buttons[1].enabled = false;
}

void buttons_enable_up_down() {
    buttons[0].enabled = buttons[1].enabled = true;
}

void buttons_read() {
    uint8_t i;
    bool pin_is_low;
    
    if(buttons_confidence_check_flag) {
        buttons_confidence_check_flag = LOW;
        
        for(i = 0; i < buttons_len; i++) {
            if(! buttons[i].enabled)
                continue;

            pin_is_low = ! ((buttons_port >> buttons[i].pin) & 0x01);
            
            if(pin_is_low) {
                if(! buttons[i].is_pressed 
                    && ++buttons[i].confidence_lvl >= BUTTONS_ACCEPTABLE_CONFIDENCE_LVL) {
                    buttons[i].is_pressed = true;

                    if(*(buttons[i].callback)) {
                        (*(buttons[i].callback))();
                    }
                } else if(buttons[i].is_pressed && buttons[i].is_burst_mode_enabled) {
                    if(buttons[i].burst_delay_counter < BUTTONS_BURST_THRESHOLD) {
                        buttons[i].burst_delay_counter++;
                    } else {
                        if(*(buttons[i].callback)) {
                            (*(buttons[i].callback))();
                        }
                    }
                }
            } else {
                buttons[i].confidence_lvl = 0;
                buttons[i].burst_delay_counter = 0;
                buttons[i].is_pressed = false;
            }
        }
    }
}