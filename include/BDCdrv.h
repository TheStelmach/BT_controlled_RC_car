#ifndef BDCDRV_H
#define BDCDRV_H

#define A_ENABLE DDD4 // DRIVER ENABLE PIN A
#define B_ENABLE DDD7 // DRIVER ENABLE PIN B

void bdc_init();
void bdcTurnLeft(uint8_t speed);
void bdcTurnRight(uint8_t speed);
void bdcCoast();
void bdcStop();

#endif