#include "usart_user.h"

void Init_USART(USART_TypeDef *usart, uint16_t USART_BaudRate){
			
	USART_InitTypeDef usart_init;
		
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //Enable Alternate function AFIO
	
	if (usart == USART1){
				RCC_APB2PeriphClockCmd (RCC_APB2Periph_USART1,ENABLE);
				Init_GPIO(GPIOA, GPIO_Mode_AF_PP, GPIO_Pin_9, GPIO_Speed_50MHz);        //Initilize for port A pin 9 is input push-pull for TX
	      Init_GPIO(GPIOA, GPIO_Mode_IPU, GPIO_Pin_10, GPIO_Speed_50MHz);         // Initilize for port A pin 10 is input push-pull for RX
				
		    USART_StructInit(&usart_init);
				usart_init.USART_BaudRate = USART_BaudRate;
				USART_Init(usart, &usart_init);
				USART_Cmd(USART1, ENABLE);
			}
			else if (usart == USART2) {
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE);
				Init_GPIO(GPIOA, GPIO_Mode_AF_PP, GPIO_Pin_2, GPIO_Speed_50MHz);        //Initilize for port A pin 2 is input push-pull for TX
	      Init_GPIO(GPIOA, GPIO_Mode_IPU, GPIO_Pin_3, GPIO_Speed_50MHz);         // Initilize for port A pin 3 is input push-pull for RX
				
		    USART_StructInit(&usart_init);
				usart_init.USART_BaudRate = USART_BaudRate;
				USART_Init(usart, &usart_init);
				USART_Cmd(USART2, ENABLE);
			}
			else if (usart == USART3) {
				RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, ENABLE);
				Init_GPIO(GPIOB, GPIO_Mode_AF_PP, GPIO_Pin_10, GPIO_Speed_50MHz);        //Initilize for port B pin 10 is input push-pull for TX
	      Init_GPIO(GPIOB, GPIO_Mode_IPU, GPIO_Pin_11, GPIO_Speed_50MHz);         // Initilize for port B pin 11 is input push-pull for RX
				
		    USART_StructInit(&usart_init);
				usart_init.USART_BaudRate = USART_BaudRate;
				USART_Init(usart, &usart_init);
				USART_Cmd(USART3, ENABLE);
			}
}

void USART_TX(USART_TypeDef *usart, char c) {
	if (usart == USART1) {
	  	while (!USART_GetFlagStatus(usart,USART_FLAG_TXE)) {} // Waitting for bit TXE set up to 1 _ Data is transferred to the shift register
			USART_SendData(usart, c);
	}
	else if (usart == USART2){
	   	while (!USART_GetFlagStatus(usart,USART_FLAG_TXE)) {} // Waitting for bit TXE set up to 1 _ Data is transferred to the shift register
			USART_SendData(usart, c);
	}
	else if (usart == USART3) {
		 	while (!USART_GetFlagStatus(usart,USART_FLAG_TXE)) {} // Waitting for bit TXE set up to 1 _ Data is transferred to the shift register
			USART_SendData(usart, c);
	}
}

char USART_RX  (USART_TypeDef *usart) {
	char c;
	if (usart == USART1) {
	  	while (!USART_GetFlagStatus(usart,USART_FLAG_RXNE)) {} // Waitting for bit RXNE set up to 1_Received data is ready to be read 
	}
	else if (usart == USART2){
	   	while (!USART_GetFlagStatus(usart,USART_FLAG_RXNE)) {} // Waitting for bit RXNE set up to 1_Received data is ready to be read 
	}
	else if (usart == USART3) {
		 	while (!USART_GetFlagStatus(usart,USART_FLAG_RXNE)) {} // Waitting for bit RXNE set up to 1_Received data is ready to be read 
			 
	}
	c = USART_ReceiveData(usart);
	return c;
}

void USART_data(USART_TypeDef *usart, char msg[]) {
	
	int i = 0;
	while (msg[i]){
		USART_TX(usart, msg[i]);
		delay_Ms(10);
		i++;
	}
	
}