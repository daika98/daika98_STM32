#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "gpio_drive.h"

#define HIGH 1
#define LOW  0

void Set_GPIO_PP_OUT50(GPIO_InitTypeDef gpio);
void lcd_rs(unsigned short signal);
void lcd_rw(unsigned short signal);
void lcd_enable(unsigned short signal);
void lcd_data (unsigned short data);
void lcd_cmd (unsigned short data);
void lcd_Init();
void lcd_send(char str[]);
void lcd_msg(unsigned short line, unsigned short pos, char msg[]);
void lcd_move(char msg[]);
	