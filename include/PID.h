// https://github.com/TheStelmach

#ifndef PID_CONTROLLER_H
#define PID_CONTROLLER_H

typedef struct 
{
	float Kp;
	float Ki;
	float Kd;

	float tau; // DERIVATIVE LOW-PASS FILTER TIME CONSTANT

	int limMin;
	int limMax;
	
	int limMinInt;
	int limMaxInt;

	int T; // SAMPLE TIME

	float integrator;
	float prevDeviation;
	float differentiator;
	float prevMotorSpeed;
	int prevMillisec;

	int out;

} PIDController;

void  PIDController_init(PIDController *pid, int millisec);
int PIDController_update(PIDController *pid, int desiredSpeed, int motorSpeed, int millisec);

#endif