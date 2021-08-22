#define USART_1  1
#define USART_2  2
#define USART_3  3



void Init_USART(unsigned short usart, unsigned long baud);//Initilize USART_x
void USART_TX(unsigned short usart, char c);//Trasmit a character
char USART_RX(unsigned short usart); //Recive a charater
void USART_TX_STR(unsigned short usart, char str[]); 
void USART_Send( unsigned short usart, unsigned short manager[], char str[]);
void Clear_str(char str[]);
