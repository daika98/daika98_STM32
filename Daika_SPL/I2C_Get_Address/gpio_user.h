#include "RTE_Device.h"                 // Keil::Device:Startup
#include "stm32f10x.h"                  // Device header
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO



#define RCC_APB2ENR (*((volatile unsigned long*) 0x40021018))
#define GPIO_A      (*((volatile unsigned long*) 0x40010800))
#define GPIO_B      (*((volatile unsigned long*) 0x40010C00))	
#define GPIO_C      (*((volatile unsigned long*) 0x40011000))

//Definition port A and C
#define  Port_A  1
#define  Port_B  2
#define  Port_C  3

//Definition direction of pin (refer to Reference manual, chapter 9 ,page 171)
#define  IN  0 
#define  OUT_10 1
#define  OUT_2  2
#define  OUT_50 3

//Definition option of input(refer to Reference manual, chapter 9 ,page 171)
#define  IN_Analog 0
#define  IN_Floating 1
#define  IN_PP 2

//Definition option of ouput(refer to Reference manual, chapter 9 ,page 171)
#define  OUT_GP_PP 0
#define  OUT_GP_OD 1
#define  OUT_AF_PP 2
#define  OUT_AF_OD 3

void Init_GPIO (GPIO_TypeDef * GPIOx, GPIOMode_TypeDef GPIO_Mode, uint16_t GPIO_Pin, GPIOSpeed_TypeDef GPIO_Speed);

int Read_GPIO (unsigned short port, unsigned short pin); //Read value of pin

void Write_GPIO (unsigned short port, unsigned short pin, unsigned short state);  // Write value on pin

