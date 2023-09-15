#include "communication.h"

#include "usart.h"




void Communication_Unpack(UART_HandleTypeDef *huart)
 {
	 if(RESET != __HAL_UART_GET_FLAG(huart, UART_FLAG_IDLE))
	 {
				 __HAL_UART_CLEAR_IDLEFLAG(huart);
				 HAL_UART_DMAStop(huart);
			if(huart->Instance == USART1)
		 {
			 
		 HAL_UART_Receive_DMA(&huart1, rx, 20);
		 }
		 else if(huart->Instance == USART3)
		 {
			 
		 HAL_UART_Receive_DMA(&huart3, rx3, 20);
		 }
			 else if(huart->Instance == UART4)
		 {
			 
		 HAL_UART_Receive_DMA(&huart4, rx4, 20);
		 }
			 else if(huart->Instance == UART5)
		 {
			 
		 HAL_UART_Receive_DMA(&huart5, rx5, 20);
		 }
	}
}
