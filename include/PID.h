#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

typedef struct 
{
	float Kp;
	float Ki;
	float Kd;

	float tau; // Derivative low-pass filter time constant

	// Output limits
	uint8_t limMin;
	uint8_t limMax;
	
	// Integrator limits
	uint8_t limMinInt;
	uint8_t limMaxInt;

	float T; // Sample time (in seconds)

	// Controller "memory"
	float integrator;
	uint8_t prevDeviation; // Required for integrator
	float differentiator;
	uint8_t prevMotorSpeed; // Required for differentiator

	uint8_t out; // Controller output

} PIDController;

void  PIDController_init(PIDController *pid);
uint8_t PIDController_update(PIDController *pid, uint8_t desiredSpeed, uint8_t motorSpeed);

#endif