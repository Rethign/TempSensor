#include "rtc.h"

void InitRTC(){

	//APB1 Inits
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);


	//APB2 Inits
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	//AHB Inits
}
