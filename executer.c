#include <avr/io.h>
#include <avr/interrupt.h>
#include "executer.h"
#include "BDCdrv.h"
#include "SERVOdrv.h"
#include "UART.h"


void sysTick_init()
{
    //INITIALIZE TIMER 2 IN CTC MODE
    // TCCR2A |= (1<<WGM21) | (1<<COM2A0);
    // TCCR2A &= (~(1<<WGM20)) & (~(1<<COM2A1));
    TCCR2A |= (1<<WGM21) | (1<<COM2A0) | (1<<COM2A1);
    TCCR2A &= (~(1<<WGM20)) & (~(1<<COM2B1)) & (~(1<<COM2B0));
    TCCR2B |= (1<<CS21);
    TCCR2B &= (~(1<<WGM22)) & (~(1<<CS20)) & (~(1<<CS22));

    OCR2A = TICK; // SHOULD BE 20ms

    SREG |= (1<<SREG_I); // GLOBAL INTERRUPT ENABLED
    TIMSK2 |= (1<<OCIE2A); // OUTPUT COMPARE MATCH INTERRUPT ENABLED
    TIFR2 |= (1<<OCF2A); // TIMER INTERRUPT FLAG REGISTER ENABLED

    //When the I-bit in SREG, OCIE2A (Timer/Counter2 compare match interrupt enable), 
    // and OCF2A are set (1), the Timer/Counter2 compare match interrupt is executed.

}

void scheduler(uint16_t *millisec)
{
    if (*millisec >= 60000) {*millisec = 0; return;} // RESTART SYSTEM TICK EVERY 5 MINUTES
    
    *millisec++; 
    return;
}

void execute(char *data)
{
    // EVERY BYTE IS A SEPARATE COMMAND, EXAMPLE AT THE BOTTOM
    char command = *data;
    switch (command)
    {
        default: angle_update(0, 'L'); break; 
        case 'q': UART_Transmit(*data); bdcTurnLeft(25); break;
        case 'w': UART_Transmit(*data); bdcTurnLeft(50); break;
        case 'e': UART_Transmit(*data); bdcTurnLeft(75); break;
        case 'r': UART_Transmit(*data); bdcTurnLeft(100); break;
        case 't': UART_Transmit(*data); bdcTurnLeft(125); break;
        case 'y': UART_Transmit(*data); bdcTurnLeft(150); break;  
        case 'u': UART_Transmit(*data); bdcTurnLeft(175); break;
        case 'i': UART_Transmit(*data); bdcTurnLeft(200); break;
        case 'o': UART_Transmit(*data); bdcTurnLeft(225); break;
        case 'p': UART_Transmit(*data); bdcTurnLeft(250); break;    

        case 'a': UART_Transmit(*data); bdcStop(); break;
        case 's': UART_Transmit(*data); bdcTurnRight(25); break;
        case 'd': UART_Transmit(*data); bdcTurnRight(50); break;
        case 'f': UART_Transmit(*data); bdcTurnRight(75); break;
        case 'g': UART_Transmit(*data); bdcTurnRight(100); break;
        case 'h': UART_Transmit(*data); bdcTurnRight(125); break;  
        case 'j': UART_Transmit(*data); bdcTurnRight(150); break;
        case 'k': UART_Transmit(*data); bdcTurnRight(175); break;
        case 'l': UART_Transmit(*data); bdcTurnRight(200); break; 

        case 'z': UART_Transmit(*data); angle_update(90, 'L'); break;
        case 'x': UART_Transmit(*data); angle_update(60, 'L'); break;
        case 'c': UART_Transmit(*data); angle_update(30, 'L'); break;
        case 'v': UART_Transmit(*data); angle_update(0, 'L'); break;
        case 'b': UART_Transmit(*data); angle_update(30, 'R'); break;
        case 'n': UART_Transmit(*data); angle_update(60, 'R'); break;  
        case 'm': UART_Transmit(*data); angle_update(90, 'R'); break;  
    }
    UART_Flush();
    data = 0;
}


/* EXAMPLE LOOKUP TABLE --- BYTES IN THE EXAMPLE RANDOMLY SELECTED!!!
00000000 = 0, do nothing
00000001 = 1, toggle pin 1
00000010 = 2, toggle pin 2
00000011 = 3, toggle pin 3
.
.
.
.
01000001 = A, forward speed 10%
01000010 = B, forward speed 20%
.
.
.
.
01110111 = w, reverse speed 30%
.
.
.
And so on
*/