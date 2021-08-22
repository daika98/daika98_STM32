#include "RTE_Device.h"                 // Keil::Device:Startup
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO


void Init_GPIO (GPIO_TypeDef * GPIOx, GPIOMode_TypeDef GPIO_Mode, uint16_t GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed);

