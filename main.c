#include "stm32f10x.h"                  // Device header
#include <stdio.h>
#include <stdlib.h>
 char str[40];
 uint32_t i;
void USART_Put(USART_TypeDef* USARTx, volatile char *s)
{
 while(*s)
         {   
          while((USARTx->SR & 0x00000040)==RESET);
	        USART_SendData(USARTx,*s);
	        *s++;
  
          }
}
int main()
{
	GPIO_InitTypeDef GPIO_IntStr;
	USART_InitTypeDef USART_IntStr;
	RCC_APB2PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);
	//GPIO_PinRemapConfig(GPIO_Remap_USART2,ENABLE);
	
	GPIO_IntStr.GPIO_Mode=GPIO_Mode_AF_PP;
	GPIO_IntStr.GPIO_Pin=GPIO_Pin_2;
	GPIO_IntStr.GPIO_Speed=GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_IntStr);
	

  
	//GPIO_AFIODeInit();
	
	
	USART_IntStr.USART_BaudRate=1200;
	USART_IntStr.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
	USART_IntStr.USART_Mode=USART_Mode_Tx;
	USART_IntStr.USART_Parity=USART_Parity_No;
	USART_IntStr.USART_StopBits=USART_StopBits_1;
	USART_IntStr.USART_WordLength=USART_WordLength_8b;
	USART_Init(USART2,&USART_IntStr);
	USART_Cmd(USART2,ENABLE);
	for(;;)
	{
	 sprintf(str,"Usart Tx Messages");
		USART_SendData(USART2,'h');
		USART_Put(USART2,str);
		i=60000;
		while(i)
			i--;
	}
}

