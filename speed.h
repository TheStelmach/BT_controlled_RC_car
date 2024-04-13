#ifndef SPEED_H
#define SPEED_H

#define TICK 49999u// TAKEN FROM EXECUTER_H

// MOTOR ENCODER
#define INTERRUPT_PIN DDD2 // DRIVER ENABLE PIN A
#define INTERRUPT_PIN_ENABLE PD4 // PIN A OUTPUT

// WHEEL ENCODERS
#define LEFT_ENC DDC0
#define RIGHT_ENC DDC1


void speed_init();

float update_tachometer(float *motorSpeed);
float update_speedometer(float *actualSpeed);
uint16_t how_many_micros_right_wheel();
uint16_t how_many_micros_left_wheel();
float calculate_slip (float actualSpeed);

#endif