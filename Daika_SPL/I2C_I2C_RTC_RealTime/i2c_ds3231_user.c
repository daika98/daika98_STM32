#include "i2c_ds3231_user.h"


void ds3231_tx(I2C_TypeDef* I2Cx, uint8_t add_register, uint8_t data) {
  /*Refer to RTC3231 datasheet, Figure 3*/
	i2c_start(I2Cx);
	i2c_address(I2Cx, 0xD0, I2C_Direction_Transmitter );  // Send address of RTC3231
	i2c_send_data(I2Cx, add_register);//Send local address of RTC3231
	i2c_send_data(I2Cx, data);  
	i2c_stop(I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED ); //Function stop for Master transmiiter
	
}
void ds3231_rx(I2C_TypeDef* I2Cx, uint8_t add_register, uint8_t *data, uint16_t length) {
  
	int i;
	/*Need again send address of RTC3231 and local address. Refer to RTC3231 datasheet, Figure 5 */
	i2c_start(I2Cx);
	i2c_address(I2Cx, 0xD0, I2C_Direction_Transmitter);
	i2c_send_data(I2Cx, add_register);
	
	i2c_start(I2Cx);
	i2c_address(I2Cx, 0xD0, I2C_Direction_Receiver);
	for(i=0;i<(length-1);i++)
	{
		data[i] = i2c_recieve_data(I2Cx,ACK);
	}
	data[i] = i2c_recieve_data(I2Cx,NACK);
	i2c_stop(I2Cx, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED );//ATTENTION Function stop for Master receiver
}

uint8_t ds3231_converter (uint8_t data) {
	uint8_t data_converter = 0;
	data_converter = data / 10;
	data_converter = data_converter<<4;
	data_converter |= (data % 10);	
	return data_converter;
}

void ds3231_update_second (I2C_TypeDef* I2Cx, uint8_t second) {
	ds3231_tx(I2Cx, 0x00, ds3231_converter(second));
		
}
void ds3231_update_minute (I2C_TypeDef* I2Cx, uint8_t minute) {
	ds3231_tx(I2Cx, 0x01, ds3231_converter(minute));
}
void ds3231_update_hour (I2C_TypeDef* I2Cx, uint8_t hour) {
	ds3231_tx(I2Cx, 0x02, ds3231_converter(hour));
}

void ds3231_update_day (I2C_TypeDef* I2Cx, uint8_t day) {
	ds3231_tx(I2Cx, 0x03, day);
}
void ds3231_update_date (I2C_TypeDef* I2Cx, uint8_t date) {
	ds3231_tx(I2Cx, 0x04, ds3231_converter(date));
}

void ds3231_update_month (I2C_TypeDef* I2Cx, uint8_t month) {
	ds3231_tx(I2Cx, 0x05, ds3231_converter(month));
}

void ds3231_update_year (I2C_TypeDef* I2Cx, uint8_t year) {
	ds3231_tx(I2Cx, 0x06, ds3231_converter(year));
}

void ds3231_update(I2C_TypeDef* I2Cx, uint8_t second, uint8_t minute,
	uint8_t hour, uint8_t day, uint8_t date, uint8_t month,uint8_t year){
		ds3231_update_second (I2Cx, second);
		ds3231_update_minute (I2Cx, minute);
		ds3231_update_hour (I2Cx, hour);
		ds3231_update_day(I2Cx, day);
		ds3231_update_date (I2Cx,date);
		ds3231_update_month (I2Cx, month);
		ds3231_update_year (I2Cx, year);
		
	}

uint8_t ds3231_reverter(uint8_t time)
{
	uint8_t update = 0;
	update	= time >> 4;
	update *= 10;
	update += (time & 0x0F);
	return update;
}
void ds3231_getData (I2C_TypeDef* I2Cx, uint8_t *data){
	ds3231_rx(I2Cx, 0x00, data, 7);
}
void display_time(uint8_t data_time, uint8_t line, uint8_t pos) {
	char time_str[2];
					int2char(data_time, time_str);
					lcd_msg(I2C1, line, pos, time_str );
					//USART_data (USART2, time_str);
					str_empty(time_str);
	
}