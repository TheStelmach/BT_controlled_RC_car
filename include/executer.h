#ifndef EXECUTER_H
#define EXECUTER_H

#define TICK 49999u// PERIOD OF 50ms

void sysTick_init();
void scheduler(uint16_t *millisec);
void execute(char *data);

void buttonA();
void buttonB();
void buttonX();
void buttonY();
void leftShoulder();
void rightShoulder();
void leftTrigger();
void rightTrigger();
void padLeft();
void padRight();
void padUp();
void padDown();

#endif