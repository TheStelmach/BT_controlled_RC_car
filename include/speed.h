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

void update_tachometer(uint16_t *motorSpeed, uint16_t millisec);
void front_wheels(float *leftWheelSpeed, float *rightWheelSpeed, uint16_t millisec);
void update_speedometer(float *actualSpeed, float leftWheelSpeed, float rightWheelSpeed);
float calculate_slip (float actualSpeed);

#endif