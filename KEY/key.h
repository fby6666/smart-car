#ifndef KEY_H
#define KEY_H

#include "main.h"


#define WK_UP1 	HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_11)
#define WK_UP2 	HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_12)
#define WK_UP3 	HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_13)
#define WK_UP4 	HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_14)
#define WK_UP5 	HAL_GPIO_ReadPin(GPIOE,GPIO_PIN_15)

//uint8_t KEY_Scan(uint8_t mode);

#endif
