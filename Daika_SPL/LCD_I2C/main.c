#include "stm32f10x.h"                  // Device header
#include "gpio_drive.h"
#include "timer.h"
#include "lcd_i2c.h"

	


int main(void){
	char msg[] = "Khoat DaiKa";
	GPIO_InitTypeDef gpio;
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOC, ENABLE);
	gpio.GPIO_Mode = GPIO_Mode_Out_PP ;
	gpio.GPIO_Pin =  GPIO_Pin_13;
	gpio.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init (GPIOC,&gpio);
	
	Delay_Timer_Init();
	
	lcd_Init();
  lcd_msg(1,3,msg);
  lcd_msg(2,4,"19/11/1998");
	//lcd_move();
	while (1) {
		
	GPIO_SetBits (GPIOC,GPIO_Pin_13);
	delay_Ms(500);
	GPIO_ResetBits (GPIOC,GPIO_Pin_13);
	delay_Ms(500);
	}
}

