#include "nvic.h"
void NVICInit(){
	NVIC_InitTypeDef nvic_timer;
	nvic_timer.NVIC_IRQChannel = TIM2_IRQn;
	nvic_timer.NVIC_IRQChannelPreemptionPriority = 4;
	nvic_timer.NVIC_IRQChannelSubPriority = 0;
	nvic_timer.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_timer);

	NVIC_InitTypeDef nvic_uart;
	nvic_uart.NVIC_IRQChannel = USART2_IRQn;
	nvic_uart.NVIC_IRQChannelPreemptionPriority = 4;
	nvic_uart.NVIC_IRQChannelSubPriority = 0;
	nvic_uart.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&nvic_uart);
}
