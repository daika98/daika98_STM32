#include "dma_user.h"
void Init_DMA (DMA_TypeDef *DMAx, DMA_Channel_TypeDef *DMAy_Channelx, uint32_t DMA_BufferSize, uint32_t DMA_DIR,
							 uint32_t DMA_Mode, uint32_t DMA_Priority, uint32_t DMA_Memory_Add, uint32_t DMA_Peripheral_Add, 
							 uint32_t DMA_Memory_Data_Size, uint32_t DMA_Peripheral_Data_Size, uint32_t DMA_Memory_Inc, uint32_t DMA_Peripheral_Inc ) {
	
	DMA_InitTypeDef dma_init; 
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_AFIO, ENABLE);  // Enable AFIO
	
	/*COnfigure DMA*/
		if ( DMAx == DMA1) {
			RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
		}
		else if (DMAx == DMA2) {
			RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA2, ENABLE);
		}
		    DMA_Cmd(DMAy_Channelx, DISABLE);
				DMA_StructInit(&dma_init);

				dma_init.DMA_BufferSize = DMA_BufferSize;
				dma_init.DMA_DIR = DMA_DIR;
				dma_init.DMA_MemoryBaseAddr = DMA_Memory_Add;
				dma_init.DMA_MemoryDataSize = DMA_Memory_Data_Size;
				dma_init.DMA_MemoryInc = DMA_Memory_Inc;
				dma_init.DMA_Mode = DMA_Mode;
				dma_init.DMA_PeripheralBaseAddr = DMA_Peripheral_Add;
				dma_init.DMA_PeripheralDataSize = DMA_Peripheral_Data_Size;
				dma_init.DMA_PeripheralInc = DMA_Peripheral_Inc;
				dma_init.DMA_Priority = DMA_Priority;
				
				DMA_Init(DMAy_Channelx, &dma_init);
        DMA_Cmd(DMAy_Channelx, ENABLE);
			
		
}


