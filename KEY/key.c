#include "key.h"

//uint8_t KEY_Scan(uint8_t mode)
//{	 
//	static uint8_t key_up=1;//按键按松开标志
//	if(mode)key_up=1;  //支持连按		  
//	if(key_up&&(WK_UP1==1||WK_UP2==1||WK_UP3==1||WK_UP4==1||WK_UP5==1))
//	{
//		HAL_Delay(10);//去抖动 
//		key_up=0;
//		if(WK_UP1==1||WK_UP2==1||WK_UP3==1||WK_UP4==1||WK_UP5==1)
//		{
//			return 1;
//		}
//	}else    
// 	{
//		return 0;// 无按键按下
//		}
//}
