#include "stm32f10x.h"                  // Device header
#include "gpio_drive.h"
#include "timer.h"
#include "lcd_driver.h"

volatile int time = 0;
void delay(volatile int k);

GPIO_InitTypeDef gpio;

int main(void) {

	timer_delay_init();
	char msg[] = "Khoat Daika";

	Init_Delay();
	GPIO_Init(GPIOC,&gpio);
	
	Set_GPIO_PP_OUT50(gpio);
	lcd_Init();
	lcd_msg(1,3,msg);
	lcd_msg(2,4,"Dep trai");
	delay(500);
	//lcd_move(msg);
	while (1) {

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