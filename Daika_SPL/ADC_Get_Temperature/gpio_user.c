#include "gpio_user.h"

void Init_GPIO (GPIO_TypeDef * GPIOx, GPIOMode_TypeDef GPIO_Mode, uint16_t GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed){

	 GPIO_InitTypeDef gpio_init;
	/*Enable clock GPIO */
	if (GPIOx == GPIOA) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	} else if (GPIOx == GPIOB) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	} else if (GPIOx == GPIOC) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
	} 
	GPIO_StructInit(&gpio_init);
	gpio_init.GPIO_Mode = GPIO_Mode;
	gpio_init.GPIO_Pin = GPIO_Pin;
	gpio_init.GPIO_Speed = GPIO_Speed;
	GPIO_Init( GPIOx, &gpio_init);
	
}
	
