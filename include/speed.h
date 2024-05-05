// https://github.com/TheStelmach

#ifndef SPEED_H
#define SPEED_H

// MOTOR ENCODER
#define INTERRUPT1_PIN DDD3 // DRIVER ENABLE PIN A
#define INTERRUPT1_PIN_ENABLE PD3 // PIN A OUTPUT

// WHEEL ENCODERS
#define INTERRUPT0_PIN DDD2 // DRIVER ENABLE PIN A
#define INTERRUPT0_PIN_ENABLE PD2 // PIN A OUTPUT

void speed_init();

void update_tachometer(int *motorSpeed, int millisec);
void front_wheels(int *leftWheelSpeed, int *rightWheelSpeed, int millisec);
int update_speedometer(int leftWheelSpeed, int rightWheelSpeed);
float calculate_slip (int actualSpeed, int motorSpeed);

#endif