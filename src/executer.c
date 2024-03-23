#include <avr/io.h>
#include <avr/interrupt.h>
#include "executer.h"
#include "BDCdrv.h"
#include "SERVOdrv.h"
#include "UART.h"


void sysTick_init()
{
    //INITIALIZE TIMER 2 IN CTC MODE
    TCCR2A |= (1<<WGM21) | (1<<COM2A0);
    TCCR2A &= (~(1<<WGM20)) & (~(1<<COM2A1));
    TCCR2B |= (1<<CS21);
    TCCR2B &= (~(1<<WGM22)) & (~(1<<CS20)) & (~(1<<CS22));

    OCR2A = TICK; // SHOULD BE 5ms

    SREG |= (1<<SREG_I); // GLOBAL INTERRUPT ENABLED
    TIMSK2 |= (1<<OCIE2A); // OUTPUT COMPARE MATCH INTERRUPT ENABLED
    TIFR2 |= (1<<OCF2A); // TIMER INTERRUPT FLAG REGISTER ENABLED

    //When the I-bit in SREG, OCIE2A (Timer/Counter2 compare match interrupt enable), 
    // and OCF2A are set (one), the Timer/Counter2 compare match interrupt is executed.

}

void scheduler(uint16_t *millisec)
{
    *millisec++;
    // CHECK ABSOLUTE ENCODER, LIDAR, ENCODER AGAIN, CALCULATE SPEED AND MAKE A DECISION IF NEEDED
    
    if (*millisec >= 60000) {*millisec = 0; return;} // RESTART SYSTEM TICK EVERY 5 MINUTES
    else return;
}

void execute(char *data)
{
    // EVERY BYTE IS A SEPARATE COMMAND, EXAMPLE AT THE BOTTOM
    char command = *data;
    switch (command)
    {
        default: angle_update(0, 'L'); bdcStop(); break; 
        case 'Q': bdcTurnLeft(25); break;
        case 'W': bdcTurnLeft(50); break;
        case 'E': bdcTurnLeft(75); break;
        case 'R': bdcTurnLeft(100); break;
        case 'T': bdcTurnLeft(125); break;
        case 'Y': bdcTurnLeft(150); break;  
        case 'U': bdcTurnLeft(175); break;
        case 'I': bdcTurnLeft(200); break;
        case 'O': bdcTurnLeft(225); break;
        case 'P': bdcTurnLeft(250); break;    

        case 'A': bdcStop(); break;
        case 'S': bdcTurnRight(25); break;
        case 'D': bdcTurnRight(50); break;
        case 'F': bdcTurnRight(75); break;
        case 'G': bdcTurnRight(100); break;
        case 'H': bdcTurnRight(125); break;  
        case 'J': bdcTurnRight(150); break;
        case 'K': bdcTurnRight(175); break;
        case 'L': bdcTurnRight(200); break; 

        case 'Z': angle_update(90, 'L'); break;
        case 'X': angle_update(60, 'L'); break;
        case 'C': angle_update(30, 'L'); break;
        case 'V': angle_update(0, 'L'); break;
        case 'B': angle_update(30, 'R'); break;
        case 'N': angle_update(60, 'R'); break;  
        case 'M': angle_update(90, 'R'); break;  
    }

    data = 0;
}


/*
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