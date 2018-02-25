#include "timer.h"

void TIMInit(void){

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

	//deklaracja struktury timera
	TIM_TimeBaseInitTypeDef tim;

	//inicjalizacja parametrow domyslnych
	TIM_TimeBaseStructInit(&tim);
	tim.TIM_CounterMode = TIM_CounterMode_Up;		//rodzaj liczenia timera
	tim.TIM_Prescaler = 24000 - 1;					//przeskalowanie clocka
	tim.TIM_Period = 10000 - 1;						//konfiguracja zakresu, maksymalnie odlicza 60 sek
	//inicjalizacja Timera
	TIM_TimeBaseInit(TIM2, &tim);
	TIM_SetCounter(TIM2, 0);

	TIM_Cmd(TIM2, ENABLE);

	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);

}

void TIM2_IRQHandler(void){

	extern bool measFlag;

	//przerwanie od przeladowania licznika, zbyt dlugi czas
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET){
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
		//zbyt dlugi czas, predkosc 0

		measFlag = true;
		TIM_SetCounter(TIM2,0);
	}
}
