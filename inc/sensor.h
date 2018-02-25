#ifndef SENSOR_H
#define SENSOR_H
#include "inc.h"
#include "lcd.h"
#include "adc.h"

uint16_t ReceiveData(uint16_t channel);
void CalculateData(void);
void SendDataToLCD(float temp, float volt);

#endif
