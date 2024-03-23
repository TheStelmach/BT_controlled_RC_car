#ifndef EXECUTER_H
#define EXECUTER_H

#define TICK 4999u// PERIOD OF 5ms

void sysTick_init();
void scheduler(uint16_t *millisec);
void execute(char *data);

#endif