// https://github.com/TheStelmach

#ifndef EXECUTER_H
#define EXECUTER_H

#define TICK 49999u// PERIOD OF 50ms

void sysTick_init();
void scheduler(uint16_t *millisec);
void execute(char *data);

#endif
