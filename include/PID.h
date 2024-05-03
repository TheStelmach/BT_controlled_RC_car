#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

typedef struct 
{
	float Kp;
	float Ki;
	float Kd;

	float tau; // Derivative low-pass filter time constant

	// Output limits
	float limMin;
	float limMax;
	
	// Integrator limits
	float limMinInt;
	float limMaxInt;

	float T; // Sample time (in seconds)

	// Controller "memory"
	float integrator;
	uint16_t prevDeviation; // Required for integrator
	float differentiator;
	uint16_t prevMotorSpeed; // Required for differentiator

	uint16_t out; // Controller output

} PIDController;

void  PIDController_init(PIDController *pid);
uint8_t PIDController_update(PIDController *pid, uint16_t desiredSpeed, uint16_t motorSpeed);

#endif