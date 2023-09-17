#include "meau.h"
#include "key.h"
#include "oled.h"

uint8_t passage = 0; //Ŀ¼
uint8_t line = 0;

void choice(void)
{
	if(WK_UP4 == 0)
	{
	passage = 0;
	line = 0;
	OLED_Clear();
	}
else if(line == 1&&WK_UP3 == 0)
{
passage = 1;
line = 0;
OLED_Clear();
}
else if(line == 2&&WK_UP3 == 0)
{
passage = 2;
line = 0;
OLED_Clear();
}
else if(line == 3&&WK_UP3 == 0)
{
passage = 3;
line = 0;
OLED_Clear();
}
else if(line == 4&&WK_UP3 == 0)
{
passage = 4;
line = 0;
OLED_Clear();
}
else if(line == 5&&WK_UP3 == 0)
{
passage = 5;
line = 0;
OLED_Clear();
}
}

void meau(void)
{
if(passage == 0)
{
  OLED_ShowString(0,0,"make your choice",12,1);
	OLED_ShowString(0,10,"one_pass",12,1);
	OLED_ShowString(0,20,"two_pass",12,1);
	OLED_ShowString(0,30,"thr_pass",12,1);
	OLED_ShowString(0,40,"fou_pass",12,1);
	OLED_ShowString(0,50,"fif_pass",12,1);
	if(WK_UP1 == 0&&line != 5)
	{
	  line++;
  	OLED_Clear();
		OLED_ShowString(120,10*line,"<",12,1);
	}
	else if(WK_UP2 == 0&&line != 0&&line != 1)
	{
	  line--;
		OLED_Clear();
		OLED_ShowString(120,10*line,"<",12,1);
	}

}
else if(passage == 1)
{
 OLED_ShowString(0,0,"one_pass",12,1);
	 OLED_ShowNum(0,10,num,5,16,1);
}
else if(passage == 2)
{
 OLED_ShowString(0,0,"two_pass",12,1);
		 OLED_ShowNum(0,10,num-(0.5*num),5,16,1);
}
else if(passage == 3)
{
 OLED_ShowString(0,0,"thr_pass",12,1);
}
else if(passage == 4)
{
 OLED_ShowString(0,0,"fou_pass",12,1);
}
else if(passage == 5)
{
 OLED_ShowString(0,0,"fif_pass",12,1);
}
  OLED_Refresh();
}

