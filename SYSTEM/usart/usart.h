/*========================usart.h=====================*/

#ifndef __USART_H
#define __USART_H

#include "stm32f10x.h"
#include <stdio.h>

// USART 1
#define USART1_GPIO_PORT GPIOA
#define USART1_GPIO_CLK RCC_APB2Periph_GPIOA
#define USART1_TX_GPIO_PIN GPIO_Pin_9
#define USART1_RX_GPIO_PIN GPIO_Pin_10

// USART 3
#define USART3_GPIO_PORT GPIOB
#define USART3_GPIO_CLK RCC_APB2Periph_GPIOB
#define USART3_TX_GPIO_PIN GPIO_Pin_10
#define USART3_RX_GPIO_PIN GPIO_Pin_11

void usart_init(void);
void usart_init3(void);
void Init_Usart(void);
void USART_Send_Byte(USART_TypeDef *USARTx, uint16_t Data);
void USART_Send_String(USART_TypeDef *USARTx, char *str);

#endif /* __USART_H */
