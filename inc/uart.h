#ifndef UART_H
#define UART_H

#include "inc.h"

void InitUART(void);
void UARTSendChar(const char outChar);
void UARTSendString(const char* outString);

char* UARTReceiveString(void);
char UARTReceiveChar(void);

int __io_putchar(int outChar);

void USART2_IRQHandler(void);

#endif
