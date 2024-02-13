#ifndef BDCDRV_H
#define BDCDRV_H

void bdc_init();
void bdcTurnLeft(uint8_t speed);
void bdcTurnRight(uint8_t speed);
void bdcCoast();
void bdcStop();

#endif