

#include "stm32f4xx.h"
void delayMS(int delay);
void USART2_Init (void);
char USART2_Read(void);
void USART_Text_Write( char *text);

int main (void){
	char c;
	RCC->AHB1ENR |= (1<<0);
    GPIOA->MODER |= (1<<10);   // PA5 pin is output
	USART2_Init ();


	while(1){
		USART_Text_Write("CHOOSE A TO TURN ON AND B TO TURN OFF\n");
		c = USART2_Read();
		USART_Text_Write(&c);
		if(c == 'A')
		{
			GPIOA->BSRR |= (1<<5); // led is turn ON
			USART_Text_Write("\n");
			USART_Text_Write("\nLED is ON\r\n");
		}
		if(c == 'B')
		{
		 GPIOA->BSRR |= (1<<21);  //  led is turn OFF
		 USART_Text_Write("\n");
		 USART_Text_Write("\nLED is OFF\r\n");
		}


	}

}

void USART2_Init (void)
{
	RCC->APB1ENR |= (1<<17);
	RCC->AHB1ENR |= (1<<0);
	GPIOA-> AFR[0] |= (7<<12);
	GPIOA-> AFR[0] |= (7<<8);
	GPIOA->MODER |= (1<<7);  //  PA3 as a Rx
	GPIOA->MODER |= (1<<5);  // PA2 a a Tx

	USART2->BRR = 0x0683;  // 9600 at 16MHz
	USART2->CR1 |= (1<<2);   // Rx Enable
	USART2->CR1 |= (1<<3);   // Tx Enable
	USART2->CR1 |= (1<<13);  // USART Enable

}

char USART2_Read(void)
{
	while(!(USART2-> SR & (1<<5))){}
	return USART2->DR;

}

char USART2_Write (char ch)
{
	while(!(USART2-> SR & (1<<7))){}
		USART2-> DR = (ch & 0xff);
		return ch;

}

void USART_Text_Write( char *text)
{
	while(*text) USART2_Write(*text++);

}

void delayMS(int delay)
{
	int i;
	for( ;delay>0; delay--)
	   for(i= 0; i<=3195; i++);


}
