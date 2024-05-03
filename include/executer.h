#ifndef EXECUTER_H
#define EXECUTER_H

#define TICK 4999u// PERIOD OF 5ms

#define LEFTMIN 46
#define LEFTMAX 80
#define LEFTOFFSET 6
#define RIGHTMIN 13
#define RIGHTMAX 46
#define RIGHTOFFSET 3
#define FORWARDMIN 96
#define FORWARDMAX 112
#define FORWARDSPEEDLIMIT 1
#define REVERSEMIN 80
#define REVERSEMAX 96
#define REVERSESPEEDLIMIT 7

static char switchPID = 0, switchTraction = 0, switchLights = 0, switchObstacles = 0,
limitAccel = 0;

void sysTick_init();
void scheduler(uint16_t *millisec);
void execute(char *data, char *motorDirection, float *desiredSpeed);

void button_toggle(char *button);


#endif