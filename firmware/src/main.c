#include "main.h"

static xTime time = { 0, 0 };
static xTime time_backup;
static bool countdown_running = false;

static sbit one_sec_led_tris at TRISB.B7;
static sbit one_sec_led at PORTB.B7;
static sbit exposure_light_tris at TRISB.B6;
static sbit exposure_light at PORTB.B6;
static sbit piezo_speaker_tris at TRISB.B5;
static sbit piezo_speaker at PORTB.B5;

void main() {
    // Set the internal oscillator frequency
#if(__FOSC__ == 8000)
    OSCCON |= 0x70; // 8 MHz
#elif(__FOSC__ == 4000)
    OSCCON |= 0x60; // 4 MHz
#elif(__FOSC__ == 2000)
    OSCCON |= 0x50; // 2 MHz
#endif

    INTCON = 0x00;  // Disable all interupts
    
    ANSEL = 0x00;   // All pins
    ANSELH = 0x00;  // are digital I/O

    one_sec_led_tris = 0;
    one_sec_led = OFF;
    
    exposure_light_tris = 0;
    exposure_light = OFF;

    piezo_speaker_tris = 0;
    piezo_speaker = OFF;

    read_time_from_eeprom();

    tmr_init();
    tmr_one_sec_callback = &one_sec_tick;
    
    buttons_init();
    buttons_up_callback = &button_up_handler;
    buttons_down_callback = &button_down_handler;
    buttons_start_stop_callback = &button_start_stop_handler;
    
    disp_init(&time);
    
    INTCON.GIE = 1; // Enable global interrupts
    
    while(true) {
        tmr_run();
        buttons_read();
        disp_show();
    }
}

void interrupt() {
    tmr_interrupt_handler();
    buttons_interrupt_handler();
    disp_interrupt_handler();
}

void start_countdown() {
    if(countdown_running || xtime_is_zero(&time))
        return;

    buttons_disable_up_down();
    save_time_to_eeprom();
    xtime_copy(&time, &time_backup);
    exposure_light = ON;
    countdown_running = true;
}

void stop_countdown() {
    if(! countdown_running)
        return;

    exposure_light = OFF;
    xtime_copy(&time_backup, &time);
    buttons_enable_up_down();
    countdown_running = false;
}

void one_sec_tick() {
    one_sec_led = ~one_sec_led;
   
    if(piezo_speaker) {
        piezo_speaker = OFF;
    }
   
    if(countdown_running) {
        if(xtime_is_zero(&time)) {
            stop_countdown();
            piezo_speaker = ON;
        } else {
            xtime_dec(&time);
        }
    }
}

void button_up_handler() {
    xtime_inc(&time);
}

void button_down_handler() {
    xtime_dec(&time);
}

void button_start_stop_handler() {
    if(countdown_running) {
        stop_countdown();
    } else {
        start_countdown();
    }
}

void save_time_to_eeprom() {
    EEPROM_Write(EEPROM_ADDR_MINUTES, time.min);
    EEPROM_Write(EEPROM_ADDR_SECONDS, time.sec);
}

void read_time_from_eeprom() {
    time.min = EEPROM_Read(EEPROM_ADDR_MINUTES);
    time.sec = EEPROM_Read(EEPROM_ADDR_SECONDS);
    
    if(time.min >= 60)
        time.min = 0;
        
    if(time.sec >= 60)
        time.sec = 0;
}