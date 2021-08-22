#include "timer.h"

void Delay_Timer_Init(void ){
	TIM_TimeBaseInitTypeDef timer;
	TIM_Cmd(TIM2, DISABLE);
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_TIM2, ENABLE);
	timer.TIM_CounterMode = TIM_CounterMode_Up;
	timer.TIM_Period = 0xffff;
	timer.TIM_Prescaler = 71;
	TIM_TimeBaseInit(TIM2, &timer);
	TIM_Cmd(TIM2, ENABLE);
	
}
void delay_1Ms(){
	TIM_SetCounter(TIM2, 0);
	while (TIM_GetCounter(TIM2) < 1000) {}
	
}
void delay_Ms(volatile int time) {
	while (time--){
		delay_1Ms();
	}
}
