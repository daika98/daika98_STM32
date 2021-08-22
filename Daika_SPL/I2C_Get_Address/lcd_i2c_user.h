#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "gpio_user.h"
#include "timer_user.h"
#include "i2c_user.h"

#define HIGH 1
#define LOW  0

void i2c_lcd_send_byte ( char data);
void i2c_lcd_data ( unsigned char data);
void i2c_lcd_cmd (unsigned char data);
void lcd_Init(void);
void lcd_send(char str[]);
void lcd_msg(unsigned short line, unsigned short pos, char msg[]);
void lcd_move(void);

