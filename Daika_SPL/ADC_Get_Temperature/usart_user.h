#include "stm32f10x.h"                  // Device header
#include "gpio_user.h"
#include "timer_user.h"


void Init_USART(USART_TypeDef *usart, uint16_t USART_BaudRate);
void USART_TX(USART_TypeDef *usart, char c);
char USART_RX  (USART_TypeDef *usart);
void USART_data(USART_TypeDef *usart, char msg[]);
