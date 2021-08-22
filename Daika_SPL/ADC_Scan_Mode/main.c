#include "stm32f10x.h"                  // Device header
#include "gpio_user.h"
#include "timer_user.h"
#include "usart_user.h"
#include "adc_user.h"
#include "char_user.h"
#include "dma_user.h"
uint16_t data[2];
	char str1[5];
	
int main(void) {
	
	Init_Delay_Timer();
	Init_USART(USART2, 9600);
	
		Init_ADC(ADC1,GPIOB, GPIO_Pin_0 | GPIO_Pin_1 , ADC_Mode_Independent, ENABLE, ENABLE, 2);
		ADC_RegularChannelConfig(ADC1, ADC_Channel_8, 1, ADC_SampleTime_71Cycles5); //Set up sample time
		ADC_RegularChannelConfig(ADC1, ADC_Channel_9, 2, ADC_SampleTime_71Cycles5);
		ADC_ExternalTrigConvCmd (ADC1, DISABLE);
	 	ADC_DMACmd (ADC1, ENABLE); //Enable DMA request for ADC1

		/*Configure DMA*/
		Init_DMA(DMA1, DMA1_Channel1, 2, DMA_DIR_PeripheralSRC, DMA_Mode_Circular, DMA_Priority_Medium,(uint32_t)data, (uint32_t)&ADC1->DR, 
		DMA_MemoryDataSize_HalfWord , DMA_PeripheralDataSize_HalfWord, DMA_MemoryInc_Enable, DMA_PeripheralInc_Disable );
		
	DMA_ITConfig(DMA1_Channel1, DMA_IT_TC, ENABLE);
	__disable_irq();
	NVIC_EnableIRQ(DMA1_Channel1_IRQn);
	__enable_irq();
	
	while(1) {
		
	}
}

void DMA1_Channel1_IRQHandler() {
	DMA_ClearITPendingBit(DMA1_IT_TC1);
	data[0] = (uint16_t) (data[0]*3300/0xffe);
		int2char(data[0], str1);
		USART_data(USART2, "\nB0:  ");
		USART_data(USART2, str1);
		str_empty(str1);
		
		data[1] = (uint16_t) (data[1]*3300/0xffe);
		int2char(data[1], str1);
		USART_data(USART2, "    B1:  ");
		USART_data(USART2, str1);
		str_empty(str1);

		delay_Ms(100);
 
}


