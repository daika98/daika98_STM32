#include "i2c_user.h"

void Init_I2C(I2C_TypeDef* I2Cx) { 

  GPIO_InitTypeDef  gpio_init;
	I2C_InitTypeDef   i2c_init;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //Enable Alternate function AFIO
	if (I2Cx == I2C1) {
		/*Set up GPIOB for I2C1*/
		
	Init_GPIO(GPIOB, GPIO_Mode_AF_OD, GPIO_Pin_6 |  GPIO_Pin_7, GPIO_Speed_50MHz);
		/*Set up I2C*/
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_I2C1, ENABLE);//Enable clock I2C
	I2C_SoftwareResetCmd(I2C1, ENABLE); //I2C peripheral under reset
	I2C_SoftwareResetCmd(I2C1, DISABLE);//Have to clear bit software reset
	
	I2C_StructInit(&i2c_init);
	i2c_init.I2C_Ack = I2C_Ack_Enable;//Acknowleage returned after a byte is received
	i2c_init.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//7 bit slave address
	i2c_init.I2C_ClockSpeed = 100000;//Frequency equal 100kHz
	i2c_init.I2C_Mode = I2C_Mode_I2C;//Enable mode I2C
	I2C_Init(I2C1,&i2c_init);
	I2C_Cmd(I2C1, ENABLE);
	}
	else {
	/*Set up GPIOB for I2C2*/
		
	Init_GPIO(GPIOB, GPIO_Mode_AF_OD, GPIO_Pin_10 |  GPIO_Pin_11, GPIO_Speed_50MHz);

		/*Set up I2C*/
	RCC_APB1PeriphClockCmd (RCC_APB1Periph_I2C2, ENABLE);//Enable clock I2C
	I2C_SoftwareResetCmd(I2C2, ENABLE); //I2C peripheral under reset
	I2C_SoftwareResetCmd(I2C2, DISABLE);//Have to clear bit software reset
	
	I2C_StructInit(&i2c_init);
	i2c_init.I2C_Ack = I2C_Ack_Enable;//Acknowleage returned after a byte is received
	i2c_init.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;//7 bit slave address
	i2c_init.I2C_ClockSpeed = 100000;//Frequency equal 100kHz
	i2c_init.I2C_Mode = I2C_Mode_I2C;//Enable mode I2C
	I2C_Init(I2C2,&i2c_init);
	I2C_Cmd(I2C2, ENABLE);

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

void i2c_address(I2C_TypeDef* I2Cx, uint8_t address, uint8_t direction){
		if (I2Cx == I2C1) {
			if (direction == I2C_Direction_Transmitter){
			I2C_Send7bitAddress (I2C1,address, 	I2C_Direction_Transmitter);
      while (!I2C_CheckEvent (I2C1, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {} //Wait until BUSY, MSL, ADDR, TXE and TRA flags set - Event EV6
			} 
			else if (direction == I2C_Direction_Receiver){                                    
			I2C_Send7bitAddress (I2C1,address, 	I2C_Direction_Receiver);
      while (!I2C_CheckEvent (I2C1, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED )) {}  
		
			}
			}
		else {
			if (direction == I2C_Direction_Transmitter){
			I2C_Send7bitAddress (I2C2,address, 	I2C_Direction_Transmitter);
      while (!I2C_CheckEvent (I2C2, I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED)) {} //Wait until BUSY, MSL, ADDR, TXE and TRA flags set - Event EV6
			} 
			else if (direction == I2C_Direction_Receiver){
			I2C_Send7bitAddress (I2C2,address, 	I2C_Direction_Receiver);
      while (!I2C_CheckEvent (I2C2, I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED )) {} 
		
		}
		}
		}
		
void i2c_send_data(I2C_TypeDef* I2Cx, uint8_t data) {
	if (I2Cx == I2C1) {
		while (!I2C_CheckEvent (I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTING )) {} // Wait event EV8
		I2C_SendData (I2C1, data);
		}
		else {
		while (!I2C_CheckEvent (I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTING )) {}
		I2C_SendData (I2C2, data);
}
}
void i2c_stop(I2C_TypeDef* I2Cx, uint32_t mode){
	if (I2Cx == I2C1) {
		 
		if (mode == I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) {   // For Master transmitter
				while (!I2C_CheckEvent (I2C1, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {}
				}
	  else {  // For Master receiver
				while(!(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))) {}
				}
				 I2C_GenerateSTOP (I2C1, ENABLE);
			}
	else {
		if (mode == I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED) {
				while (!I2C_CheckEvent (I2C2, I2C_EVENT_MASTER_BYTE_TRANSMITTED)) {}
				}
	  else {
					while(!(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED))) {}
				}
				 I2C_GenerateSTOP (I2C2, ENABLE);
	}
}


uint8_t i2c_recieve_data (I2C_TypeDef* I2Cx, uint8_t ACK_NACK) {
   uint8_t data;
  if (I2Cx == I2C1){
		I2C_AcknowledgeConfig (I2C1, ENABLE);
		while(!(I2C_CheckEvent(I2C1, I2C_EVENT_MASTER_BYTE_RECEIVED))) {} //Wait event EV7
		data = I2C_ReceiveData(I2C1);
		if (ACK_NACK == NACK) { //For the last byte have to enable ACK bit
		I2C_AcknowledgeConfig(I2C1, DISABLE);
	}
} 
	else {
		I2C_AcknowledgeConfig (I2C2, ENABLE);
		while(!(I2C_CheckEvent(I2C2, I2C_EVENT_MASTER_BYTE_RECEIVED))) {}
		data = I2C_ReceiveData(I2C2);
		if (ACK_NACK == NACK) {
			I2C_AcknowledgeConfig(I2C2, DISABLE);
	}
}
	return data;
}
	
