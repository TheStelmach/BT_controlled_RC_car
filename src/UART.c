// https://github.com/TheStelmach

#include <avr/io.h>
#include <avr/interrupt.h>
#include "UART.h"

void UART_init()
{
    
    UBRR0H = ((unsigned char)MYUBRR)>>8; // Set baud rate
    UBRR0L = (unsigned char)MYUBRR;
    
    UCSR0A |= (1<<RXC0);
    UCSR0B = (1<<RXEN0)|(1<<TXEN0) | (1<<RXCIE0); // Enable receiver and transmitter
    UCSR0C &= (~(1<<UMSEL01)) & (~(1<<UMSEL00));
    UCSR0C |= (1<<USBS0)|(3<<UCSZ00); // Set frame format: 8 data, 2 stop bit
    // UCSR0C |= (3<<UPM00); // ODD PARITY MODE
    
}

void UART_Transmit(uint8_t data)
{
    while (!(UCSR0A & (1<<UDRE0))) // Wait for empty transmit buffer
    {
        // ADD TIMEOUT CODE MAYBE
    }

    UCSR0B &= ~(1<<TXB80); // Copy 9th bit to TXB8
    if (data & 0x0100)
    UCSR0B |= (1<<TXB80);

    UDR0 = data; // Put data into buffer, sends the data 
    UART_Flush();
}

unsigned char UART_Receive()
{ 
    while (!(UCSR0A & (1<<RXC0)));// Wait for data to be received 
    uint8_t data = UDR0;
    UART_Flush();
    return data;
}

void UART_Flush()
{
    unsigned char dummy;
    while (UCSR0A & (1<<RXC0)) dummy = UDR0;
    dummy = 0;
}

/*
uint8_t UART_error()
{
    // MAY WRITE THIS FUNCTION, MAY NOT

    //CHECK THE ERROR FLAGS

    Due to the buffering of the error flags, the UCSRnA must be read before the
    receive buffer (UDRn), since reading the UDRn I/O location changes the buffer read location. 
    Another equality for the error flags is that they can not be altered by software doing a write
    to the flag location. However, all flags must be set to zero when the UCSRnA is written for
    upward compatibility of future USART implementations. None of the error flags can generate interrupts.
    uint8_t err = 0;
    return err;

}*/

