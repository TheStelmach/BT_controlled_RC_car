// https://github.com/TheStelmach

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "queue.h"

uint8_t QueueReadPtr;
uint8_t QueueWritePtr;
uint8_t QueueSize;

char QueueStorage[QUEUECAPACITY]; // DATA BUFFER FOR QUEUE

void queue_init()
{
    QueueReadPtr = 0;
    QueueWritePtr = 0;
    QueueSize = 0;
}

void queue_write (char data)
{
	if(QueueSize >= QUEUECAPACITY) return; // FAILURE
	else 
	{
		QueueStorage[QueueWritePtr++] = data; 
		if(QueueWritePtr >= QUEUECAPACITY) 
        	{
			QueueWritePtr = 0; 
		}
		QueueSize++; 
	}
    return; // SUCCESS
}

void queue_read (char *data)
{
    if(QueueSize > 0) 
    {
	    *data = QueueStorage[QueueReadPtr]; // COPY VALUE FROM QUEUE
		QueueStorage[QueueReadPtr] = 0; // DELETE THE VALUE
		++QueueReadPtr; // SHIFT THE POSITION IN THE QUEUE
	    if(QueueReadPtr >= QUEUECAPACITY) 
		{
		    QueueReadPtr = 0; 
	    }
	    QueueSize--; 
	    return; // SUCCESS 
	}

	else *data = 0; // FAILURE
}
