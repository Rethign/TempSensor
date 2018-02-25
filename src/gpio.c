#include "gpio.h"

void InitGPIOPins(void){

	//Initialize GPIO structure
	GPIO_InitTypeDef gpio;
	GPIO_StructInit(&gpio);

	//Initialize clock for LED GPIO
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_GPIOA | RCC_APB2Periph_GPIOB | RCC_APB2Periph_GPIOC, ENABLE );

	//GPIO Initialization - LED
	gpio.GPIO_Pin = GPIO_Pin_8;
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOC, &gpio);

	//Initialize clock for USART GPIO
	RCC_APB2PeriphClockCmd( RCC_APB2Periph_AFIO, ENABLE);

	//GPIO Initialization - USART
	gpio.GPIO_Pin = GPIO_Pin_9;		//TX PIN
	gpio.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOA, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_10;		//RX PIN
	gpio.GPIO_Mode  = GPIO_Mode_IN_FLOATING;
	GPIO_Init(GPIOA, &gpio);

	gpio.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1;
	gpio.GPIO_Mode = GPIO_Mode_AIN;
	GPIO_Init(GPIOA, &gpio);

	//Initialize clock for I2C GPIO
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

	//GPIO Initialization - I2C
	GPIO_InitTypeDef gpio_i2c;
	GPIO_StructInit(&gpio_i2c);
	gpio_i2c.GPIO_Pin = GPIO_Pin_6 | GPIO_Pin_7; // SCL, SDA
	gpio_i2c.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB, &gpio_i2c);

}



