#include "gpio_drive.h"
#include "RTE_Device.h"                 // Keil::Device:Startup
#include "stm32f10x.h"                  // Device header

void Init_GPIO (unsigned short port, unsigned short pin, unsigned short dir, unsigned short opt){
	volatile unsigned long *CR = 0;
	unsigned short new_pin, offset = 0x00;
	new_pin = pin;
	if (pin > 7) { //(if pin = 8..15. This is CRH)
		new_pin -= 8;
		offset  = 0x01;
	}
	if (port == 1) {
		RCC_APB2ENR |=  4;  //Enable GPIO port A
		CR = (volatile unsigned long*)(&GPIO_A + offset);
	}
	if (port == 2) {
		RCC_APB2ENR |=  (1<<3) ;  //Enable GPIO port B
		CR = (volatile unsigned long*)(&GPIO_B + offset);
	}
  if (port == 3) {
		RCC_APB2ENR |=  0x10;  //Enable GPIO port C
		CR = (volatile unsigned long*)(&GPIO_C + offset);
	}
	*CR &= (unsigned long)~(0xf << (4*new_pin));//Reset the target pin
	*CR |= (unsigned long)((dir << (4*new_pin)) | (opt <<(4*new_pin + 2)));// Set value on the target pin
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


void Init_AFIO_Port_A() {
RCC->APB2ENR &= 0xfffffff0; //Reset register APB2ENR
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN; // Enable AFIO 
	AFIO->EXTICR[0] = 0x00; //Setup interrupt function of pin 0 of port A
	EXTI->PR |= 1;//Clear pending register
	EXTI->IMR |= 1;//Allow interrupt function
	EXTI->RTSR |= 1;//Enable rising trigger
	NVIC_EnableIRQ(EXTI0_IRQn);	// Enable interrupt funtion for line 0
	
}


void Init_Delay() {
	SysTick->CTRL &= 0;// Reset Control register
	SysTick->LOAD &= 0xffffff; // Maximum value of Load_Register
	SysTick->VAL &= 0;  // Current value
	SysTick->CTRL |= 5; // Set state of control Register
}
	
void Init_Systick_Interrupt(){
	SysTick->CTRL &= 0 ; // Reset control register 
  SysTick->LOAD &= 0xffffff ;
	SysTick->LOAD |= 7200000;
  SysTick->VAL 	|= 0;
	SysTick->CTRL |= 7;
}


void delay_1_ms (){
   SysTick->LOAD |= 72000 - 1;//Set value of LOAD_Register
	 SysTick->VAL |= 0;//Set current value
	while ((SysTick->CTRL & 0x00010000) == 0) {}// Waitting for state of Counter flag is set
}

void delay_ms(volatile unsigned int time){
	while (time--){
			delay_1_ms(); 
}
}
