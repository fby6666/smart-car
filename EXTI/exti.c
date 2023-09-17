#include "exti.h"
#include "pid_control.h"
#include "motor_control.h"
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{

	if (htim->Instance == TIM6)
	{
		motor_pid_l.iGain=20;
		motor_pid_l.pGain=400;
		motor_pid_r.iGain=20;
		motor_pid_r.pGain=400;
		Get_Speed();
		Motor_PID(20,20);
		//Give_Motor_PWM(-3000,0);
	}
	
	
}

