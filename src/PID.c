// https://github.com/TheStelmach

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include <stdlib.h>

#include "PID.h"

void PIDController_init(PIDController *pid, int millisec) 
{
	pid->integrator = 0.0f;
	pid->prevDeviation  = 0;
	pid->differentiator  = 0.0f;
	pid->prevMotorSpeed = 0;
	pid->out = 0;
    pid->prevMillisec = millisec;
}

int PIDController_update(PIDController *pid, int desiredSpeed, int motorSpeed, int millisec) 
{
    int deviation = desiredSpeed - motorSpeed; // DEVIATION / ERROR SIGNAL
    pid->T = millisec - pid->prevMillisec;

    float proportional = pid->Kp * deviation; // PROPORTIONAL

    pid->integrator = 0.5f * (pid->Ki) * (pid->T / 1000) * (deviation + pid->prevDeviation); // INTEGRAL

    if ((pid->integrator) >= (pid->limMaxInt)) pid->integrator = pid->limMaxInt;
    else if ((pid->integrator) <= (pid->limMinInt)) pid->integrator = pid->limMinInt;

	// DERIVATIVE (BAND-LIMITED DIFERENTIATOR)	
    pid->differentiator = -(2.0f * pid->Kd * ((float)motorSpeed - ((float)(pid->prevMotorSpeed)))
    + ((2.0f * pid->tau) - (pid->T / 1000)) * pid->differentiator) / ((2.0f * pid->tau) + (pid->T / 1000));

    pid->out = proportional + pid->Ki * pid->integrator + pid->differentiator; // COMPUTE OUTPUT

	// STORE VALUES FOR THE NEXT ITERATION
    pid->prevDeviation = deviation;
    pid->prevMotorSpeed = motorSpeed;
    pid->prevMillisec = millisec;

    return pid->out;
}