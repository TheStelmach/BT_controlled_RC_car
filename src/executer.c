#include <avr/io.h>
#include <avr/interrupt.h>
#include "executer.h"
#include "BDCdrv.h"
#include "SERVOdrv.h"
#include "UART.h"
#include "peripherals.h"

extern char switchPID, switchTraction, switchLights, switchObstacles,
limitAccel;

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

void scheduler(int *millisec)
{
    if ((*millisec) >= 60000) {*millisec = 0; return;} // RESTART SYSTEM TICK WHEN VALUE GETS CLOSE TO OVERFLOWING THE 16 BIT INTEGER
    
    (*millisec)++; 
    return;
}

void execute(char *data, char *motorDirection, float *desiredSpeed)
{
    // EVERY BYTE IS A SEPARATE COMMAND, EXAMPLE AT THE BOTTOM
    char command = *data;
    if (command > 0 && command <= 12)
    {
        switch (command)
        { 
            case 1: 
                bdcStop();
                angle_update(0, 'R');
                break;
            case 2: button_toggle(&switchPID); break;
            case 3: button_toggle(&switchTraction); break;
            case 4: button_toggle(&switchLights); break;
            case 5: button_toggle(&switchObstacles); break;
            case 6: 
                button_toggle(&limitAccel);
                if (limitAccel == 1) switchPID = 0;
                break;
            case 7: break;
            case 8: break;
            case 9: break;
            case 10: break;
            case 11: break;  
            case 12: break; 
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
        int speed = (255/16)*(FORWARDMIN - command);
        if (switchPID != 1) {*desiredSpeed = speed; *motorDirection = 'F';}
        else bdcTurnRight(speed);
    }    

    else if (command == FORWARDMIN) {*motorDirection = 0; *desiredSpeed = 0; bdcStop();}

    else if (command > FORWARDMIN && command < FORWARDMAX) // Right joystick up (RX)
    {
        if (command > (FORWARDMAX - FORWARDSPEEDLIMIT)) command = (FORWARDMAX - FORWARDSPEEDLIMIT);
        int speed = (255/16)*(command - FORWARDMIN);
        if (switchPID != 1) {*desiredSpeed = speed; *motorDirection = 'B';}
        else bdcTurnLeft(speed);
    }

    else;

    UART_Flush();
    data = 0;
}

void button_toggle(char *button)
{
    if (*button == 0) *button =  1;
    else *button = 0;
}