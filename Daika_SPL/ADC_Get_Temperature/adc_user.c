#include "adc_user.h"

void Init_ADC(ADC_TypeDef *ADCx, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t  ADC_Mode ,
							FunctionalState ADC_ContinuousConvMode, FunctionalState  ADC_ScanConvMode, uint8_t ADC_NbrOfChannel) {
	ADC_InitTypeDef adc_init;
	
	RCC_ADCCLKConfig(RCC_PCLK2_Div6);//Configure ADC_Clock. ADC Clock must > 14MHz
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //Enable Alternate function
	
			/*Configure pin of ADC*/
	Init_GPIO(GPIOx, GPIO_Mode_AIN, GPIO_Pin,GPIO_Speed_10MHz); //GPIO_Speed_10MHz : Dont care speed for input mode
	
	if (ADCx == ADC1) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE); //Enable clock ADC1
	}
	else if (ADCx == ADC2) {
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC2, ENABLE);
	}
	
	ADC_StructInit(&adc_init);//Set default values
	
	adc_init.ADC_Mode = ADC_Mode;																// Mode of ADC
	adc_init.ADC_ContinuousConvMode = ADC_ContinuousConvMode;  	// Continous conversion mode
	adc_init.ADC_ScanConvMode = ADC_ScanConvMode;							 	// Scan mode
	adc_init.ADC_NbrOfChannel = ADC_NbrOfChannel; 							//Configure number of channel
	ADC_Init(ADCx, &adc_init);
	
	ADC_Cmd(ADCx, ENABLE); //Enable ADC
	delay_Ms(10);						//Need delay time then enable ADC1 again
	ADC_Cmd(ADCx, ENABLE);	//Conversion starts when this bit holds a value of 1 and a 1 is written to i
  
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