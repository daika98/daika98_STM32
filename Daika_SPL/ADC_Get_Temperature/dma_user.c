#include "dma_user.h"
void Init_DMA (DMA_TypeDef *DMAx, DMA_Channel_TypeDef *DMAy_Channelx, uint32_t DMA_BufferSize, uint32_t DMA_DIR,
							 uint32_t DMA_Mode, uint32_t DMA_Priority, uint32_t DMA_MemoryBaseAddr, uint32_t DMA_PeripheralBaseAddr, 
							 uint32_t DMA_MemoryDataSize, uint32_t DMA_PeripheralDataSize, uint32_t DMA_MemoryInc, uint32_t DMA_PeripheralInc ) {
	
	DMA_InitTypeDef dma_init; 
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_AFIO, ENABLE);  // Enable AFIO
	
	/*COnfigure DMA*/
		if ( DMAx == DMA1) {
			RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);	//Enable clock DMA1
		}
		else if (DMAx == DMA2) {
			RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
		}
		  //  DMA_Cmd(DMAy_Channelx, DISABLE);
				DMA_StructInit(&dma_init);

				dma_init.DMA_BufferSize = DMA_BufferSize;
				dma_init.DMA_DIR = DMA_DIR;
				dma_init.DMA_MemoryBaseAddr = DMA_MemoryBaseAddr;
				dma_init.DMA_MemoryDataSize = DMA_MemoryDataSize;
				dma_init.DMA_MemoryInc = DMA_MemoryInc;
				dma_init.DMA_Mode = DMA_Mode;
				dma_init.DMA_PeripheralBaseAddr = DMA_PeripheralBaseAddr;
				dma_init.DMA_PeripheralDataSize = DMA_PeripheralDataSize;
				dma_init.DMA_PeripheralInc = DMA_PeripheralInc;
				dma_init.DMA_Priority = DMA_Priority;
				
				DMA_Init(DMAy_Channelx, &dma_init);
				DMA_Cmd(DMA1_Channel1, ENABLE);

			
		
}


