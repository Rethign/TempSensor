#ifndef ADC_H
#define ADC_H


#include "inc.h"

void InitADC(void);
void ADCCalibrate(void);
uint16_t ADCRead(uint16_t channel);
#endif
