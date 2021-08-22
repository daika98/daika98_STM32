#include "i2c.h"

void i2c_init(I2C_TypeDef* I2Cx) { 

  GPIO_InitTypeDef  gpio_init;
	I2C_InitTypeDef   i2c_init;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //Enable Alternate function AFIO
	if (I2Cx == I2C1) {
		/*Set up GPIOB for I2C1*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//Enable clock GPIOB
	gpio_init.GPIO_Pin = GPIO_Pin_6 |  GPIO_Pin_7;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB,&gpio_init);
		/*Set up I2C*/
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_I2C1, ENABLE);//Enable clock I2C
	I2C_SoftwareResetCmd(I2C1, ENABLE); //I2C peripheral under reset
	I2C_SoftwareResetCmd(I2C1, DISABLE);//Have to clear bit software reset
	
	i2c_init.I2C_Ack = I2C_Ack_Enable;//Acknowleage returned after a byte is received
	i2c_init.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//7 bit slave address
	i2c_init.I2C_ClockSpeed = 100000;//Frequency equal 100kHz
	i2c_init.I2C_Mode = I2C_Mode_I2C;//Enable mode I2C
	I2C_Init(I2C1,&i2c_init);
	}
	else {
	/*Set up GPIOB for I2C2*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);//Enable clock GPIOB
	gpio_init.GPIO_Pin = GPIO_Pin_10 |  GPIO_Pin_11;
	gpio_init.GPIO_Speed = GPIO_Speed_50MHz;
	gpio_init.GPIO_Mode = GPIO_Mode_AF_OD;
	GPIO_Init(GPIOB,&gpio_init);
		/*Set up I2C*/
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_I2C2, ENABLE);//Enable clock I2C
	I2C_SoftwareResetCmd(I2C2, ENABLE); //I2C peripheral under reset
	I2C_SoftwareResetCmd(I2C2, DISABLE);//Have to clear bit software reset
	
	i2c_init.I2C_Ack = I2C_Ack_Enable;//Acknowleage returned after a byte is received
	i2c_init.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//7 bit slave address
	i2c_init.I2C_ClockSpeed = 100000;//Frequency equal 100kHz
	i2c_init.I2C_Mode = I2C_Mode_I2C;//Enable mode I2C
	I2C_Init(I2C2,&i2c_init);
	}
}


void i2c_start(I2C_TypeDef* I2Cx){
	if (I2Cx == I2C1) {
		I2C_GenerateSTART (I2C1,ENABLE); 
	while (!I2C_CheckEvent (I2C1,I2C_EVENT_MASTER_MODE_SELECT)) {} //Wait until BUSY, MSL and SB flag set-Event EV5 
	}
	else {
	I2C_GenerateSTART (I2C2,ENABLE);
	while (!I2C_CheckEvent (I2C2,I2C_EVENT_MASTER_MODE_SELECT)) {}
	}
}

void i2c_address(I2C_TypeDef* I2Cx, uint8_t address){
		if (I2Cx == I2C1) {
			I2C_Send7bitAddress (I2C1,address, 	I2C_Direction_Transmitter);
      while (!I2C_CheckEvent (I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {} //Wait until BUSY, MSL, ADDR, TXE and TRA flags set - Event EV6
}
		else {
			I2C_Send7bitAddress (I2C2,address, 	I2C_Direction_Transmitter);
      while (!I2C_CheckEvent (I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {}
		}
}
void i2c_data(I2C_TypeDef* I2Cx, char data) {
	if (I2Cx == I2C1) {
		while(!I2C_GetFlagStatus (I2C1, I2C_FLAG_TXE)){} // Wait until Flaf TXE set - Data register empty
		I2C_SendData (I2C1, data);
		while(!I2C_GetFlagStatus (I2C1, I2C_FLAG_TXE)){}	
		}
		else {
		while(!I2C_GetFlagStatus (I2C2, I2C_FLAG_TXE)){}
		I2C_SendData (I2C2, data);
		while(!I2C_GetFlagStatus (I2C2, I2C_FLAG_TXE)){}	
}
}
void i2c_stop(I2C_TypeDef* I2Cx){
	if (I2Cx == I2C1) {
		while (!I2C_CheckEvent (I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {} //Wait until RA, BUSY, MSL, TXE and BTF flags set - Event EV8_2
	I2C_GenerateSTOP (I2C1, ENABLE);	
	}
	else {
	while (!I2C_CheckEvent (I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {}
	I2C_GenerateSTOP (I2C2, ENABLE);	
	}
	}

void i2c_send_data (I2C_TypeDef* I2Cx,uint8_t address, uint8_t READ_WRITE, char data[]) {
	int i = 0;
	
	i2c_start(I2Cx);
	i2c_address(I2Cx, address);
	while (data[i]) {
		i2c_data(I2Cx, data[i]);
		i++;
	}
	i2c_stop(I2Cx);
}

