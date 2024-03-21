#ifndef QUEUE_H
#define QUEUE_H
#define QUEUELENGTH 10

void *queue_init();
uint8_t sendToQueue(uint8_t *currQueue, char newCommand, char *queue[]);
char nextInQueue(uint8_t *currQueue, char *queue[]);
void flushQueue(char *queue[]);

#endif