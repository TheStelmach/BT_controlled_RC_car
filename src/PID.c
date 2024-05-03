#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#include "PID.h"

void PIDController_init(PIDController *pid) 
{
	pid->integrator = 0.0f;
	pid->prevDeviation  = 0.0f;
	pid->differentiator  = 0.0f;
	pid->prevMotorSpeed = 0.0f;
	pid->out = 0.0f;
}

uint8_t PIDController_update(PIDController *pid, uint16_t desiredSpeed, uint16_t motorSpeed) 
{
    uint16_t deviation = desiredSpeed - motorSpeed; // Deviation / error signal

    float proportional = pid->Kp * deviation; // Proportional

    pid->integrator += 0.5f * pid->Ki * pid->T * (deviation + pid->prevDeviation); // Integral

	// Anti-wind-up via integrator clamping
    if (pid->integrator > pid->limMaxInt) pid->integrator = pid->limMaxInt;
    else if (pid->integrator < pid->limMinInt) pid->integrator = pid->limMinInt;

	// Derivative (band-limited differentiator)	
    pid->differentiator = -(2.0f * pid->Kd * (motorSpeed - pid->prevMotorSpeed)
    + (2.0f * pid->tau - pid->T) * pid->differentiator) / (2.0f * pid->tau + pid->T);
    // Note: derivative on motorSpeed, therefore minus sign in front of equation!

    pid->out = proportional + pid->integrator + pid->differentiator; // Compute output and apply limits

    if (pid->out > pid->limMax) pid->out = pid->limMax;
    else if (pid->out < pid->limMin) pid->out = pid->limMin;

	// Store deviation and motorSpeed for the next iteration
    pid->prevDeviation = deviation;
    pid->prevMotorSpeed = motorSpeed;

    return (uint8_t)pid->out;
}