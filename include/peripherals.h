// https://github.com/TheStelmach

#ifndef PERIPHERALS_H
#define PERIPHERALS_H

#define LEDPIN DDB5
#define LEDENABLE PB5

void periph_init();
void toggle_headlights();
void toggle_inbuilt_LED();
uint8_t read_encoder();
uint8_t calculate_speed();

#endif
