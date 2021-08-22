#include "spi_drive.h"
#include "stm32f10x.h"                  // Device header
#include "gpio_drive.h"
void Init_SPI(unsigned short spi) {
	
	if (spi == SPI_1) {
	RCC->APB2ENR |= RCC_APB2ENR_SPI1EN; // ( or RCC->APB2ENR |= 1<<12;)  //Enable SPI1
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;     //Enable Alternate function
			// Set up pins for SPI1
	Init_GPIO(Port_A, 4, OUT_50, OUT_GP_PP); // pin 4 for SS
	Init_GPIO(Port_A, 5, OUT_50, OUT_AF_PP); // pin 5 for SCK
	Init_GPIO(Port_A, 6, IN, IN_PP);         // pin 6 for MISO
	Init_GPIO(Port_A, 7, OUT_50, OUT_AF_PP); // pin 7 for MOSI
	
	SPI1->CR2 |= 1<<2;  //SS Output enable

	SPI1->CR1 |= 0<<11; //Data frame 8 bit
	SPI1->CR1 |= 0<<7; // MSB transmitted first
	//SPI1->CR1 |= 1<<8 | 1<<9;// Control by software 
	SPI1->CR1 |= 0x31;   // Select Baud rate control / 2
	SPI1->CR1 |= 1<<2 ;  // Select Master mode
	SPI1->CR1 |= 0;     //CPHA = 0
	SPI1->CR1 |= 0<<1;  //CPOL = 0
	SPI1->CR1 |= 1<<6;  // Enable SPI1
		Write_GPIO(Port_A, 4, 1);
	}
	else if (spi == SPI_2) {
	RCC->APB1ENR |= RCC_APB1ENR_SPI2EN;   //Enable SPI2
	RCC->APB2ENR |= RCC_APB2ENR_AFIOEN;     //Enable Alternate function
			// Set up pins for SPI2

	Init_GPIO(Port_B, 13, OUT_50, OUT_AF_PP); // pin 13 for SCK
	Init_GPIO(Port_B, 14, IN, IN_PP);         // pin 14 for MISO
	Init_GPIO(Port_B, 15, OUT_50, OUT_AF_PP); // pin 15 for MOSI
	
	//SPI1->CR2 |= 1<<2;  //SS Output enable

	SPI2->CR1 |= 0<<11; //Data frame 8 bit
	SPI2->CR1 |= 0<<7; // MSB transmitted first
	SPI2->CR1 |= 1<<8 | 1<<9;// Control by software 
	SPI2->CR1 |= 0x31;   // Select Baud rate control / 2
	SPI2->CR1 |= 1<<2 ;  // Select Master mode
	SPI2->CR1 |= 0;     //CPHA = 0
	SPI2->CR1 |= 0<<1;  //CPOL = 0
	SPI2->CR1 |= 1<<6;  // Enable SPI2
	}
	
}

void SPI_Transfer_Data(unsigned short spi, char str[]) {
	  int i = 0;
	while (str[i] != '\0')
	
	 	Write_GPIO(Port_A, 4, 0);
	  SPI1->DR = str[i];
		while(SPI1->SR & (1<<7)){}
			i++;
		Write_GPIO(Port_A, 4, 1);
		}


