#include "usr_inc.h"

bool measFlag = false;

void InitMods(void){

	InitGPIOPins();
	InitUART();
	InitADC();
	NVICInit();
	Init_I2C();
	LCD_Init();
	TIMInit();

}

int main(void)
{
	InitMods();
	ADCCalibrate();
	LCD_SendText("DUPA");

    while(1)
    {
    	if(measFlag){
    		CalculateData();
    		measFlag = false;
    	}

    }
}
