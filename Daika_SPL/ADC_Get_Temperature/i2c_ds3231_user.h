#include "i2c_user.h"
#include "char_user.h"
#include "usart_user.h"
#include "lcd_i2c_user.h"


void ds3231_tx(I2C_TypeDef* I2Cx, uint8_t add_register, uint8_t data);// To transmit data
void ds3231_rx(I2C_TypeDef* I2Cx, uint8_t add_register, uint8_t data[], uint16_t length);  // To receive data

uint8_t ds3231_converter (uint8_t data); // Convert data from real data to RTCdata format
uint8_t ds3231_reverter(uint8_t time);   // COnvert data from RTCdata format to real data
/*Function for update data*/
void ds3231_update_second (I2C_TypeDef* I2Cx, uint8_t second);
void ds3231_update_minute (I2C_TypeDef* I2Cx, uint8_t minute);
void ds3231_update_hour (I2C_TypeDef* I2Cx, uint8_t hour);
void ds3231_update_day (I2C_TypeDef* I2Cx, uint8_t day);
void ds3231_update_date (I2C_TypeDef* I2Cx, uint8_t date);
void ds3231_update_month (I2C_TypeDef* I2Cx, uint8_t month);
void ds3231_update_year (I2C_TypeDef* I2Cx, uint8_t year);
void ds3231_update(I2C_TypeDef* I2Cx, uint8_t second, uint8_t minute,
	uint8_t hour, uint8_t day, uint8_t date, uint8_t month,uint8_t year);

void ds3231_getData (I2C_TypeDef* I2Cx, uint8_t data[]);
void display_time(uint8_t data_time, uint8_t line, uint8_t pos);