#include "gpio_user.h"

void Init_GPIO (GPIO_TypeDef * GPIOx, GPIOMode_TypeDef GPIO_Mode, uint16_t GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed){

	 GPIO_InitTypeDef gpio_init;
	if (GPIOx == GPIOA) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	} else if (GPIOx == GPIOB) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	} else if (GPIOx == GPIOC) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	} 
	
	gpio_init.GPIO_Mode = GPIO_Mode;
	gpio_init.GPIO_Pin = GPIO_Pin;
	gpio_init.GPIO_Speed = GPIO_Speed;
	GPIO_Init( GPIOx, &gpio_init);
	
}
	
int  Read_GPIO (unsigned short port, unsigned short pin){
	 volatile unsigned long *IDR = 0;
	 int state;
	 unsigned long offset = 0x02;
	
	 if (port == Port_A) {
		 IDR = (volatile unsigned long*)(&GPIO_A + offset);
	 }
	 else if (port == Port_B) {
		 IDR = (volatile unsigned long*)(&GPIO_B + offset);
	 }
	 else if (port == Port_C) {
		 IDR = (volatile unsigned long*)(&GPIO_C + offset);
	 }
	 
	 state = (int)((*IDR & (1 << pin)) >> pin);// Read state of pin on the varriable state 
	 return state;
	 
}


void Write_GPIO (unsigned short port, unsigned short pin, unsigned short state) {
	volatile unsigned long *ODR = 0;
	 unsigned long offset = 0x03;
	
	 if (port == Port_A) {
		 ODR = (volatile unsigned long*)(&GPIO_A + offset);
	 }
	  else if (port == Port_B) {
		 ODR = (volatile unsigned long*)(&GPIO_B + offset);
	 }
	 else if (port == Port_C) {
		 ODR = (volatile unsigned long*)(&GPIO_C + offset);
	 }
	 
	 state ? (*ODR |= (1 << pin)) : (*ODR &= ~(1 << pin));// if varriable state = 1 we write value 1 on the target pin or if varriable state = 0 we write value 0 on the target
}


void Toggle_Pin (unsigned short port, unsigned short pin) {
   if (Read_GPIO (port,pin) == 1) {
		 Write_GPIO(port, pin, 0);//If state of pin is 1 we rewrite value 0 on the pin 
	 }
	 else {
		 Write_GPIO(port, pin, 1);//If state of pin is 0 we rewrite value 1 on the pin 
	 }
}

