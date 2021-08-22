#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_adc.h"              // Keil::Device:StdPeriph Drivers:ADC
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "gpio_user.h"
#include "timer_user.h"

void Init_ADC(ADC_TypeDef *ADCx, GPIO_TypeDef *GPIOx, uint16_t GPIO_Pin, uint32_t  ADC_Mode ,
							FunctionalState ADC_ContinuousConvMode, FunctionalState  ADC_ScanConvMode, uint8_t ADC_NbrOfChannel);
uint16_t ADC_rx (ADC_TypeDef *ADCx);
