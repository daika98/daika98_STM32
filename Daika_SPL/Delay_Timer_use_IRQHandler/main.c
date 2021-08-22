#include "stm32f10x.h"                  // Device header
#include "gpio_drive.h"
#include "spi_drive.h"

volatile int time = 0;
void delay(volatile int k);

int main(void) {

	Init_GPIO(Port_C, 13, OUT_50, OUT_GP_PP);
	Write_GPIO(Port_C,13,0);

	//Configuration timer 4 chanel 4
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;//Enable timer 4	
	//Cofigure TIM4 with time base
	
	TIM4->PSC = 71;
	TIM4->ARR = 999;
	TIM1->CR1 |= TIM_CR1_URS; //Only counter overflow/underflow generates an update interrupt
	TIM4->DIER |= TIM_DIER_UIE;//Update interrupt enable
	TIM4->EGR |= TIM_EGR_UG;// Update genration 
	
	NVIC_EnableIRQ(TIM4_IRQn);
	
	while (1) {
   Write_GPIO(Port_C,13,0);
	 delay(1000);
	 Write_GPIO(Port_C,13,1);
	 delay(1000);
		
	}
}

void delay(volatile int k) {
	TIM4->CR1 |= TIM_CR1_CEN; // Enable counter
	time = 0;
	while (time < k) {}
	TIM4->CR1 &= ~TIM_CR1_CEN; //Disable counter
	
}

void TIM4_IRQHandler(void) {
  if (TIM4->SR & TIM_SR_UIF) {
		time++;
	}
	TIM4->SR &= ~TIM_SR_UIF; //Clear update interrupt flag
}