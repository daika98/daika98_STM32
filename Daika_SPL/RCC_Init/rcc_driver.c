#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "rcc_driver.h"

void rcc_init(void) {

		//Enable HSE Clock
	RCC->CR |= RCC_CR_HSEON; 
		//Wait for external High Speed clock ready flag
	while (!(RCC->CR & RCC_CR_HSERDY)) {}
	
		
	RCC->CR &= ~RCC_CR_PLLON;
	while(!(RCC->CR & RCC_CR_PLLRDY)) {}
		
			// HSE sorce is selected
	RCC->CFGR |= RCC_CFGR_PLLSRC_HSE;
		//Set PLLMUL = 9
	RCC->CFGR |= RCC_CFGR_PLLMULL5;
		//Setting cycle for Flash
  FLASH->ACR |= FLASH_ACR_LATENCY_2; 
		
		//Setting AHB, AHB1, AHB2
	RCC->CFGR |= RCC_CFGR_HPRE_DIV1 | RCC_CFGR_PPRE1_DIV8 | RCC_CFGR_PPRE2_DIV2;
	 RCC->CFGR |= RCC_CFGR_SW_PLL;
	 while(!(RCC->CFGR & RCC_CFGR_SWS_PLL)){}
		 	// Enalble PLL
	RCC->CR |= RCC_CR_PLLON;
		// Wait for PLL enable
	while(!(RCC->CR & RCC_CR_PLLRDY)) {}

}
