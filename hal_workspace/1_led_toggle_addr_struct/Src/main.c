#include <stdint.h>

#define PERIPH_BASE			(0x40000000UL)
#define IOPORT_OFFSET		(0x10000000UL)
#define IOPORT_BASE 		(PERIPH_BASE + IOPORT_OFFSET)
#define GPIOA_OFFSET		(0x0000UL) 					// Equal to 0x 0000	0000

#define GPIOA_BASE 			(IOPORT_BASE + GPIOA_OFFSET)

#define RCC_OFFSET			(0x0FFDF000UL)
#define RCC_BASE			(IOPORT_BASE - RCC_OFFSET)

#define GPIOAEN				(1U<<0) // 0b 0000 0000 0000 0000 0000 0000 0000 0001

#define PIN5				(1U<<5)
#define LED_PIN				 PIN5

typedef struct 
{
	volatile uint32_t DUMMY[13];
	volatile uint32_t RCC_IOPEN_R; 		/*!I/O port clock enable register (RCC_IOPENR)   							Address offset: 0x34 */
} RCC_TypeDef;


typedef struct
{
	volatile uint32_t MODER;			/*!< GPIO Port Mode Register 												Address Offset 0x00 */
	volatile uint32_t DUMMY[4];			
	volatile uint32_t ODR;				/*!  GPIO Port Output Data Register											Address offset 0x14	*/
} GPIO_TypeDef;


#define RCC 				((RCC_TypeDef*)   RCC_BASE)
#define GPIOA 				((GPIO_TypeDef*)  GPIOA_BASE)

int main(void)
{
	/*1. Enable Clock Access to GPIOA by using OR operator*/
	RCC->RCC_IOPEN_R |=  GPIOAEN;

	/*2. Set PA5 as output pin*/
	GPIOA->MODER |= (1U<<10); // Set bit 10 to 1
	GPIOA->MODER &=~(1U<<11); // Set bit 11 to 0

	while(1)
	{
		/*3. Set PA5 high*/
		// GPIOA_OD_R |= LED_PIN;

		/*4:Experiment 2 : toggle PA5*/
		GPIOA->ODR^= LED_PIN;
		for (int i=0; i<100000;i++){}
	}
}
