#include "buttons.h"

static uint8_t buttons_port at PORTB;

bool buttons_timer_overflow_flag = false;
static uint8_t buttons_timer_check_index = 0;
static uint8_t buttons_timer_checks[] = { 0x40, 0x80, 0xC0 };

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
    TRISB |= 0b00000111; // Set pins as input
    WPUB = 0b00000111;   // Enable weak pull-ups on pins
    OPTION_REG.B7 = 0;   // Enable weak pull-ups globaly
    
                         // TIMER1
                         // Timer1 is already set up by timer.c
                         // but if timer.c is not used in project
                         // next lines should be uncommented
                         
    //T1CON = 0b00000001;  // No prescaler; source: Fosc/4; enable tmr1
    //PIE1.TMR1IE = 1;     // Enable tmr1 overflow interrupt
    //INTCON.PEIE = 1;     // Enable peripheral interrupts for tmr1
    //TMR1H = TMR1L = 0;   // Reset tmr1
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
    bool confident_check = false;
    
    if(buttons_timer_overflow_flag) {
        buttons_timer_overflow_flag = false;
        confident_check = true;
        buttons_timer_check_index = 0;
    } else if(buttons_timer_check_index < sizeof(buttons_timer_checks)
              && BUTTONS_TIMER_VALUE >= buttons_timer_checks[buttons_timer_check_index]) {
        confident_check = true;
        buttons_timer_check_index++;
    }
    
    if(! confident_check) {
        return;
    }
    
    // debounce
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