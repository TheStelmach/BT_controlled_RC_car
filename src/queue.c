#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "queue.h"

void *queue_init()
{
    char *queue = (char*) malloc(QUEUELENGTH*sizeof(char));
    for (int i = 0; i < QUEUELENGTH; i++) queue[i] = 0;
    static uint8_t currQueue = 0;
}

uint8_t sendToQueue(uint8_t *currQueue, char newCommand, char *queue[])
{
    if (*currQueue < QUEUELENGTH)
    {
        *queue[*currQueue] = newCommand;
        *currQueue++;
        return 1;
    }

    else return 0;
}

char nextInQueue(uint8_t *currQueue, char *queue[])
{
    if (*currQueue == 0) return 0;

    else
    {
        *currQueue--;
        return *queue[*currQueue + 1];
    }
}

void flushQueue(char *queue[])
{
 for (int i = 0; i < QUEUELENGTH; i++) *queue[i] = 0;
}