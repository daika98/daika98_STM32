#include "stm32f10x.h"                  // Device header
#include "gpio_user.h"
#include "timer_user.h"
#include "lcd_i2c_user.h"
#include "usart_user.h"

void   Get_Address_I2C();
void i2c_add(I2C_TypeDef* I2Cx, uint8_t address);

int main(void){
	
	Init_GPIO(GPIOC,GPIO_Mode_Out_PP,GPIO_Pin_13,GPIO_Speed_50MHz);
	Delay_Timer_Init();
	Init_I2C(I2C2);
	Init_USART(USART2, 9600);
		USART_TX(USART2, 'K');
	
	
  Get_Address_I2C();
  
	
	while (1) {
  GPIO_SetBits (GPIOC,GPIO_Pin_13);
	delay_Ms(500);
	GPIO_ResetBits (GPIOC,GPIO_Pin_13);
	delay_Ms(500);
		}
	}

	void   Get_Address_I2C()
{        int a=0; 
         for (int i=0;i<256;i++)
   {
            i2c_start(I2C2);
						i2c_add(I2C2, i);
     }
}

void i2c_add(I2C_TypeDef* I2Cx, uint8_t address){
		if (I2Cx == I2C1) {
		I2C_Send7bitAddress (I2C1,address, 	I2C_Direction_Transmitter);
		    delay_Ms(50);
            if (I2C_CheckEvent (I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
         {
					 USART_TX(USART2, address);
				 }
			}
		else {
			I2C_Send7bitAddress (I2C2,address, 	I2C_Direction_Transmitter);
		    delay_Ms(50);
            if (I2C_CheckEvent (I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
         {
					// USART_data(USART2, "Address of I2C: ");
					 USART_TX(USART2, address);
					// USART_TX(USART2, '\n');
				 }
			}
}