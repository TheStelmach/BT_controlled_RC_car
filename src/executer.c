#include <avr/io.h>
#include <avr/interrupt.h>
#include "executer.h"
#include "BDCdrv.h"
#include "SERVOdrv.h"
#include "UART.h"
#include "peripherals.h"

static char buttonA = 0, buttonB = 0, buttonX = 0, buttonY = 0, leftShoulder = 0, rightShoulder = 0, 
leftTrigger = 0, rightTrigger = 0, padLeft = 0, padRight = 0, padUp = 0, padDown = 0;

void sysTick_init()
{
    //INITIALIZE TIMER 2 IN CTC MODE
    // TCCR2A |= (1<<WGM21) | (1<<COM2A0);
    // TCCR2A &= (~(1<<WGM20)) & (~(1<<COM2A1));
    TCCR2A |= (1<<WGM21) | (1<<COM2A0);
    TCCR2A &= (~(1<<WGM20)) & (~(1<<COM2B1)) & (~(1<<COM2B0)) & (~(1<<COM2A1));
    TCCR2B |= (1<<CS21);
    TCCR2B &= (~(1<<WGM22)) & (~(1<<CS20)) & (~(1<<CS22));

    OCR2A = TICK;

    SREG |= (1<<SREG_I); // GLOBAL INTERRUPT ENABLED
    TIMSK2 |= (1<<OCIE2A); // OUTPUT COMPARE MATCH INTERRUPT ENABLED
    TIFR2 |= (1<<OCF2A); // TIMER INTERRUPT FLAG REGISTER ENABLED

    //When the I-bit in SREG, OCIE2A (Timer/Counter2 compare match interrupt enable), 
    // and OCF2A are set (1), the Timer/Counter2 compare match interrupt is executed.

}

void scheduler(uint16_t *millisec)
{
    if ((*millisec) >= 60000) {*millisec = 0; return;} // RESTART SYSTEM TICK WHEN VALUE GETS CLOSE TO OVERFLOWING THE 16 BIT INTEGER
    
    (*millisec)++; 
    return;
}

void execute(char *data)
{
    // EVERY BYTE IS A SEPARATE COMMAND, EXAMPLE AT THE BOTTOM
    char command = *data;
    if (command > 0 && command <= 12)
    {
        switch (command)
        { 
            case 1: button_toggle(&buttonA); break;
            case 2: button_toggle(&buttonB); break;
            case 3: button_toggle(&buttonX); break;
            case 4: button_toggle(&buttonY); break;
            case 5: button_toggle(&leftShoulder); break;
            case 6: button_toggle(&rightShoulder); break;
            case 7: button_toggle(&leftTrigger); break;
            case 8: button_toggle(&rightTrigger); break;
            case 9: button_toggle(&padLeft); break;
            case 10: button_toggle(&padRight); break;
            case 11: button_toggle(&padUp); break;  
            case 12: button_toggle(&padDown); break; 
            default: break;
        }
    }

    else if (command >= RIGHTMIN && command < RIGHTMAX) // Left joystick left (LX)
    {
        if (command < (RIGHTMIN + RIGHTOFFSET)) command = (RIGHTMIN + RIGHTOFFSET);
        uint16_t angle = ((90/32.0)*(45 - command));
        angle_update(angle, 'R');
    }

    else if (command == LEFTMIN) angle_update(0, 'R');

    else if (command > LEFTMIN && command < LEFTMAX) // Left joystick right (LX)
    {
        if (command > (LEFTMAX - LEFTOFFSET)) command = (LEFTMAX - LEFTOFFSET);
        uint16_t angle = (90/32.0)*(command - 44);
        angle_update(angle, 'L');
    }

    else if (command >= REVERSEMIN && command < REVERSEMAX) // Right joystick down (RX)
    {
        if (command < REVERSEMIN + REVERSESPEEDLIMIT) command = (REVERSEMIN + REVERSESPEEDLIMIT);
        uint8_t speed = (255/16)*(FORWARDMIN - command);
        bdcTurnRight(speed);
    }    

    else if (command == FORWARDMIN) bdcStop();

    else if (command > FORWARDMIN && command < FORWARDMAX) // Right joystick up (RX)
    {
        if (command > (FORWARDMAX - FORWARDSPEEDLIMIT)) command = (FORWARDMAX - FORWARDSPEEDLIMIT);
        uint8_t speed = (255/16)*(command - FORWARDMIN);
        bdcTurnLeft(speed);
    }

    else;

    UART_Flush();
    data = 0;
}

void button_toggle(char *button)
{
    if (*button == 0) return 1;
    else return 0;
}