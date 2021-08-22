#include "lcd_i2c_user.h"


void i2c_lcd_send_byte ( char data) {
	i2c_start(I2C2);
	i2c_address(I2C2, 0x4e);
	i2c_data(I2C2, data);
	i2c_stop(I2C2);
}


void i2c_lcd_data ( unsigned char data) {
	i2c_lcd_send_byte(0x09);// Set RS High and RW Low
	delay_1Ms();
	i2c_lcd_send_byte(0x0D);//Enable LCD
	delay_1Ms();
	i2c_lcd_send_byte((data & 0x00f0) | 0x0D); //Send 4 high bit of data
	delay_1Ms();
	i2c_lcd_send_byte((data & 0x00f0) | 0x09);//Disable LCD
	delay_Ms(20);
	i2c_lcd_send_byte(((data<<4) & 0x00f0) | 0x0D);//Send 4 low bit of data
	delay_1Ms();
	i2c_lcd_send_byte(((data<<4) & 0x00f0) | 0x09);//Disable LCD
	delay_1Ms();
}

void i2c_lcd_cmd ( unsigned char data) {
	i2c_lcd_send_byte(0x08); //Set RS and RW low
	delay_Ms(1);
	i2c_lcd_send_byte(0x0C);//Enable LCD
	delay_Ms(1);
	i2c_lcd_send_byte((data & 0x00f0) | 0x0C);
	delay_Ms(1);
	i2c_lcd_send_byte((data & 0x00f0) | 0x08);
	delay_Ms(20);	
	i2c_lcd_send_byte(0x0C);
	delay_Ms(1);
	i2c_lcd_send_byte(((data<<4) & 0x00f0) | 0x0C);
	delay_Ms(1);
	i2c_lcd_send_byte(((data<<4) & 0x00f0) | 0x08);
	delay_Ms(1);
}
void lcd_Init() {
	Init_I2C(I2C2);
	delay_Ms(20);
	i2c_lcd_cmd(0x3C); // Set up moode 8 bit, 2 line and font
	delay_Ms(5);
	i2c_lcd_cmd(0x02);//Return home
	delay_Ms(5);
	i2c_lcd_cmd(0x2C); // Set up moode 4 bit, 2 line and font
	delay_Ms(5);
	i2c_lcd_cmd( 0x0C); //Set up display on, no cursor anh no blinking
	delay_Ms(5);
	i2c_lcd_cmd( 0x01);//Clear display
	delay_Ms(5);
	i2c_lcd_cmd(0x02);//Return home
	delay_Ms(5);
  i2c_lcd_cmd( 0x06);
	delay_Ms(5);
	
	
}

void lcd_send(char str[]) {	
	int i = 0;
	while(str[i]) {
		i2c_lcd_data(str[i]);
		i++;
	}
}

void lcd_msg( unsigned short line, unsigned short pos, char msg[]){
	
	int offset = 0;
	if (line == 1) {
		offset = 0;
	}
	else offset = 0x40;
	i2c_lcd_cmd( 0x80+pos+offset);
	lcd_send( msg);
}
void lcd_move() {
	while(1){
		i2c_lcd_cmd( 0x18);
			delay_Ms(300);
	}
}
