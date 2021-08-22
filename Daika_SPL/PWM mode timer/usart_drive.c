#include "stm32f10x.h"                  // Device header
#include "gpio_drive.h"
#include "usart_drive.h"
unsigned long Find_BaudRate(unsigned short usart, unsigned long baud_Rate);

void Init_USART(unsigned short usart, unsigned long baud_Rate){
			unsigned long val;
			val = Find_BaudRate(usart, baud_Rate);
	    RCC->APB2ENR |= 1;                         //Enable AFIO
			if (usart == USART_1){
				__disable_irq();
				RCC->APB2ENR |= (1<<14);                   //Enable USART_1
				Init_GPIO (Port_A, 9, OUT_50, OUT_AF_PP);  //Initilize for port A pin 9 is output push-pull for TX
				Init_GPIO (Port_A, 10, IN, IN_PP);          // Initilize for port A pin 10 is input push-pull for RX
				USART1->BRR = val;                       // Setup Baud rate
				USART1->CR1 |= (1<<13) | (1<<2) | (1<<3);  // Enable USART, USART Transmit and USART Receive
			  USART1->CR1 |= (1<<5);                    //Enable interrupt function if RXNE = 1
				NVIC_EnableIRQ( USART1_IRQn);             
				__enable_irq();
				
			}
			else if (usart == USART_2) {
				__disable_irq();
				RCC->APB1ENR |= (1<<17);                   //Enable USART_2
				Init_GPIO (Port_A, 2, OUT_50, OUT_AF_PP);  //Initilize for port A pin 2 is output push-pull for TX
				Init_GPIO (Port_A, 3, IN, IN_PP);          // Initilize for port A pin 3 is input push-pull for RX
				USART2->BRR = val;                       // Setup Baud rate
				USART2->CR1 |= (1<<13) | (1<<2) | (1<<3);  // Enable USART, USART Transmit and USART Receive
			  USART2->CR1 |= (1<<5);                    //Enable interrupt function if RXNE = 1
				NVIC_EnableIRQ( USART2_IRQn); 
				__enable_irq();
			}
			else if (usart == USART_3) {
				__disable_irq();
				RCC->APB1ENR |= (1<<18);                   //Enable USART_3
				Init_GPIO (Port_B, 10, OUT_50, OUT_AF_PP);  //Initilize for port B pin 10 is output push-pull for TX
				Init_GPIO (Port_B, 11, IN, IN_PP);          // Initilize for port B pin 11 is input push-pull for RX
				USART3->BRR = val;                       // Setup Baud rate
				USART3->CR1 |= (1<<13) | (1<<2) | (1<<3);  // Enable USART, USART Transmit and USART Receive
			  USART3->CR1 |= (1<<5);                    //Enable interrupt function if RXNE = 1
				NVIC_EnableIRQ( USART3_IRQn); 
				__enable_irq();
			}
}

unsigned long Find_BaudRate(unsigned short usart, unsigned long baud_Rate) {
			unsigned long frequency;
			double frequency_double;
			unsigned int div;
			unsigned int frac;
			double frac_1;
			double div_double;
			double sub;
			unsigned long final;
			
			frequency = 36000000;
			frequency_double = 36000000.00;
			if (usart == USART_1) {
				frequency = 72000000;
				frequency_double = 72000000.00;
			}
			div = frequency / (16 * baud_Rate);
			div_double = frequency_double / (16 * baud_Rate);
			frac = (unsigned int)((div_double - div) * 16);
			frac_1 = (div_double - div) * 16;
			sub = frac_1 - frac;
			if (sub >= 0.5) {
				frac = frac + 1;
					 if (frac == 16){
						 div++;
					 }
			}
			
			final = div<<4;
			final += frac;
			return final;
		}
	
void USART_TX(unsigned short usart, char c) {
	if (usart == USART_1) {
	  	while (!(USART1->SR & (1<<7))) {} // Waitting for bit TXE set up to 1 _ Data is transferred to the shift register
			USART1->DR = c;
	}
	else if (usart == USART_2){
	    while (!(USART2->SR & (1<<7))) {}
			USART2->DR = c;
	}
	else if (usart == USART_3) {
		 while (!(USART3->SR & (1<<7))) {}
			USART3->DR = c;
	}
}

char USART_RX(unsigned short usart) {
	char c;
	if (usart == USART_1) {
	  	while (!(USART1->SR & (1<<5))) {} // Waitting for bit RXNE set up to 1_Received data is ready to be read 
			c = USART1->DR;
	}
	else if (usart == USART_2){
	    while (!(USART2->SR & (1<<5))) {}
			c = USART2->DR;
	}
	else if (usart == USART_3) {
		 while (!(USART3->SR & (1<<5))) {}
			c = USART3->DR;
	}
	return c;
}	

void USART_TX_STR(unsigned short usart, char str[]){
	int i = 0;
	while(str[i] != '\0')
	{
		USART_TX(usart,str[i]);
		i++;
	//	delay_ms(10);
	}
}

/* 
0- Current count of string
1- USART's Target 
2- Same baud Rate 1:Yes 0:No
3- Recieve signal
4- Teminator char(\0 or \n)
5- Interrupt(1) or Terminator(0) 
6- Timer counter
7- Timer counter copy
*/
void USART_Send( unsigned short usart, unsigned short manager[], char str[] )
{
	if (manager[2] == 0) {
		str[manager[0]] = USART_RX(usart);
		if (str[manager[0]] == '\n') {
			manager[0] = 0;
			manager[3] = 1;
		} else {
			manager[0]++;
		}
	}
	else {
	USART_TX(manager[1], USART_RX(usart));
	
	}
}

void Clear_str(char str[]){
 int i = 0;
 while (str[i] != '\0') {
	 str[i] = '\0';
	 i++;
 }

	
}

