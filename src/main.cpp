/**
  ******************************************************************************
  * @file    main.c
  * @author  Ac6
  * @version V1.0
  * @date    01-December-2013
  * @brief   Default main function.
  ******************************************************************************
*/


#include "stm32f0xx.h"
#include "Hbridge.h"
#include  "USART.h"

USART *usart;

int main(void)
{
	H_bridge *Motor = new H_bridge(1,3,GPIOA,4,5,6,7);
	usart = new USART(USART1, 115200);
	Motor->Move(600,600);
	Motor->Move(600,600);
	for(;;);
}
extern "C" void USART1_IRQHandler()
{
	usart->InterruptHandler();
}
