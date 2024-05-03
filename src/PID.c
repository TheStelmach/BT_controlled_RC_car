#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#include "PID.h"

void PIDController_init(PIDController *pid) 
{
	pid->integrator = 0.0f;
	pid->prevDeviation  = 0;
	pid->differentiator  = 0.0f;
	pid->prevMotorSpeed = 0;
	pid->out = 0;
}

uint8_t PIDController_update(PIDController *pid, uint8_t desiredSpeed, uint8_t motorSpeed) 
{
    uint8_t deviation = desiredSpeed - motorSpeed; // Deviation / error signal

    float proportional = pid->Kp * deviation; // Proportional

    pid->integrator += 0.5f * (pid->Ki) * (pid->T) * (deviation + pid->prevDeviation); // Integral

	// Anti-wind-up via integrator clamping
    if ((pid->integrator) >= (pid->limMaxInt)) pid->integrator = pid->limMaxInt;
    else if ((pid->integrator) <= (pid->limMinInt)) pid->integrator = pid->limMinInt;

	// Derivative (band-limited differentiator)	
    pid->differentiator = -(2.0f * pid->Kd * ((float)motorSpeed - ((float)(pid->prevMotorSpeed)))
    + ((2.0f * pid->tau) - pid->T) * pid->differentiator) / ((2.0f * pid->tau) + pid->T);
    // Note: derivative on motorSpeed, therefore minus sign in front of equation!

    pid->out = (uint8_t)proportional + (uint8_t)pid->integrator + (uint8_t)pid->differentiator; // Compute output and apply limits

    if (pid->out > pid->limMax) pid->out = (uint8_t)pid->limMax;
    else if (pid->out < pid->limMin) pid->out = (uint8_t)pid->limMin;

	// Store deviation and motorSpeed for the next iteration
    pid->prevDeviation = deviation;
    pid->prevMotorSpeed = motorSpeed;

    return pid->out;
}