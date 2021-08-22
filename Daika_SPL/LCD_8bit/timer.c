#include "timer.h"

void timer_delay_init(void) {
		//Configuration timer 4 chanel 4
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;//Enable timer 4	
	//Cofigure TIM4 with time base
	
	TIM4->PSC = 999;
	TIM4->ARR = 71;
	TIM1->CR1 |= TIM_CR1_URS; //Only counter overflow/underflow generates an update interrupt
	TIM4->DIER |= TIM_DIER_UIE;//Update interrupt enable
	TIM4->EGR |= TIM_EGR_UG;// Update genration 
	
	NVIC_EnableIRQ(TIM4_IRQn);
}
