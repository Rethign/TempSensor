#include "uart.h"

#define USART USART1

char UARTBuffer[BUFF_SIZE] = {0};
int it = 0;
void InitUART(void){

	USART_InitTypeDef uart;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	USART_StructInit(&uart);

	uart.USART_BaudRate = 115200;
	uart.USART_WordLength = USART_WordLength_8b;
	uart.USART_StopBits = USART_StopBits_1;
	uart.USART_Parity = USART_Parity_No;
	uart.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;
	USART_Init(USART, &uart);
	USART_Cmd(USART, ENABLE);
}

void UARTSendChar(const char outChar){

	while(USART_GetFlagStatus(USART, USART_FLAG_TXE) == RESET);
	USART_SendData(USART, outChar);
}

int __io_putchar(int outChar){

	if(outChar == '\n')
		UARTSendChar('\r');
	UARTSendChar(outChar);
	return outChar;
}

void USART2_IRQHandler(void){

	//RX Handle
	if(USART_GetITStatus(USART, USART_IT_RXNE) != RESET){
		UARTBuffer[it] = (char)USART_ReceiveData(USART);
		it++;
		if(it == BUFF_SIZE) it = 0;
	}
}
