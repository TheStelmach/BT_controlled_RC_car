#ifndef UART_H
#define UART_H

#define BAUDRATE 38400 // ONLY WORKS ON 38400 FOR SOME REASON, BUT THIS IS WHAT THE BLUETOOTH MODULE TAKES IN
#define FOSC 16000000
#define MYUBRR (FOSC/(16*BAUDRATE))-1

void UART_init();
void UART_Transmit(unsigned char data);
unsigned char USART_Receive();
void USART_Flush();


#endif