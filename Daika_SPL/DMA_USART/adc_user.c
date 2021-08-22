#include "adc_user.h"

void Init_ADC(ADC_TypeDef *ADCx, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint8_t ADC_Channel) {
	ADC_InitTypeDef adc_init;
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //Enable Alternate function
	
			/*Configure pin of ADC*/
	Init_GPIO(GPIOx, GPIO_Mode_AIN, GPIO_Pin,GPIO_Speed_10MHz); //GPIO_Speed_10MHz : Dont care speed for input mode
	
	if (ADCx == ADC1) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //Enable clock ADC1
		ADC_StructInit(&adc_init);
		adc_init.ADC_ContinuousConvMode = ENABLE;  // Continous conversion mode
		adc_init.ADC_NbrOfChannel = 1; //Configure number of channel
		ADC_Init(ADC1, &adc_init);
		ADC_Cmd(ADC1, ENABLE); //Enable ADC1
		delay_Ms(10);						//Need delay time then enable ADC1 again
		ADC_Cmd(ADC1, ENABLE);	//Conversion starts when this bit holds a value of 1 and a 1 is written to i
		ADC_RegularChannelConfig (ADC1, ADC_Channel, 1, ADC_SampleTime_1Cycles5); //Configure regular channel
	}
	else if (ADCx == ADC2) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
		ADC_StructInit(&adc_init);
		adc_init.ADC_ContinuousConvMode = ENABLE;
		adc_init.ADC_NbrOfChannel = 1;
		ADC_Init(ADC2, &adc_init);
		ADC_Cmd(ADC2, ENABLE);
		delay_Ms(10);
		ADC_Cmd(ADC2, ENABLE);
		ADC_RegularChannelConfig (ADC2, ADC_Channel, 1, ADC_SampleTime_1Cycles5);
	}
}
uint16_t ADC_rx (ADC_TypeDef *ADCx) {
	
	uint16_t data;
	 if (ADCx == ADC1) {
			while ( !(ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC))) {} // Need wait flag EOC set - End of conversion
			data = (uint16_t) (ADC_GetConversionValue(ADC1) * 3300 / 0xFFF);
				
	 } 
	 else if (ADCx == ADC2) {
		 while ( !(ADC_GetFlagStatus(ADC2, ADC_FLAG_EOC))) {}
			data = (uint16_t) (ADC_GetConversionValue(ADC2) * 3300 / 0xFFF);
	 }
	 return data;
	
}