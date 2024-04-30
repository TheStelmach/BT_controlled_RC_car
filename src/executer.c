#include <avr/io.h>
#include <avr/interrupt.h>
#include "executer.h"
#include "BDCdrv.h"
#include "SERVOdrv.h"
#include "UART.h"
#include "peripherals.h"


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
    if ((*millisec) >= 20000) {/*toggle_inbuilt_LED();*/ *millisec = 0; return;} // RESTART SYSTEM TICK EVERY 100 seconds
    
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
            case 1: UART_Transmit(command); buttonA(); break;
            case 2: UART_Transmit(command); buttonB(); break;
            case 3: UART_Transmit(command); buttonX(); break;
            case 4: UART_Transmit(command); buttonY(); break;
            case 5: UART_Transmit(command); leftShoulder(); break;
            case 6: UART_Transmit(command); rightShoulder(); break;
            case 7: UART_Transmit(command); leftTrigger(); break;  
            case 8: UART_Transmit(command); rightTrigger(); break;
            case 9: UART_Transmit(command); padLeft(); break;
            case 10: UART_Transmit(command); padRight(); break;
            case 11: UART_Transmit(command); padUp(); break;    
            case 12: UART_Transmit(command); padDown(); break; 
            default: break;
        }
    }

    else if (command > 12 && command < 46) // Left joystick left (LX)
    {
        uint16_t angle = ((90/32.0)*(44.0 - command));
        angle_update(angle, 'L');
    }

    else if (command == 46) angle_update(0, 'R');

    else if (command > 46 && command < 80) // Left joystick right (LX)
    {
        uint16_t angle = (90/32.0)*(command - 44);
        angle_update(angle, 'R');
    }

    else if (command >= 80 && command < 96) // Right joystick down (RX)
    {
        uint8_t speed = (255/16)*(command - 76);
        bdcTurnRight(speed);
    }    

    else if (command == 96) bdcStop();

    else if (command > 96 && command < 110) // Right joystick up (RX)
    {
        uint8_t speed = (255/16)*(command - 93);
        bdcTurnLeft(speed);
    }

    else;

    UART_Flush();
    data = 0;
}

void buttonA()
{
    bdcStop();
    angle_update(0, 'L');
}

void buttonB()
{
    bdcStop();
    angle_update(0, 'L');
}

void buttonX()
{
    bdcStop();
    angle_update(0, 'L');
}

void buttonY()
{
    bdcStop();
    angle_update(0, 'L');
}

void leftShoulder()
{
    bdcStop();
    angle_update(0, 'L');
}

void rightShoulder()
{
    bdcStop();
    angle_update(0, 'L');
}

void leftTrigger()
{
    bdcStop();
    angle_update(0, 'L');
}

void rightTrigger()
{
    bdcStop();
    angle_update(0, 'L');
}

void padLeft()
{
    bdcStop();
    angle_update(0, 'L');
}

void padRight()
{
    bdcStop();
    angle_update(0, 'L');
}

void padUp()
{
    bdcStop();
    angle_update(0, 'L');
}

void padDown()
{
    bdcStop();
    angle_update(0, 'L');
}
