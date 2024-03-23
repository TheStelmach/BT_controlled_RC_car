#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#define LEDPIN DDB5
#define LEDENABLE PB5

void periph_init();
void toggle_headlights();
void toggle_inbuilt_LED();

#endif