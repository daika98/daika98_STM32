#include "lcd_i2c_user.h"


void i2c_lcd_send_byte (I2C_TypeDef* I2Cx, char data) {
	i2c_start(I2Cx);
	i2c_address(I2Cx, 0x4e,I2C_Direction_Transmitter);
	i2c_send_data(I2Cx, data);
	i2c_stop(I2Cx,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED );
}


void i2c_lcd_data (I2C_TypeDef* I2Cx, unsigned char data) {
	i2c_lcd_send_byte(I2Cx, 0x09);// Set RS High and RW Low
	delay_1Ms();
	i2c_lcd_send_byte( I2Cx, 0x0D);//Enable LCD
	delay_1Ms();
	i2c_lcd_send_byte( I2Cx, (data & 0x00f0) | 0x0D); //Send 4 high bit of data
	delay_1Ms();
	i2c_lcd_send_byte( I2Cx, (data & 0x00f0) | 0x09);//Disable LCD
	delay_Ms(20);
	i2c_lcd_send_byte( I2Cx, ((data<<4) & 0x00f0) | 0x0D);//Send 4 low bit of data
	delay_1Ms();
	i2c_lcd_send_byte( I2Cx, ((data<<4) & 0x00f0) | 0x09);//Disable LCD
	delay_1Ms();
}

void i2c_lcd_cmd (I2C_TypeDef* I2Cx, unsigned char data) {
	i2c_lcd_send_byte(I2Cx, 0x08); //Set RS and RW low
	delay_Ms(1);
	i2c_lcd_send_byte(I2Cx, 0x0C);//Enable LCD
	delay_Ms(1);
	i2c_lcd_send_byte(I2Cx, (data & 0x00f0) | 0x0C);
	delay_Ms(1);
	i2c_lcd_send_byte(I2Cx, (data & 0x00f0) | 0x08);
	delay_Ms(20);	
	i2c_lcd_send_byte(I2Cx,0x0C);
	delay_Ms(1);
	i2c_lcd_send_byte(I2Cx, ((data<<4) & 0x00f0) | 0x0C);
	delay_Ms(1);
	i2c_lcd_send_byte(I2Cx, ((data<<4) & 0x00f0) | 0x08);
	delay_Ms(1);
}
void lcd_Init(I2C_TypeDef* I2Cx) {
	Init_I2C(I2Cx);
	delay_Ms(20);
	i2c_lcd_cmd(I2Cx, 0x3C); // Set up moode 8 bit, 2 line and font
	delay_Ms(5);
	i2c_lcd_cmd(I2Cx, 0x02);//Return home
	delay_Ms(5);
	i2c_lcd_cmd(I2Cx, 0x2C); // Set up moode 4 bit, 2 line and font
	delay_Ms(5);
	i2c_lcd_cmd(I2Cx, 0x0C); //Set up display on, no cursor anh no blinking
	delay_Ms(5);
	i2c_lcd_cmd(I2Cx, 0x01);//Clear display
	delay_Ms(5);
	i2c_lcd_cmd(I2Cx, 0x02);//Return home
	delay_Ms(5);
  i2c_lcd_cmd(I2Cx, 0x06);
	delay_Ms(5);
	
	
}

void lcd_clear (I2C_TypeDef* I2Cx) {
	i2c_lcd_cmd(I2Cx, 0x01);//Clear display
	delay_Ms(5);
}
void lcd_send(I2C_TypeDef* I2Cx, char str[]) {	
	int i = 0;
	while(str[i]) {
		i2c_lcd_data(I2Cx, str[i]);
		i++;
	}
}

void lcd_msg(I2C_TypeDef* I2Cx, unsigned short line, unsigned short pos, char msg[]){
	
	int offset = 0;
	if (line == 1) {
		offset = 0;
	}
	else offset = 0x40;
	i2c_lcd_cmd(I2Cx, 0x80+pos+offset);
	lcd_send(I2Cx, msg);
	delay_Ms(5);
}
void lcd_move(I2C_TypeDef* I2Cx) {
	while(1){
		i2c_lcd_cmd(I2Cx, 0x18);
			delay_Ms(300);
	}
}
