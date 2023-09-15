#ifndef CONTROL_H
#define CONTROL_H

#include "main.h"

int ABS(int a);
void Give_Motor_PWM(int MotorL_PWM,int MotorR_PWM);
void Get_Encoder(void);

extern TIM_HandleTypeDef htim2;//����TIM2��HAL��ṹ��
extern TIM_HandleTypeDef htim3;//����TIM3��HAL��ṹ��
extern TIM_HandleTypeDef htim4;//����TIM4��HAL��ṹ��
extern uint8_t x;
typedef struct motor_param{
        uint8_t Encoder;
        int16_t last_encoder;
        int16_t total_encoder;
}motor_param;
extern motor_param motor_l;
extern motor_param motor_r;
extern motor_param motor;
#endif
