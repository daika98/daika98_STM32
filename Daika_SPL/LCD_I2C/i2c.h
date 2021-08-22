#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_i2c.h"              // Keil::Device:StdPeriph Drivers:I2C
#include "gpio_drive.h"
#include "timer.h"


void i2c_init(I2C_TypeDef* I2Cx);
void i2c_start(I2C_TypeDef* I2Cx);
void i2c_address(I2C_TypeDef* I2Cx, uint8_t address);
void i2c_data(I2C_TypeDef* I2Cx, char data);
void i2c_stop(I2C_TypeDef* I2Cx);
void i2c_send_data (I2C_TypeDef* I2Cx,uint8_t address, uint8_t READ_WRITE, char data[]);

