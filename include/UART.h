// https://github.com/TheStelmach

#ifndef UART_H
#define UART_H

#define BAUDRATE 38400 // THIS IS THE BANDWIDTH THAT THE BLUETOOTH MODULE REQUIRES
#define FOSC 16000000
#define MYUBRR (FOSC/(16*BAUDRATE))-1

void UART_init();
void UART_Transmit(unsigned char data);
unsigned char UART_Receive();
void UART_Flush();


#endif
