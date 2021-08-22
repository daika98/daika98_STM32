#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_tim.h"              // Keil::Device:StdPeriph Drivers:TIM
#include "gpio_user.h"
#include "timer_user.h"
#include "i2c_user.h"

#define HIGH 1
#define LOW  0

void i2c_lcd_send_byte (I2C_TypeDef* I2Cx, char data);
void i2c_lcd_data (I2C_TypeDef* I2Cx, unsigned char data);
void i2c_lcd_cmd (I2C_TypeDef* I2Cx, unsigned char data);
void lcd_Init(I2C_TypeDef* I2Cx);
void lcd_send(I2C_TypeDef* I2Cx, char str[]);
void lcd_msg(I2C_TypeDef* I2Cx, unsigned short line, unsigned short pos, char msg[]);
void lcd_move(I2C_TypeDef* I2Cx);
void lcd_clear (I2C_TypeDef* I2Cx);

