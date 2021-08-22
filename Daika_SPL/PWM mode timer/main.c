#include "stm32f10x.h"                  // Device header
#include "gpio_drive.h"
#include "spi_drive.h"


int main(void) {

	Init_GPIO(Port_C, 13, OUT_50, OUT_GP_PP);
	Write_GPIO(Port_C,13,0);
	//Setting state of chanels 1,2,3,4 of timer 4
	Init_GPIO(Port_B, 6, OUT_50, OUT_AF_PP);
	Init_GPIO(Port_B, 7, OUT_50, OUT_AF_PP);
	Init_GPIO(Port_B, 8, OUT_50, OUT_AF_PP);
	Init_GPIO(Port_B, 9, OUT_50, OUT_AF_PP);
	
	//Configuration timer 4 chanel 4
	RCC->APB1ENR |= RCC_APB1ENR_TIM4EN;//Enable timer 4
	
	TIM4->CCER |= TIM_CCER_CC1E;
	TIM4->CCER |= TIM_CCER_CC2E;
	TIM4->CCER |= TIM_CCER_CC3E;
	TIM4->CCER |= TIM_CCER_CC4E; // Compare 4 output enable
	
	TIM4->CR1 |= TIM_CR1_ARPE;//Auto-reload preload enable
	//PWM mode 1
	TIM4->CCMR2 |= TIM_CCMR2_OC4M_2 | TIM_CCMR2_OC4M_1 | TIM_CCMR2_OC4PE;
	TIM4->CCMR2 &= ~(TIM_CCMR2_OC4M_0);
	TIM4->CCMR2 |= TIM_CCMR2_OC3M_2 | TIM_CCMR2_OC3M_1 | TIM_CCMR2_OC3PE;
	TIM4->CCMR2 &= ~(TIM_CCMR2_OC3M_0);
	TIM4->CCMR1 |= TIM_CCMR1_OC2M_2 | TIM_CCMR1_OC2M_1 | TIM_CCMR1_OC2PE;
	TIM4->CCMR1 &= ~(TIM_CCMR1_OC2M_0);
	TIM4->CCMR1 |= TIM_CCMR1_OC1M_2 | TIM_CCMR1_OC1M_1 | TIM_CCMR1_OC1PE;
	TIM4->CCMR1 &= ~(TIM_CCMR1_OC1M_0);
	
	TIM4->PSC = 71;
	TIM4->ARR = 999;
	
	TIM4->CCR1 = 50;
	TIM4->CCR2 = 200;
	TIM4->CCR3 = 500;
	TIM4->CCR4 = 1000;
	TIM4->EGR |= TIM_EGR_UG;
	TIM4->CR1 |= TIM_CR1_CEN;
	
	while (1) {

		
	}
}

