
#define RCC_APB2ENR (*((volatile unsigned long*) 0x40021018))
#define GPIO_A      (*((volatile unsigned long*) 0x40010800))
#define GPIO_B      (*((volatile unsigned long*) 0x40010C00))	
#define GPIO_C      (*((volatile unsigned long*) 0x40011000))

//Definition port A and C
#define  Port_A  1
#define  Port_B  2
#define  Port_C  3

//Definition direction of pin (refer to Reference manual, chapter 9 ,page 171)
#define  IN  0 
#define  OUT_10 1
#define  OUT_2  2
#define  OUT_50 3

//Definition option of input(refer to Reference manual, chapter 9 ,page 171)
#define  IN_Analog 0
#define  IN_Floating 1
#define  IN_PP 2

//Definition option of ouput(refer to Reference manual, chapter 9 ,page 171)
#define  OUT_GP_PP 0
#define  OUT_GP_OD 1
#define  OUT_AF_PP 2
#define  OUT_AF_OD 3

void Init_GPIO (unsigned short port, unsigned short pin, unsigned short dir, unsigned short opt);  //Initilize port of MCU

int Read_GPIO (unsigned short port, unsigned short pin); //Read value of pin

void Write_GPIO (unsigned short port, unsigned short pin, unsigned short state);  // Write value on pin

void Toggle_Pin (unsigned short port, unsigned short pin); //Toggle state 1 pin

void Init_AFIO_Port_A(void);  //Initilize external interrupt for pin 0 port A

void Init_Delay(void); //Initilize delay, that use Systick

void Init_Systick_Interrupt(void);

void delay_1_ms(void);

void delay_ms(volatile unsigned int time);
