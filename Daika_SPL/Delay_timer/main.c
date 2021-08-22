#include "stm32f10x.h"                  // Device header
#include "gpio_drive.h"
#include "timer.h"

volatile int time = 0;

int main(void) {
  TIM_TimeBaseInitTypeDef delay_timer;
	Init_GPIO(Port_C, 13, OUT_50, OUT_GP_PP);
	Write_GPIO(Port_C,13,0);
	Delay_Timer_Init(delay_timer);
	while (1) {
   Write_GPIO(Port_C,13,0);
	 delay_Ms(500);
	 Write_GPIO(Port_C,13,1);
	 delay_Ms(500);
		
	}
}
