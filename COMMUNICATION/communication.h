#ifndef COMMUNICATION_H
#define COMMUNICATION_H

#include "main.h"

extern uint8_t rx[20];
extern uint8_t rx3[20];
extern uint8_t rx4[20];
extern uint8_t rx5[20];


extern DMA_HandleTypeDef hdma_usart1_rx;
extern DMA_HandleTypeDef hdma_usart3_rx;
extern DMA_HandleTypeDef hdma_uart4_rx;
extern DMA_HandleTypeDef hdma_uart5_rx;


void Communication_Unpack(UART_HandleTypeDef *huart);


#endif

