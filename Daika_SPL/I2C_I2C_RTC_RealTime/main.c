#include "stm32f10x.h"                  // Device header
#include "gpio_user.h"
#include "timer_user.h"
#include "usart_user.h"
#include "lcd_i2c_user.h"
#include "i2c_user.h"
#include "i2c_ds3231_user.h"

/*Daa of date and time Use only first time*/
uint8_t year = 21;
uint8_t month =8;
uint8_t date = 10;
uint8_t day  = 3;
uint8_t hour = 13;
uint8_t minute = 25;
uint8_t second = 20;

uint8_t time_table[7];
char time_str[15];
char time_data[5];
char day_of_week[5];
char day_char;

int main(void) {
	Delay_Timer_Init();
	Init_I2C(I2C2);
 // Init_USART(USART2, 9600);//If you want to use usart to display data
	lcd_Init(I2C1);          //If you want to use lcd to display data
	
	//USART_data(USART2,"Hello guys\n");
	
	//ds3231_update(I2C2, second, minute, hour, day, date, month, year); // Use only for update data
		Init_GPIO(GPIOC,GPIO_Mode_Out_PP,GPIO_Pin_13, GPIO_Speed_50MHz);
	while (1) {

		ds3231_getData(I2C2, time_table);  // Get data from RTC3231
 		delay_Ms(50);
		
		int2char(ds3231_reverter(time_table[2]), time_str);
		catenate_str(time_str, ":");
		int2char(ds3231_reverter(time_table[1]), time_data);
		catenate_str(time_str, time_data);
		str_empty(time_data);
		catenate_str(time_str, ":");
		int2char(ds3231_reverter(time_table[0]), time_data);
		catenate_str(time_str, time_data);
		str_empty(time_data);
		lcd_msg(I2C1, 1, 4, time_str);
		
		str_empty(time_str);
		
		if (time_table[3] == 0x01) {
			lcd_msg(I2C1, 2, 2, " CN,");
		} else {
			lcd_msg(I2C1, 2, 2, "Th");
			day_char = time_table[3] + 0x30;
			day_of_week[0] = day_char;
			lcd_msg(I2C1, 2, 4, day_of_week);
			lcd_msg(I2C1, 2, 5, ",");	
			str_empty(day_of_week);
		}
		delay_Ms(50);
		GPIO_ResetBits(GPIOC, GPIO_Pin_13);
		
		int2char(ds3231_reverter(time_table[4]), time_str);
		catenate_str(time_str, "/");
		int2char(ds3231_reverter(time_table[5]), time_data);
		catenate_str(time_str, time_data);
		str_empty(time_data);
		catenate_str(time_str, "/");
		int2char(ds3231_reverter(time_table[6]), time_data);
		catenate_str(time_str, time_data);
		str_empty(time_data);
		lcd_msg(I2C1, 2, 6, time_str);
		str_empty(time_str);
		
 		
		
		delay_Ms(50);
		GPIO_SetBits(GPIOC, GPIO_Pin_13);
	}
}
