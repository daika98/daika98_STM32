#include "stm32f10x.h"                  // Device header
#include "gpio_user.h"
#include "timer_user.h"
#include "usart_user.h"
#include "dma_user.h"
#include "char_user.h"

int main(void) {
	/*Trong thoi gian xay ra ngat DMA van hoat dong*/
	char a[] = "Hello World\n";
	Delay_Timer_Init();
	Init_USART(USART2, 9600);
	USART_DMACmd(USART2, USART_DMAReq_Tx, ENABLE); //Enable DMA request for USART_Tx

	/*Configure DMA*/

	Init_DMA(DMA1,DMA1_Channel7, length_str(a), DMA_DIR_PeripheralDST, DMA_Mode_Circular, DMA_Priority_Medium,
						(uint32_t)a, (uint32_t)&USART2->DR, DMA_MemoryDataSize_Byte, DMA_PeripheralDataSize_Byte,
							DMA_MemoryInc_Enable, DMA_PeripheralInc_Disable);
		/*Configure interrupt for delay DMA to USART*/
	DMA_ITConfig(DMA1_Channel7, DMA_IT_TC, ENABLE);
	__disable_irq();
	NVIC_EnableIRQ(DMA1_Channel7_IRQn);
	__enable_irq();
	
	while(1) {
        DMA_Cmd(DMA1_Channel7, ENABLE);//Enable DMA_Transmit data continue

	}
}
 
void DMA1_Channel7_IRQHandler() {
	DMA_ClearITPendingBit(DMA1_IT_TC7);
	DMA_Cmd(DMA1_Channel7, DISABLE); // Disable DMA_Trasmit data stop
	delay_Ms(500);
	USART_data(USART2, "Test delay_Daika\n\n");
	delay_Ms(500);
}

