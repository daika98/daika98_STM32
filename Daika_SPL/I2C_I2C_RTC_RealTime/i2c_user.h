#include "stm32f10x.h"                  // Device header
#include "stm32f10x_gpio.h"             // Keil::Device:StdPeriph Drivers:GPIO
#include "stm32f10x_rcc.h"              // Keil::Device:StdPeriph Drivers:RCC
#include "stm32f10x_i2c.h"              // Keil::Device:StdPeriph Drivers:I2C
#include "gpio_user.h"
#include "timer_user.h"

#define ACK 1
#define NACK 0

void Init_I2C(I2C_TypeDef* I2Cx);
void i2c_start(I2C_TypeDef* I2Cx);
void i2c_address(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction);
void i2c_send_data(I2C_TypeDef* I2Cx, uint8_t data);
void i2c_stop(I2C_TypeDef* I2Cx, uint32_t mode);
uint8_t i2c_recieve_data (I2C_TypeDef* I2Cx, uint8_t ACK_NACK);

