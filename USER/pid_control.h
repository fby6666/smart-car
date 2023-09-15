/*
 * pid_control.h
 *
 *  Created on: Aug 15, 2022
 *      Author: HP
 */
#ifndef PID_CONTROL_PID_CONTROL_H_
#define PID_CONTROL_PID_CONTROL_H_
#include "main.h"

#define USE_GYRO 1

typedef struct
{
        float pGain;//P����ϵ��
        float iGain;//I����ϵ��
        float dGain;//D΢��ϵ��
        float ilimit;//�����޷�
        float instate;//������
        float perr;//�ϴ����?
        float errdat;//��ǰ���?
        //float zhuanjiao;
       //float GKD;//������΢��
        float   P;
        float   I;
        float   D;
        float last_derivative;//�ϴ���������ϴ����֮��
        float lastperr_errdat;//���ϴ����?
        float last_pidout;
        float pidout;//PID���������?
}PID;
extern PID motor_pid_l;
extern PID motor_pid_r;
extern PID motor_pid;
extern PID Distance;
extern PID Turn;
extern PID Turn_Angle;
extern PID local;

extern float bias_error;
extern int8_t expect_speed;
extern int8_t speed_l;//应当期待的左轮速度
extern int8_t speed_r;//应当期待的右轮速度
extern uint8_t fuhao;
extern int expectlength;
extern int pathlength;
int Up_balance(float Angle,float Gyro,float Mechanical_Angle);
int Velocity(int Encoder_left,int Encoder_right,int Mechanical_velocity);
int Turn_out(int gyro_Z,int RC);
void Track(uint8_t expect_speed);
void give_pwm (void);
void follow_adjust(void);
void Motor_PID(int speed_l, int speed_r);
void follow_speed_adjust(void);//循迹和转弯速度闭环
int Encoder_count(void);
#endif /* PID_CONTROL_PID_CONTROL_H_*/
