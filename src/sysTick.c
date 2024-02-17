#include <avr/io.h>
#include <avr/interrupt.h>
#include "sysTick.h"
#include "BDCdrv.h"
#include "SERVOdrv.h"
#include "UART.h"


void sysTick_init()
{
    //INITIALIZE TIMER 2
    TCCR2A |= (1<<WGM21) | (1<<COM2A0);
    TCCR2A &= (~(1<<WGM20)) & (~(1<<COM2A1));
    TCCR2B |= (1<<CS21);
    TCCR2B &= (~(1<<WGM22)) & (~(1<<CS20)) & (~(1<<CS22));

    OCR2A = TICK; // SHOULD BE 1ms

    SREG |= (1<<SREG_I); // GLOBAL INTERRUPT ENABLED
    TIMSK2 |= (1<<OCIE2A); // OUTPUT COMPARE MATCH INTERRUPT ENABLED
    TIFR2 |= (1<<OCF2A); // TIMER INTERRUPT FLAG REGISTER ENABLED

    //When the I-bit in SREG, OCIE2A (Timer/Counter2 compare match interrupt enable), 
    // and OCF2A are set (one), the Timer/Counter2 compare match interrupt is executed.



    //INITIALIZE OUTPUT COMPARE INTERRUPT


}

void scheduler(uint16_t *millisec)
{
    *millisec++;
    if (*millisec == 2000)
    {
        bdcTurnLeft(40);
        
    }
    else if (*millisec >= 4000)
    {
        bdcStop();
        *millisec = 0;
    }
    else return;
}
