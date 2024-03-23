#ifndef QUEUE_H
#define QUEUE_H

#define QUEUECAPACITY 10

void queue_init();
uint8_t queue_write (char data);
uint8_t queue_read (char *data);

#endif