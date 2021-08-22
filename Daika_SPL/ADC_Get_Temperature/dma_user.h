#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_dma.h"              // Keil::Device:StdPeriph Drivers:DMA

void Init_DMA (DMA_TypeDef *DMAx, DMA_Channel_TypeDef *DMAy_Channelx, uint32_t DMA_BufferSize, uint32_t DMA_DIR,
							 uint32_t DMA_Mode, uint32_t DMA_Priority, uint32_t DMA_Memory_Add, uint32_t DMA_Peripheral_Add, 
							 uint32_t DMA_Memory_Data_Size, uint32_t DMA_Peripheral_Data_Size, uint32_t DMA_Memory_Inc, uint32_t DMA_Peripheral_Inc ) ;


