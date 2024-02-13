#include <avr/io.h>
#include <avr/interrupt.h>
#include "SERVOdrv.h"
#include "Arduino.h"

static uint16_t position = 0;

void servo_init()
{

/*
    TCCR1A |= (1<<WGM11) | (1<<COM1A1);
    TCCR1A &= (~(1<<WGM10)) & (~(1<<COM1A0));
    TCCR1B |= (1<<WGM12) | (1<<WGM13) | (1<<CS11);
    TCCR1B &= (~(1<<CS10)) & (~(1<<CS12));
    TIMSK1 |= (1<<TOIE1) | (1<<OCIE1A);

    ICR1H = 8 << (TIMERINTERRUPT && 0xFF00);
    ICR1L = (TIMERINTERRUPT && 0x00FF);
    OCR1AH = 8 << (MINANGLE && 0xFF00);
    OCR1AL = (MINANGLE && 0x00FF);

    // TIMER2 in Fast PWM mode
    // CS22 = 1, CS21 = CS20 = 0 -> prescaler @ 128, 8Mhz clock.
    DDRB |= (1<<SERVODATA);

     
    OCR1A = MIDANGLE;
    position = MIDANGLE;
*/

//Initialize Timer2
    TCCR2A = 0;
    TCCR2B = 0;
    TCNT2 = 0;
    
    // Set OC2B for Compare Match (digital pin3)
    pinMode(3, OUTPUT);
    //bitSet(TCCR2A, COM2B0);//not valid when used by itself
    bitSet(TCCR2A, COM2B1);//clear OC2B on up count compare match
    //set OC2B on down count compare match

    // Set mode 5-- Phase correct PWM to OCR2A counts up and down
    bitSet(TCCR2A, WGM20);
    bitSet(TCCR2B, WGM22);

    // Set up /1024 prescale
    bitSet(TCCR2B, CS20);
    bitSet(TCCR2B, CS21);
    bitSet(TCCR2B, CS22);

    //OCR2A = 32;      // Sets freq 50hz?    OC2A PIN 11
    OCR2A = 156; //Sets freq 50Hz
    //Timer 2 counts up and down for 312 total counts
    //312 x 1024 x.0625 = 19.968ms 50.08 Hz

    // enable timer compare interrupt
    //bitSet(TIMSK2, OCIE2A);

    OCR2B = 19;//50% duty cycle valid values 1-155

}
