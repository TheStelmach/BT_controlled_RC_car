#ifndef MANAGER_H
#define MANAGER_H

typedef struct queue
{
    uint8_t toExecute;
    unsigned char command;
    uint8_t value;
}Queue;

Queue manageData();
void printQueue (Queue task);

#endif

