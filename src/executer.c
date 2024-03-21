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

void execute (char nextCommand)
{
    char command = nextCommand;
    if (command >= 1 && command <= 9)
    {

    }
    return;
}