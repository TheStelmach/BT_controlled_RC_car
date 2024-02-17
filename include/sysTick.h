#ifndef SYSTICK_H
#define SYSTICK_H

#define TICK 999u// PERIOD OF 1ms

void sysTick_init();
void scheduler(uint16_t *millisec);

#endif