#include "sensor.h"

uint16_t ReceiveData(uint16_t channel){
	return ADCRead(channel);
}

void CalculateData(void){
	uint16_t data = 0;
	float volt, mvolt;
	float temp = 0;

	data = ReceiveData(0);
	volt = 3.3 * (data-52)/4096;
	mvolt = volt*100;
	temp = mvolt - 273.15;
	printf("Temperature: %.1f", temp);

	data = ReceiveData(1);
	volt = 5.0 * (data - 52)/4096;
	printf("Voltage: %.2f", volt);
	SendDataToLCD(temp, volt);
}

void SendDataToLCD(float temp, float volt){
	char table[16];
	sprintf(table, "Temp: %.1f", temp);
	LCD_Clear();
	LCD_GoTo(0,0);
	LCD_SendText(table);

	sprintf(table, "Volt: %.2f", volt);
	LCD_GoTo(1,0);
	LCD_SendText(table);
}
