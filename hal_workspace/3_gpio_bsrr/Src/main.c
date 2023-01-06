#include "stm32g0xx.h"

#define GPIOAEN			(1U<<0)
#define PIN5			(1U<<5)
#define LED_PIN			PIN5

int main(void)
{
	RCC->IOPENR |=  GPIOAEN;

	GPIOA->MODER |= (1U<<10); // Set bit 10 to 1
	GPIOA->MODER &=~(1U<<11); // Set bit 11 to 0

	while(1)
	{
		GPIOA->ODR ^= LED_PIN;
		for(int i=0;i<100000;i++){}
	}
}
