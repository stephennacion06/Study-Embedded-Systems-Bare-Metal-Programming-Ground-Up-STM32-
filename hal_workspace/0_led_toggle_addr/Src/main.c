#define PERIPH_BASE			(0x40000000UL)
#define IOPORT_OFFSET		(0x10000000UL)
#define IOPORT_BASE 		(PERIPH_BASE + IOPORT_OFFSET)
#define GPIOA_OFFSET		(0x0000UL) 					// Equal to 0x 0000	0000

#define GPIOA_BASE 			(IOPORT_BASE + GPIOA_OFFSET)

#define RCC_OFFSET			(0x0FFDF000UL)
#define RCC_BASE			(IOPORT_BASE - RCC_OFFSET)

#define RCC_IOPENR_OFFSET	(0x34UL)
#define RCC_IOPEN_R			(*(volatile unsigned int *)(RCC_BASE + RCC_IOPENR_OFFSET))

#define MODE_R_OFFSET		(0x00UL)
#define GPIOA_MODE_R		(*(volatile unsigned int *)(GPIOA_BASE + MODE_R_OFFSET))

#define OD_R_OFFSET			(0x14UL)
#define GPIOA_OD_R			(*(volatile unsigned int *)(GPIOA_BASE + OD_R_OFFSET))

#define GPIOAEN				(1U<<0) // 0b 0000 0000 0000 0000 0000 0000 0000 0001

#define PIN5				(1U<<5)
#define LED_PIN				 PIN5
/*
 * MODE_R Bit Manipulation
 * (1U<<10) // Set bit 10 to 1
 * & (1U<<11) // Set bit 11 to 1
 */

int main(void)
{
	/*1. Enable Clock Access to GPIOA by using OR operator*/
	RCC_IOPEN_R |=  GPIOAEN;

	/*2. Set PA5 as output pin*/
	GPIOA_MODE_R |= (1U<<10); // Set bit 10 to 1
	GPIOA_MODE_R &=~(1U<<11); // Set bit 11 to 0

	while(1)
	{
		/*3. Set PA5 high*/
		// GPIOA_OD_R |= LED_PIN;

		/*4:Experiment 2 : toggle PA5*/
		GPIOA_OD_R ^= LED_PIN;
		for (int i=0; i<100000;i++){}
	}
}
