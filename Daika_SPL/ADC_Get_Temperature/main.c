#include "stm32f10x.h"                  // Device header
#include "gpio_user.h"
#include "timer_user.h"
#include "usart_user.h"
#include "adc_user.h"
#include "char_user.h"
#include "dma_user.h"

	
int main(void) {
	volatile int data;
	char str1[5];
	Init_Delay_Timer();
	Init_USART(USART2, 9600);

	ADC_InitTypeDef adc_init;
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //Enable Alternate function
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //Enable clock ADC1

	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//Configure ADC_Clock. ADC Clock must > 14MHz

	ADC_RegularChannelConfig(ADC1, ADC_Channel_16, 1,ADC_SampleTime_239Cycles5);
  ADC_TempSensorVrefintCmd(ENABLE);

	ADC_Cmd(ADC1, ENABLE); //Enable ADC
	delay_Ms(10);						//Need delay time then enable ADC1 again
	ADC_Cmd(ADC1, ENABLE);	//Conversion starts when this bit holds a value of 1 and a 1 is written to i
	
	
	while(1) {
		data = (uint16_t) (ADC_GetConversionValue(ADC1) * 3300 / 0xFFE);
		data = (uint16_t) ((1430 - data )/4.3) + 25;
		int2char(data, str1);
		USART_data(USART2, "Temperature of sensor: ");
		USART_data(USART2, str1);
		USART_data(USART2, "\n");
		str_empty(str1);
		delay_Ms(1000);
	}
}

