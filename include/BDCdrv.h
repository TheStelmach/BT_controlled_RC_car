#ifndef BDCDRV_H
#define BDCDRV_H

#define A_ENABLE DDD4 // DRIVER ENABLE PIN A
#define A_EN_PIN PD4 // PIN A OUTPUT
#define B_ENABLE DDD7 // DRIVER ENABLE PIN B
#define B_EN_PIN PD7 // PIN B OUTPUT
#define A_PWM DDD5
#define B_PWM DDD6

void bdc_init();
void bdcTurnLeft(uint8_t speed);
void bdcTurnRight(uint8_t speed);
void bdcStop();

#endif