#ifndef SPEED_H
#define SPEED_H

// MOTOR ENCODER
#define INTERRUPT_PIN DDD3 // DRIVER ENABLE PIN A
#define INTERRUPT_PIN_ENABLE PD3 // PIN A OUTPUT

// WHEEL ENCODERS
#define LEFT_ENC DDC0
#define RIGHT_ENC DDC1

void speed_init();

void update_tachometer(int *motorSpeed, int millisec);
void front_wheels(float *leftWheelSpeed, float *rightWheelSpeed, int millisec);
void update_speedometer(float *actualSpeed, float leftWheelSpeed, float rightWheelSpeed);
float calculate_slip (float actualSpeed);

#endif