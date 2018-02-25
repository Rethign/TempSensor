#include "adc.h"

void InitADC(void){

	//Initialize clock for ADC
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);

	ADC_InitTypeDef adc;
	adc.ADC_ContinuousConvMode = DISABLE;
	adc.ADC_NbrOfChannel = 2;
	adc.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
	ADC_Init(ADC1, &adc);

	ADC_Cmd(ADC1, ENABLE);
}

void ADCCalibrate(void){
	ADC_ResetCalibration(ADC1);
	while(ADC_GetResetCalibrationStatus(ADC1));

	ADC_StartCalibration(ADC1);
	while(ADC_GetCalibrationStatus(ADC1));

}

uint16_t ADCRead(uint16_t channel){

	ADC_RegularChannelConfig(ADC1, channel, 1, ADC_SampleTime_71Cycles5);
	ADC_SoftwareStartConvCmd(ADC1, ENABLE);

	while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) != SET);

	return ADC_GetConversionValue(ADC1);
}

