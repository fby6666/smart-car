#include "control.h"

motor_param motor_l={0,0,0};
motor_param motor_r={0,0,0};

void Give_Motor_PWM(int MotorL_PWM,int MotorR_PWM)
{
	if (MotorL_PWM>0) //������ת
	{
		HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_RESET);
	}
	else              //������ת
	{
		HAL_GPIO_WritePin(AIN1_GPIO_Port, AIN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(AIN2_GPIO_Port, AIN2_Pin, GPIO_PIN_SET);
	}
	if (MotorR_PWM>0) //�ҵ����ת
	{
		HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_SET);
		HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_RESET);
	}
	else              //�ҵ����ת
	{
		HAL_GPIO_WritePin(BIN1_GPIO_Port, BIN1_Pin, GPIO_PIN_RESET);
		HAL_GPIO_WritePin(BIN2_GPIO_Port, BIN2_Pin, GPIO_PIN_SET);
	}

	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_1, ABS(MotorL_PWM)+250);//180Ϊ������ѹ��Ӧ��ֵ
	__HAL_TIM_SET_COMPARE(&htim2,TIM_CHANNEL_2, ABS(MotorR_PWM)+250);
}

void Get_Encoder(void)
{
		x = (__HAL_TIM_GET_COUNTER(&htim2));   
		__HAL_TIM_SET_COUNTER(&htim2,0);  // ����������
//	x = __HAL_TIM_GET_COUNTER(&htim3);     //�����������������ֵ
	//motor_r.Encoder= __HAL_TIM_GET_COUNTER(&htim4);
	//motor.Encoder=0.5*(motor_l.Encoder+motor_r.Encoder);
}

int ABS(int a)
{
	a = a>0?a:(-a);
	return a;
}

