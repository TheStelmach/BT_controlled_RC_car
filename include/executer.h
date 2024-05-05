// https://github.com/TheStelmach

#ifndef EXECUTER_H
#define EXECUTER_H

#define TICK 999u// PERIOD OF 1mSec

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
// VALUES TUNED FOR THE SPECIFIC CONTROLLER


void sysTick_init();
void sysTick(int *millisec);
void execute(char *data, char *motorDirection, float *desiredSpeed);
void button_toggle(char *button);


#endif