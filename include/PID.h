#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

typedef struct 
{
	float Kp;
	float Ki;
	float Kd;

	float tau; // Derivative low-pass filter time constant

	// Output limits
	int limMin;
	int limMax;
	
	// Integrator limits
	int limMinInt;
	int limMaxInt;

	int T; // Sample time (in seconds)

	// Controller "memory"
	float integrator;
	float prevDeviation; // Required for integrator
	float differentiator;
	float prevMotorSpeed; // Required for differentiator
	int prevMillisec;

	int out; // Controller output

} PIDController;

void  PIDController_init(PIDController *pid, int millisec);
int PIDController_update(PIDController *pid, int desiredSpeed, int motorSpeed, int millisec);

#endif