# PCB Exposure Box [expbox]

This is repository of PCB Exposure Box [expbox] which uses PIC16F886 for it's brain and shows the time on display made up out of four seven-segment led modules.

Because display is made up out of 4 digits, I have decided to limit **maximum exposure time**, that can be set, to **1 hour** (**59m59s**). Even 1 hour is more than enough, because exposure process takes no more than maximum 10 to 15 minutes.

After the countdown comes to zero, finish of exposure process will be signalized with 1 second of high frequency tone.

### Demo

[![Making of Exposure Box ... *PCB diy*](https://img.youtube.com/vi/g0XoKE_xRvM/mqdefault.jpg)](https://www.youtube.com/watch?v=g0XoKE_xRvM)

## Microcontroller

Microcontroller used in this project is [**PIC16F886**](https://www.microchip.com/wwwproducts/en/PIC16F886) produced by [Microchip](https://www.microchip.com) company. This MCU has three timers and each timer is assigned to a separated task. **Timer0** is responsible for multiplexing four seven-segment led modules. **Timer1** is shared between tasks for precise time measuring and buttons debouncing. And last, but not least, **Timer2** is in charge of driving piezo speaker with **P**ulse **W**ide **M**odulated signal.

The controller uses an **internal oscillator** and it's set to maximum frequency of **8 MHz**.
