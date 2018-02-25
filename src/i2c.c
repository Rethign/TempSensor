/*****************************************************************
 * @title:		comm.c
 * @author: 	Maciej Urda
 * @version:	1.0.0
 * @date:		25-01-2017
 * @brief:		Plik zawierajacy deklaracje funkcji modulow
 * 				komunikacyjnych wykorzystywanych w projekcie:
 * 					UART	I2C
 * *************************************************************** */


/*	includes	*/
#include "i2c.h"

void Init_I2C(void){



	I2C_InitTypeDef i2c_lcd;

	I2C_StructInit(&i2c_lcd);
	i2c_lcd.I2C_Mode = I2C_Mode_I2C;
	i2c_lcd.I2C_ClockSpeed = 100000;
	i2c_lcd.I2C_Ack = I2C_Ack_Enable;

	I2C_Init(I2C1, &i2c_lcd);

	I2C_Cmd(I2C1, ENABLE);
}



/* *************************************** *
 * @param:	data is constant integer.
 * @brief:	Funkcja wysylajaca znaki po
 * 			interfejsie I2C
 * @return	constant integer pointer.
 * *************************************** */
int write_I2C(int data){

	int pcf_addr = ADDRESS_WRITE;	/*I2C Slave write address*/
	int pcf_data = data;

	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BUSY));
	I2C_GenerateSTART(I2C1, ENABLE);

	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_MODE_SELECT));
	I2C_Send7bitAddress(I2C1, pcf_addr, I2C_Direction_Transmitter);

	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED));

	I2C_SendData(I2C1, pcf_data);
    while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED));

	//while(I2C_GetFlagStatus(I2C1, I2C_FLAG_BTF));
	I2C_GenerateSTOP(I2C1, ENABLE);
	//while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));

	return 1;
}

/* *************************************** *
 * @brief:	Funkcja obslugujaca odczyt z
 * 			magistrali I2C
 * @return	integer
 * *************************************** */
int read_I2C() {

	int pcf_pins;
	int pcf_addr = ADDRESS_READ;

	I2C_AcknowledgeConfig(I2C1, ENABLE);
	while(I2C_GetFlagStatus(I2C1,I2C_FLAG_BUSY));

	I2C_GenerateSTART(I2C1, ENABLE);
	while(!I2C_GetFlagStatus(I2C1,I2C_FLAG_SB));

	I2C_Send7bitAddress(I2C1,  pcf_addr, I2C_Direction_Receiver);
	while(!I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED));

	pcf_pins = I2C_ReceiveData(I2C1);

	I2C_NACKPositionConfig(I2C1, I2C_NACKPosition_Current);
	I2C_AcknowledgeConfig(I2C1, DISABLE);
	I2C_GenerateSTOP(I2C1, ENABLE);
	while(I2C_GetFlagStatus(I2C1, I2C_FLAG_STOPF));

	return pcf_pins;
}
