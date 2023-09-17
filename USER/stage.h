/*
 * stage.h
 *
 *  Created on: Jul 15, 2023
 *      Author: fby
 */

#ifndef STAGE_H_
#define STAGE_H_
#include "stdio.h"
#include "stdint.h"
#include "stdbool.h"
#include "motor_control.h"
#include "pid_control.h"
#include "usart.h"
#define  PLAN                     1
extern uint8_t track_flag;
extern uint8_t turn_flag;
extern int16_t yaw_adjust;
extern uint16_t pathlength;
extern uint16_t expectlength;
extern int a;
extern int b;
extern uint8_t tx[5][5];
extern uint8_t stop_flag;
extern uint8_t task;
extern uint8_t code[16][5];
extern uint8_t back1_flag;
extern uint8_t rx3_flag;
extern uint8_t back_flag;
void mode_selct_one(void);
void mode_select_two(void);
void GO_Foward(void);
int abs(int n);
void follow_speed(void);
void return_state(void);
void number_state(void);
enum CAR_ONE_TASK
{
    CAR_START,
    ONE_TASK_1,
    ONE_TASK_2,
    ONE_TASK_3,
    ONE_TASK_4,
    ONE_TASK_STOP,
    ONE_TASK_SPECIAL,
    CAR_END
};

enum CAR_TWO_TASK
{
	  CAR_CODE,
	  CAR_GO,
	  CAR_PUT_A,
	  CAR_PUT_B,
	  CAR_PUT_C,
	  CAR_PUT_D,
	  CAR_PUT_E,
	  CAR_BACK,
	  CAR_ALL_END
};

enum TURN_STATE
{
    TURN_BLUE,
    TURN_RED,
    TURN_GRAY,
    TURN_WHITE,
    TURN_GREEN
};

// enum PUT_STATE
// {
//     PUT_ONE,
//     PUT_TWO,
//     PUT_THREE,
//     PUT_FOUR,
//     PUT_FIVE
// };

enum STOP_STATE
{
    STOP_CENTER,
    STOP_CROSSING,
    STOP_END
};
extern	enum CAR_ONE_TASK car_one_task;
extern	enum TURN_STATE turn_state;
extern	enum STOP_STATE stop_state;
extern  enum CAR_TWO_TASK car_two_task;
extern  enum PUT_STATE put_state;


#endif /* STAGE_H_ */
