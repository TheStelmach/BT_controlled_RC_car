#ifndef SYSTICK_H
#define SYSTICK_H

#define TICK 4999u// PERIOD OF 5ms

void sysTick_init();
void scheduler(uint16_t *millisec);

#endif