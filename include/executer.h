#ifndef EXECUTER_H
#define EXECUTER_H

#define TICK 19999u// PERIOD OF 20ms

void sysTick_init();
void scheduler(uint16_t *millisec);
void execute(char *data);

#endif