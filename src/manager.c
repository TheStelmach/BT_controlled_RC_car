#include <stdio.h>
#include <stdlib.h>
#include "manager.h"
#include "UART.h"

Queue manageData()
{
    Queue task;
    task.command = UART_Receive();
    uint8_t value1 = UART_Receive();
    uint8_t value2 = UART_Receive();
    task.value = (value1*10) + value2;
    task.toExecute = 1;
    return task;
}

/*void update_queue(uint32_t data_buffer, uint8_t *queue[10])
{
    for (uint8_t i = 9; i >= 0; i--)
    {
        if (*queue[i] == 0 && *queue[(i-1)] != 0)
        {
            *queue[i] = data_buffer;
            return;
        }
        else
        {
            *queue[0] = 0;
            for(uint8_t e = 1; e <= 9; e++)
            {
                *queue[(e-1)] = *queue[e];
            }
            *queue[9] = data_buffer;
            return;
        }
    }
}*/

void printQueue (Queue task)
{
    UART_Transmit(task.command);
    UART_Flush();
    UART_Transmit(task.value);
    UART_Flush();
}