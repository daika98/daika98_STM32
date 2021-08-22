#include "stm32f10x.h"                  // Device header
#include "gpio_user.h"
#include "timer_user.h"
#include "usart_user.h"
#include "i2c_user.h"
#include "adc_user.h"
#include "char_user.h"

uint16_t data = 0;

int main(void) {
	char str[10];
	Init_Delay_Timer();
	Init_USART(USART2, 9600);
	Init_ADC(ADC1, GPIOB, GPIO_Pin_0, ADC_Channel_8);
	Init_GPIO(GPIOC, GPIO_Mode_Out_PP, GPIO_Pin_13, GPIO_Speed_50MHz);
	RCC->CFGR |= RCC_CFGR_ADCPRE_DIV6;
	
	ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);		//Configure interrupt for ADC1 _ End of conversion
	__disable_irq();
	NVIC_EnableIRQ(ADC1_2_IRQn);
	__enable_irq();
	
	while(1) {
		int2char(data, str);
		USART_data(USART2, str);
		USART_data(USART2, "\nADC Value: ");
		ADC_ITConfig(ADC1, ADC_IT_EOC, ENABLE);
		str_empty(str);

		GPIO_SetBits(GPIOC, GPIO_Pin_13);
		delay_Ms(200);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		delay_Ms(200);
	}
}

void ADC1_2_IRQHandler() {
	data = ADC_rx(ADC1);
	ADC_ITConfig(ADC1, ADC_IT_EOC, DISABLE);
}

