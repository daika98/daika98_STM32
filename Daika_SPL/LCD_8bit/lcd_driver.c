#include "lcd_driver.h"

GPIO_InitTypeDef gpio_a;

void Set_GPIO_PP_OUT50(GPIO_InitTypeDef gpio) {//Set pins from A0 to A10 - OUT50MHz PP
	RCC_APB2PeriphClockCmd (RCC_APB2Periph_GPIOA,ENABLE);
	gpio.GPIO_Mode = GPIO_Mode_Out_PP;
	gpio.GPIO_Pin = GPIO_Pin_0;
	gpio.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_1;
	GPIO_Init(GPIOA,&gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_2;
	GPIO_Init(GPIOA,&gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_3;
	GPIO_Init(GPIOA,&gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_4;
	GPIO_Init(GPIOA,&gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_5;
	GPIO_Init(GPIOA,&gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_6;
	GPIO_Init(GPIOA,&gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_7;
	GPIO_Init(GPIOA,&gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_8;
	GPIO_Init(GPIOA,&gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_9;
	GPIO_Init(GPIOA,&gpio);
	
	gpio.GPIO_Pin = GPIO_Pin_10;
	GPIO_Init(GPIOA,&gpio);
	
}

void lcd_rs(unsigned short signal) {//Set pin RS 1:Data 0: Command
	if (signal == 1) {
		GPIO_SetBits(GPIOA, GPIO_Pin_8);
	}
	else {
		GPIO_ResetBits(GPIOA, GPIO_Pin_8);
	}
}

void lcd_rw(unsigned short signal) {//Set pin RW 1: Read 0: Write
	if (signal == 1) {
		GPIO_SetBits(GPIOA, GPIO_Pin_9);
	}
	else {
		GPIO_ResetBits(GPIOA, GPIO_Pin_9);
	}
}

void lcd_enable(unsigned short signal) {//Enable LCD
	if (signal == 1) {
		GPIO_SetBits(GPIOA, GPIO_Pin_10);
	}
	else {
		GPIO_ResetBits(GPIOA, GPIO_Pin_10);
	}
}

void lcd_data (unsigned short data) {
	lcd_rs(HIGH);
	lcd_rw(LOW);
	delay_ms(1);
	lcd_enable(HIGH);
	delay_ms(1);
	GPIOA->ODR &= 0xff00;
	GPIOA->ODR |= data;
	delay_ms(1);
	lcd_enable(LOW);
	
}

void lcd_cmd (unsigned short data) {
	lcd_rs(LOW);
	lcd_rw(LOW);
	delay_ms(1);
	lcd_enable(HIGH);
	delay_ms(1);
	GPIOA->ODR &= 0xff00;
	GPIOA->ODR |= data;
	delay_ms(1);
	lcd_enable(LOW);
}
void lcd_Init() {
	lcd_cmd(0x3C); // Set up moode 8 bit, 2 line and font
	delay_ms(1);
	lcd_cmd(0x0C); //Set up display on, no cursor anh no blinking
	delay_ms(1);
	lcd_cmd(0x01);//Clear display
	delay_ms(1);
	lcd_cmd(0x02);//Return home
	delay_ms(1);
	lcd_cmd(0x06);
	delay_ms(1);
	
	
}

void lcd_send(char str[]) {	
	int i = 0;
	while(str[i]) {
		lcd_data(str[i]);
		i++;
	}
}

void lcd_msg(unsigned short line, unsigned short pos, char msg[]){
	
	int offset = 0;
	if (line == 1) {
		offset = 0;
	}
	else offset = 0x40;
	lcd_cmd(0x80+pos+offset);
	lcd_send(msg);
}
void lcd_move(char msg[]) {
	while(1){
		lcd_cmd(0x18);
		delay_ms(200);
	}
}