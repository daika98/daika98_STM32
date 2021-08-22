#include "stm32f10x.h"                  // Device header
#include "gpio_user.h"
#include "timer_user.h"
#include "usart_user.h"
#include "i2c_user.h"
#include "adc_user.h"
#include "char_user.h"

int main(void) {
	uint16_t data;
	char str[10];
	Delay_Timer_Init();
	Init_USART(USART2, 9600);
	Init_ADC(ADC1, GPIOB, GPIO_Pin_0, ADC_Channel_8);
	Init_ADC(ADC2, GPIOB, GPIO_Pin_1, ADC_Channel_9);
	
	while(1) {
		data = ADC_rx(ADC1);
		int2char(data,str);
		USART_data(USART2, "\nADC1: ");
		USART_data(USART2, str);
		delay_Ms(200);
		
		str_empty(str);
		
		data = ADC_rx(ADC2);
		int2char(data,str);
		USART_data(USART2, "      ADC2: ");
		USART_data(USART2, str);
		str_empty(str);
		delay_Ms(200);
		
	}
}