/*
 * stage.c
 *
 *  Created on: Jul 15, 2023
 *      Author: fby
 */
#include "stage.h"
//#include "LobotServoController.h"

enum CAR_ONE_TASK car_one_task;
enum TURN_STATE turn_state;
enum STOP_STATE stop_state;
enum CAR_TWO_TASK car_two_task;
enum PUT_STATE put_state;

#define  TO_DISTANCE_CENTER    5900 //home前往中心�?
#define  TO_ANGLE_ONE_CATCH    200   //中心点转向物料抓取点
#define  TO_ANGLE_TWO_CATCH    400   //中心点转向物料抓取点
#define  TO_ANGLE_THREE_CATCH    600   //中心点转向物料抓取点
#define  TO_ANGLE_FOUR_CATCH    800   //中心点转向物料抓取点
#define  TO_destination_CATCH     2400  //中心点到物料点抓取距�?
#define  TO_destination_PUT     1000  //中心点到物料点抓取距�?
#define  TO_destination_BACK    4800  //中心点到外圆�?
#define  back                    2300
// #define  PLAN                     1
uint8_t track_flag = 0;
uint8_t turn_flag = 0;
uint8_t back_flag = 0;
uint16_t pathlength;
uint16_t expectlength;
uint8_t rx_state;
uint8_t tx_state=0;
uint8_t rx4_state = 0;
uint8_t tx4_state = 0;
uint8_t gray_state = 0;
uint8_t find_code[1] = {1};
uint8_t catch_num = 0;
uint8_t stop = 0;
uint8_t red = 0;
uint8_t green = 0;
uint8_t blue = 0;
uint8_t white = 0;
uint8_t gray = 0;
uint8_t fang = 0;
uint8_t find_color[1] = {'f'};
uint8_t find_ok[1] = {'n'};
int a=0;
int b=0;
int state_catch=1;//�?1开�?0就进入了放物�?
int state_put=0;
int distance;//每次开始准备转向的角度>0右转 <0左转
void GO_Foward()
{
    Get_Speed();
    //Motor_PID(20, 20);
    a = motor_l.Encoder > 0 ? motor_l.Encoder : -motor_l.Encoder;
    b = motor_r.Encoder > 0 ? motor_r.Encoder : -motor_r.Encoder;
    pathlength += (a + b) * 0.5;
}
void follow_speed(void)
{
    Get_Speed();
    //Motor_PID(20, 20);
    a = motor_l.Encoder > 0 ? motor_l.Encoder : -motor_l.Encoder;
    b = motor_r.Encoder > 0 ? motor_r.Encoder : -motor_r.Encoder;
    pathlength += (a + b) * 0.5;
    if(track_flag==1 && turn_flag==0 && back_flag ==0)
    {
        Track(20);
    }
    else if(track_flag==0 && turn_flag==1 && back_flag ==0)
    {
       if(state_catch == 1||state_catch == 3)
			 {
				 if(distance>0)
        {
            
					Motor_PID(20,-20);
        }
        else
        {
            Motor_PID(-20,20);
        }
    }
			 else 
			 {
			 Motor_PID(20,-20);
			 }
	}
    else if(back1_flag == 1)
    {
  //      Motor_PID(20,20);
			Track (20);
    }
		else if(track_flag == 0&& turn_flag == 0&& back_flag == 1)
		{
		     //Track(20);
			Motor_PID(20,20);
		}
		else if(track_flag==0 && turn_flag==0 && back_flag ==0)
		{
		   //  Give_Motor_PWM(0,0);
			 Motor_PID(0,0);
		}
}
int abs(int n)
{
    if(n>=0)return n;
    else return -n;
}

void number_state(void)
{
  switch(car_two_task)
	{
		case CAR_PUT_A:
			if(code[task-1][0] == 1)
			{
			put_state = PUT_ONE;
				break;
			}
		  else if(code[task-1][0] == 2)
			{
			put_state = PUT_TWO;
				break;
			}
			else if(code[task-1][0] == 3)
			{
			put_state = PUT_THREE;
				break;
			}
			else if(code[task-1][0] == 4)
			{
			put_state = PUT_FOUR;
				break;
			}
			else if(code[task-1][0] == 5)
			{
			put_state = PUT_FIVE;
				break;
			}
			break;
					case CAR_PUT_D:
			if(code[task-1][3] == 1)
			{
			put_state = PUT_ONE;
				break;
			}
		  else if(code[task-1][3] == 2)
			{
			put_state = PUT_TWO;
				break;
			}
			else if(code[task-1][3] == 3)
			{
			put_state = PUT_THREE;
				break;
			}
			else if(code[task-1][3] == 4)
			{
			put_state = PUT_FOUR;
				break;
			}
			else if(code[task-1][3] == 5)
			{
			put_state = PUT_FIVE;
				break;
			}
			break;
				case CAR_PUT_C:
			if(code[task-1][2] == 1)
			{
			put_state = PUT_ONE;
				break;
			}
		  else if(code[task-1][2] == 2)
			{
			put_state = PUT_TWO;
				break;
			}
			else if(code[task-1][2] == 3)
			{
			put_state = PUT_THREE;
				break;
			}
			else if(code[task-1][2] == 4)
			{
			put_state = PUT_FOUR;
				break;
			}
			else if(code[task-1][2] == 5)
			{
			put_state = PUT_FIVE;
				break;
			}
			break;
				case CAR_PUT_B:
			if(code[task-1][1] == 1)
			{
			put_state = PUT_ONE;
				break;
			}
		  else if(code[task-1][1] == 2)
			{
			put_state = PUT_TWO;
				break;
			}
			else if(code[task-1][1] == 3)
			{
			put_state = PUT_THREE;
				break;
			}
			else if(code[task-1][1] == 4)
			{
			put_state = PUT_FOUR;
				break;
			}
			else if(code[task-1][1] == 5)
			{
			put_state = PUT_FIVE;
				break;
			}
			break;
		default:
			break;
	}
}

void return_state(void)//distance 用于将每次放完物料后对正下一个数�?
{
    switch (car_one_task)
    {
    case ONE_TASK_1:
        distance=425;
        break;
    case ONE_TASK_2:
        switch (turn_state)
        {
        case TURN_BLUE:
            distance=400;
            break;
        case TURN_GREEN:
            distance=-400;
            break;
        case TURN_RED:
            distance=-1200;
            break;
        case TURN_WHITE:
            distance=1200;
            break;
        case TURN_GRAY:
            distance=850;
            break;
        default:
            break;
        }
        break;
    case ONE_TASK_3:
        switch (turn_state)
        {
        case TURN_BLUE:
            distance=1200;
            break;
        case TURN_GREEN:
            distance=400;
            break;
        case TURN_RED:
            distance=-400;
            break;
        case TURN_WHITE:
            distance=-1200;
            break;
        case TURN_GRAY:
            distance=850;
            break;
        default:
            break;
        }
				break;
    case ONE_TASK_4:
        switch (turn_state)
        {
        case TURN_BLUE:
            distance=-1200;
            break;
        case TURN_GREEN:
            distance=1200;
            break;
        case TURN_RED:
            distance=400;
            break;
        case TURN_WHITE:
            distance=-400;
            break;
        case TURN_GRAY:
            distance=850;
            break;
        default:
            break;
        }
        break;
    case ONE_TASK_SPECIAL:
        switch (turn_state)
        {
        case TURN_BLUE:
            distance=-1200;
            break;
        case TURN_GREEN:
            distance=1200;
            break;
        case TURN_RED:
            distance=400;
            break;
        case TURN_WHITE:
            distance=-400;
            break;
        case TURN_GRAY://最后一个点需要改
            distance=0;
            break;
        default:
            break;
        }
        break;
				case CAR_END:
					distance = -850;
					break;
    default:
        break;
    }
}

void mode_selct_one(void)
{
    switch (car_one_task)
    {
    case CAR_START:
    if(pathlength<TO_DISTANCE_CENTER)
    {
        track_flag=1;
        turn_flag=0;
        back_flag=0;
#if PLAN == 1
        Track(20);
#endif
        //GO_Foward();
    }
    else
    {
        pathlength=0;
        track_flag=0;
        turn_flag=0;
        back_flag=0;
        car_one_task = ONE_TASK_1;
		//	car_one_task=CAR_START;      
    }
       break;
    case ONE_TASK_1:
    if(state_catch==1)//进行转弯一定角�?
    {
        if(pathlength<abs(distance))
            {
                track_flag=0;
                turn_flag=1;
                back_flag=0;
#if PLAN==1
            if(distance>0)
                Motor_PID(20,-20);
            else
                Motor_PID(-20,20);
#endif
                //转弯
            }
        else
            {
                car_one_task=ONE_TASK_1;
                pathlength=0;
                track_flag=0;
                turn_flag=0;
                back_flag=0;
                state_catch=2;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
            }
    }
    else if(state_catch==2)//转弯后直�?
    {
        if(pathlength<TO_destination_CATCH)
            {
                track_flag=1;
                turn_flag=0;
                back_flag=0;
                //直走
#if PLAN == 1
                Track(20);
#endif
            }
        else{
            pathlength=0;
            track_flag=0;
            turn_flag=0;
            back_flag=0;
            car_one_task=ONE_TASK_1;
            state_catch=3;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
        }
    }
    else if(state_catch ==3)//根据颜色执行抓取动作
    {
			if(rx3_flag == 1)
			{
				HAL_UART_Transmit_DMA(&huart3,find_ok,1);
				if(turn_state == TURN_GRAY)
                    {
                        if(tx_state == 0&& rx_state == 0)
                        {
                            //执行动作组把黑色夹到车上
                            tx_state = 1;
                            gray_state = 1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                        }
                        else if(tx_state == 1&& rx_state == 1)
                        {
                            state_catch =4;
                            tx_state=0;
                            rx_state=0;
                            rx3_flag = 0;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                        }
                    }
                else
                {
                    if(tx_state==0 && rx_state==0)
                    {
                        runActionGroup(0,1);  //执行动作�?
                        tx_state=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
            //					state_catch =4;
            //            tx_state=0;
            //            rx_state=0;
                            //	HAL_UART_Transmit_DMA(&huart1,tx[1],1);
                    }
                else if(tx_state==1 && rx_state==1)
                {
                    state_catch =4;
                    tx_state=0;
                    rx_state=0;
                            rx3_flag = 0;
                }
                else{

                }
                    }
            }
			else if(rx3_flag == 0)
			{
			HAL_UART_Transmit_DMA(&huart3,find_color,1);
			}
	}
    else if(state_catch ==4)//倒车之前距离回去中心
    {
        if(pathlength<back)
        {
            track_flag=0;
            turn_flag=0;
            back_flag=1;
#if PLAN==1
            Motor_PID(20,20);
#endif
        }
        else
        {
            pathlength=0;
            track_flag=0;
            turn_flag=0;
            back_flag=0;
            state_catch=0;
            car_one_task=ONE_TASK_1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
        }
    }
    else if(state_catch==0)
    {
        switch (turn_state)// 根据摄像头判别颜�?
        {
        case TURN_BLUE:
            if(state_put==0)
            {
                if(pathlength<400)//蓝色放置点角�?
                {
                    track_flag=0;
                    turn_flag=1;
                    back_flag=0;
#if PLAN == 1
                    Motor_PID(20,-20);
#endif
                }
                else
                {
                    track_flag=0;
                    turn_flag=0;
                    back_flag=0;
                    pathlength=0;
                    state_put=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                }
            }
            else if(state_put==1)
            {
                if(tx_state==0 && rx_state==0)
                    {
                       runActionGroup(1,1); //执行动作�?
                        tx_state=1;
                        blue = 1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
//									      state_put =0;
//                        tx_state=0;
//                        rx_state=0;
//                        car_one_task=ONE_TASK_2;
//                        state_catch=1;
                    }
                    else if(tx_state==1 && rx_state==1)
                    {
                        state_put =0;
                        tx_state=0;
                        rx_state=0;
						pathlength = 0;
                        car_one_task=ONE_TASK_2;
                        state_catch=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                        break;
                    }
            }
            break;
        case TURN_GREEN:
            if(state_put==0)
            {
                if(pathlength<1375)//绿色放置点角�?      1200
                    {
                        track_flag=0;
                        turn_flag=1;
                        back_flag=0;
#if PLAN == 1
                        Motor_PID(20,-20);
#endif
                    }
                    else
                    {
                        track_flag=0;
                        turn_flag=0;
                        back_flag=0;
                        pathlength=0;
                        state_put=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
            }
            else if(state_put==1)
            {
                if(tx_state==0 && rx_state==0)
                    {
                        runActionGroup(1,1);  //执行动作�? //执行动作�?
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                        tx_state=1;
                        green = 1;

                    }
                    else if(tx_state==1 && rx_state==1)
                    {
                        state_put =0;
                        tx_state=0;
                        rx_state=0;
                        state_catch=1;
                        pathlength = 0;
                        car_one_task=ONE_TASK_2;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                        break;
                    }
            }
						break;
        case TURN_RED:
            if(state_put==0)
            {
#if PLAN ==1
                if(pathlength<1500)
#else
                if(pathlength<2225)//红色放置点角�?        2100
#endif
                    {
                        track_flag=0;
                        turn_flag=1;
                        back_flag=0;
#if PLAN == 1
                        Motor_PID(-20,20);
#endif
                    }
                    else
                    {
                        track_flag=0;
                        turn_flag=0;
                        back_flag=0;
                        pathlength=0;
                        state_put=1;
                    }
            }
            else if(state_put==1)
            {
                if(tx_state==0 && rx_state==0)
                    {
                        runActionGroup(1,1);  //执行动作�? 
                        tx_state=1;
                        red = 1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
                    else if(tx_state==1 && rx_state==1)
                    {
                        state_put =0;
                        tx_state=0;
                        rx_state=0;
                        state_catch=1;
                        pathlength = 0;
                        car_one_task=ONE_TASK_2;
#if PLAN == 1
                        Motor_PID(0,0);
#endif 
                        break;
                    }
            }
						break;
        case TURN_WHITE:
            if(state_put==0)
            {
#if PLAN==1 
                if(pathlength<450)
#else
                if(pathlength<3225)//白色放置点角�?    3100
#endif
                    {
                        track_flag=0;
                        turn_flag=1;
                        back_flag=0;
#if PLAN == 1
                        Motor_PID(-20,20);
#endif              
                    }
                    else
                    {
                        track_flag=0;
                        turn_flag=0;
                        back_flag=0;
                        pathlength=0;
                        state_put=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
            }
            else if(state_put==1)
            {
                if(tx_state==0 && rx_state==0)
                    {
                        runActionGroup(1,1);  //执行动作�? 
                        tx_state=1;
                        white = 1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
                    else if(tx_state==1 && rx_state==1)
                    {
                        state_put =0;
                        tx_state=0;
                        rx_state=0;
                        state_catch=1;
                        pathlength = 0;
                        car_one_task=ONE_TASK_2;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                        break;
                    }
            }
						break;
        case TURN_GRAY:
            state_catch=1;
            car_one_task=ONE_TASK_2;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
            break;
        default:
            break;
        }
    }
        break;
    case ONE_TASK_2:
        if(state_catch==1)//进行转弯一定角�?
    {
        if(pathlength<abs(distance))
            {
                track_flag=0;
                turn_flag=1;
                back_flag=0;
#if PLAN==1
            if(distance>0)
                Motor_PID(20,-20);
            else
                Motor_PID(-20,20);
#endif
                //转弯
            }
        else
            {
                car_one_task=ONE_TASK_2;
                pathlength=0;
                track_flag=0;
                turn_flag=0;
                back_flag=0;
                state_catch=2;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
            }
    }
    else if(state_catch==2)//转弯后直�?
    {
        if(pathlength<TO_destination_CATCH+100)
            {
                track_flag=1;
                turn_flag=0;
                back_flag=0;
                //直走
#if PLAN == 1
                Track(20);
#endif

            }
        else{
            pathlength=0;
            track_flag=0;
            turn_flag=0;
            back_flag=0;
            car_one_task=ONE_TASK_2;
            state_catch=3;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
        }
    }
    else if(state_catch ==3)//根据颜色执行抓取动作
    {
      if(rx3_flag == 1)
			{
				HAL_UART_Transmit_DMA(&huart3,find_ok ,1);
				if(turn_state == TURN_GRAY)
			 {
			 if(tx_state == 0 && rx_state == 0)
			 {
				// 执行动作组把黑色放车�?
				   tx_state = 1; 
#if PLAN == 1
                        Motor_PID(0,0);
#endif
//				 		state_catch =4;
//            tx_state=0;
//            rx_state=0;
//				gray_state = 1;
//				 rx3_flag = 0;
			 }
			 else if(tx_state == 1 && rx_state == 1)
			 {
                state_catch =4;
                tx_state=0;
                rx_state=0;
                rx3_flag = 0;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
			 }
			 }
			else
			{
				if(tx_state==0 && rx_state==0)
        {
               runActionGroup(0,1); //执行动作�?
            tx_state=1;
//					  state_catch =4;
//            tx_state=0;
//            rx_state=0;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
        }
        else if(tx_state==1 && rx_state==1)
        {
            state_catch =4;
            tx_state=0;
            rx_state=0;
            rx3_flag = 0;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
        }
        else{

        }
			}
    }
			else if(rx3_flag == 0)
			{
			HAL_UART_Transmit_DMA(&huart3,find_color,1);
			}
	}
    else if(state_catch ==4)//倒车之前距离回去中心
    {
        if(pathlength<back-100)
        {
            track_flag=0;
            turn_flag=0;
            back_flag=1;
#if PLAN == 1
                Motor_PID(20,20);
#endif
        }
        else
        {
            pathlength=0;
            track_flag=0;
            turn_flag=0;
            back_flag=0;
            state_catch=0;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
        }
    }
    else if(state_catch==0)
    {
        switch (turn_state)// 根据摄像头判别颜�?
        {
        case TURN_GREEN:
            if(state_put==0)
            {
                if(pathlength<425)//绿色放置点角�?
                {
                    track_flag=0;
                    turn_flag=1;
                    back_flag=0;
#if PLAN == 1
                Track(20);
#endif
                }
                else
                {
                    track_flag=0;
                    turn_flag=0;
                    back_flag=0;
                    pathlength=0;
                    state_put=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                }
            }
            else if(state_put==1)
            {
                if(tx_state==0 && rx_state==0)
                    {
                        runActionGroup(1,1); //执行动作�?
                        tx_state=1;
                        green = 1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
//										    state_put =0;
//                        tx_state=0;
//                        rx_state=0;
//                        state_catch=1;
//                        car_one_task=ONE_TASK_3;
                    }
                    else if(tx_state==1 && rx_state==1)
                    {
                        state_put =0;
                        tx_state=0;
                        rx_state=0;
                        state_catch=1;
                        pathlength = 0;
                        car_one_task=ONE_TASK_3;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                        break;
                    }
            }
            break;
        case TURN_RED:
            if(state_put==0)
            {
                if(pathlength<1375)//红色放置点角�?
                    {
                        track_flag=0;
                        turn_flag=1;
                        back_flag=0;
#if PLAN == 1
                Motor_PID(20,-20);
#endif

                    }
                    else
                    {
                        track_flag=0;
                        turn_flag=0;
                        back_flag=0;
                        pathlength=0;
                        state_put=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
            }
            else if(state_put==1)
            {
                if(tx_state==0 && rx_state==0)
                    {
                       runActionGroup(1,1);  //执行动作�?  
                        tx_state=1;
                        red = 1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
                    else if(tx_state==1 && rx_state==1)
                    {
                        state_put =0;
                        tx_state=0;
                        rx_state=0;
                        state_catch=1;
                        pathlength = 0;
                        car_one_task=ONE_TASK_3;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                        break;
                    }
            }
						break;
        case TURN_WHITE:
            if(state_put==0)
            {
#if PLAN==1
                if(pathlength<1375)
#else
                if(pathlength<2225)//白色放置点角�?
#endif
                    {
                        track_flag=0;
                        turn_flag=1;
                        back_flag=0;
#if PLAN == 1
                Motor_PID(-20,20);
#endif
                    }
                    else
                    {
                        track_flag=0;
                        turn_flag=0;
                        back_flag=0;
                        pathlength=0;
                        state_put=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
            }
            else if(state_put==1)
            {
                if(tx_state==0 && rx_state==0)
                    {
                       runActionGroup(1,1);  //执行动作�?  //执行动作�?
                        tx_state=1;
                        white = 1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
                    else if(tx_state==1 && rx_state==1)
                    {
                        state_put =0;
                        tx_state=0;
                        rx_state=0;
                        state_catch=1;
                        pathlength = 0;
                        car_one_task=ONE_TASK_3;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                        break;
                    }
            }
						break;
        case TURN_BLUE:
            if(state_put==0)
            {
#if PLAN==1
                if(pathlength<450)
#else
                if(pathlength<3300)//蓝色放置点角�?
#endif
                    {
                        track_flag=0;
                        turn_flag=1;
                        back_flag=0;
#if PLAN == 1
                Motor_PID(-20,20);
#endif
                    }
                    else
                    {
                        track_flag=0;
                        turn_flag=0;
                        back_flag=0;
                        pathlength=0;
                        state_put=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
            }
            else if(state_put==1)
            {
                if(tx_state==0 && rx_state==0)
                    {
                        runActionGroup(1,1);  //执行动作�?    //执行动作�?
                        tx_state=1;
                        blue = 1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
                    else if(tx_state==1 && rx_state==1)
                    {
                        state_put =0;
                        tx_state=0;
                        rx_state=0;
                        state_catch=1;
                        pathlength = 0;
                        car_one_task=ONE_TASK_3;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                        break;
                    }
            }
              break;						
        case TURN_GRAY:
            state_catch=1;
            car_one_task=ONE_TASK_3;
            break;
        default:
            break;
        }
    }
        break;
    case ONE_TASK_3:
    if(state_catch==1)//进行转弯一定角�?
    {
        if(pathlength<abs(distance))
            {
                track_flag=0;
                turn_flag=1;
                back_flag=0;
                //转弯
#if PLAN==1
            if(distance>0)
                Motor_PID(20,-20);
            else
                Motor_PID(-20,20);
#endif
            }
        else
            {
                car_one_task=ONE_TASK_3;
                pathlength=0;
                track_flag=0;
                turn_flag=0;
                back_flag=0;
                state_catch=2;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
            }
    }
    else if(state_catch==2)//转弯后直�?
    {
        if(pathlength<TO_destination_CATCH+150)
            {
                track_flag=1;
                turn_flag=0;
                back_flag=0;
#if PLAN == 1
                Track(20);
#endif
                //直走
            }
        else{
            pathlength=0;
            track_flag=0;
            turn_flag=0;
            back_flag=0;
            car_one_task=ONE_TASK_3;
            state_catch=3;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
        }
    }
    else if(state_catch ==3)//根据颜色执行抓取动作
    {
       if(rx3_flag == 1)
			 {
				 HAL_UART_Transmit_DMA(&huart3,find_ok,1);
				 if(turn_state == TURN_GRAY )
				{
				if(tx_state == 0 && rx_state == 0)
				{
					//执行动作组把黑色放车�?
					tx_state = 1;
					gray_state = 1;
				}
				else if(tx_state == 1 && rx_state == 1)
				{
				    state_catch =4;
                    tx_state=0;
                    rx_state=0;
                    rx3_flag = 0;
				}
				}
				else
				{
					if(tx_state==0 && rx_state==0)
        {
            runActionGroup(0,1);//执行动作�?
            tx_state=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
//					  state_catch =4;
//            tx_state=0;
//            rx_state=0;
        }
        else if(tx_state==1 && rx_state==1)
        {
            state_catch =4;
            tx_state=0;
            rx_state=0;
            rx3_flag = 0;
        }
        else{

        }
			}
    }
			 else if(rx3_flag == 0)
			 {
			 HAL_UART_Transmit_DMA(&huart3,find_color,1);
			 }
	}
    else if(state_catch ==4)//倒车之前距离回去中心
    {
        if(pathlength<back-100)
        {
            track_flag=0;
            turn_flag=0;
            back_flag=1;
#if PLAN == 1
                Motor_PID(20,20);
#endif
        }
        else
        {
            pathlength=0;
            track_flag=0;
            turn_flag=0;
            back_flag=0;
            state_catch=0;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
        }
    }
    else if(state_catch==0)
    {
        switch (turn_state)// 根据摄像头判别颜�?
        {
        case TURN_RED:
            if(state_put==0)
            {
                if(pathlength<425)//红色放置点角�?
                {
                    track_flag=0;
                    turn_flag=1;
                    back_flag=0;
#if PLAN == 1
                Motor_PID(20,-20);
#endif
                }
                else
                {
                    track_flag=0;
                    turn_flag=0;
                    back_flag=0;
                    pathlength=0;
                    state_put=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                }
            }
            else if(state_put==1)
            {
                if(tx_state==0 && rx_state==0)
                    {
                       runActionGroup(1,1);    //执行动作�?
                        tx_state=1;
                        red = 1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
//										    state_put =0;
//                        tx_state=0;
//                        rx_state=0;
//                        state_catch=1;
//                        car_one_task=ONE_TASK_4;
                    }
                    else if(tx_state==1 && rx_state==1)
                    {
                        state_put =0;
                        tx_state=0;
                        rx_state=0;
                        state_catch=1;
                        pathlength = 0;
                        car_one_task=ONE_TASK_4;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                        break;
                    }
            }
            break;
        case TURN_WHITE:
            if(state_put==0)
            {
                if(pathlength<1375)//白色放置点角�?
                    {
                        track_flag=0;
                        turn_flag=1;
                        back_flag=0;
#if PLAN == 1
                Motor_PID(20,-20);
#endif
                    }
                    else
                    {
                        track_flag=0;
                        turn_flag=0;
                        back_flag=0;
                        pathlength=0;
                        state_put=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
            }
            else if(state_put==1)
            {
                if(tx_state==0 && rx_state==0)
                    {
                        runActionGroup(1,1);  //执行动作�?   //执行动作�?
                        tx_state=1;
                        white = 1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
                    else if(tx_state==1 && rx_state==1)
                    {
                        state_put =0;
                        tx_state=0;
                        rx_state=0;
                        state_catch=1;
                        pathlength = 0;
                        car_one_task=ONE_TASK_4;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                        break;
                    }
            }
						break;
        case TURN_BLUE:
            if(state_put==0)
            {
#if PLAN ==1
                if(pathlength<1375)
#else
                if(pathlength<2225)//蓝色放置点角�?
#endif
                    {
                        track_flag=0;
                        turn_flag=1;
                        back_flag=0;
#if PLAN == 1
                        Motor_PID(-20,20);
#endif
                    }
                    else
                    {
                        track_flag=0;
                        turn_flag=0;
                        back_flag=0;
                        pathlength=0;
                        state_put=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
            }
            else if(state_put==1)
            {
                if(tx_state==0 && rx_state==0)
                    {
                       runActionGroup(1,1);  //执行动作�?   //执行动作�? //执行动作�?
                        tx_state=1;
                        blue = 1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
                    else if(tx_state==1 && rx_state==1)
                    {
                        state_put =0;
                        tx_state=0;
                        rx_state=0;
                        state_catch=1;
                        pathlength = 0;
                        car_one_task=ONE_TASK_4;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                        break;
                    }
            }
						break;
        case TURN_GREEN:
            if(state_put==0)
            {
#if PLAN==1
                if(pathlength<425)
#else
                if(pathlength < 3300)//绿色放置点角�?
#endif
                    {
                        track_flag=0;
                        turn_flag=1;
                        back_flag=0;
#if PLAN == 1
                        Motor_PID(-20,20);
#endif
                    }
                    else
                    {
                        track_flag=0;
                        turn_flag=0;
                        back_flag=0;
                        pathlength=0;
                        state_put=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
            }
            else if(state_put==1)
            {
                if(tx_state==0 && rx_state==0)
                    {
                       runActionGroup(1,1);  //执行动作�?
                        tx_state=1;
                        green = 1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
                    else if(tx_state==1 && rx_state==1)
                    {
                        state_put =0;
                        tx_state=0;
                        rx_state=0;
                        state_catch=1;
                        pathlength = 0;
                        car_one_task=ONE_TASK_4;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                        break;
                    }
            }
						break;
        case TURN_GRAY:
            state_catch=1;
            car_one_task=ONE_TASK_4;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
            break;
        default:
            break;
        }
    }
        break;
    case ONE_TASK_4:
        if(state_catch==1)//进行转弯一定角�?
    {
        if(pathlength<abs(distance))
            {
                track_flag=0;
                turn_flag=1;
                back_flag=0;
#if PLAN==1
            if(distance>0)
                Motor_PID(20,-20);
            else
                Motor_PID(-20,20);
#endif
                //转弯
            }
        else
            {
                car_one_task=ONE_TASK_4;
                pathlength=0;
                track_flag=0;
                turn_flag=0;
                back_flag=0;
                state_catch=2;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
            }
    }
    else if(state_catch==2)//转弯后直�?
    {
        if(pathlength<TO_destination_CATCH+50)
            {
                track_flag=1;
                turn_flag=0;
                back_flag=0;
#if PLAN == 1
                Track(20);
#endif
                //直走

            }
        else{
            pathlength=0;
            track_flag=0;
            turn_flag=0;
            back_flag=0;
            car_one_task=ONE_TASK_4;
            state_catch=3;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
        }
    }
    else if(state_catch ==3)//根据颜色执行抓取动作
    {
       if(rx3_flag == 1)
			 {
				 HAL_UART_Transmit_DMA(&huart3,find_ok,1);
				 if(turn_state == TURN_GRAY)
				{
				if(tx_state == 0 && rx_state == 0)
				{
					//执行动作组把黑的放车�?
					tx_state = 1;
				  gray_state = 1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
				}
				else if(tx_state == 1 && rx_state == 1)
				{
				    state_catch =4;
                    tx_state=0;
                    rx_state=0;
                    rx3_flag = 0;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
				}
				}
			else
			{
				if(tx_state==0 && rx_state==0)
        {
                runActionGroup(0,1);  //执行动作�?
                tx_state=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
//					  state_catch =4;
//            tx_state=0;
//            rx_state=0;
        }
        else if(tx_state==1 && rx_state==1)
        {
            state_catch =4;
            tx_state=0;
            rx_state=0;
            rx3_flag = 0;
        }
        else{

        }
			}
    }
			 else if(rx3_flag == 0)
			 {
			 HAL_UART_Transmit_DMA(&huart3,find_color,1);
			 }
	}
    else if(state_catch ==4)//倒车之前距离回去中心
    {
        if(pathlength<back)
        {
            track_flag=0;
            turn_flag=0;
            back_flag=1;
#if PLAN == 1
                Motor_PID(20,20);
#endif
        }
        else
        {
            pathlength=0;
            track_flag=0;
            turn_flag=0;
            back_flag=0;
            state_catch=0;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
        }
    }
    else if(state_catch==0)
    {
        switch (turn_state)// 根据摄像头判别颜�?
        {
        case TURN_WHITE:
            if(state_put==0)
            {
                if(pathlength<425)//白色放置点角�?
                {
                    track_flag=0;
                    turn_flag=1;
                    back_flag=0;
#if PLAN == 1
                Motor_PID(20,-20);
#endif
                }
                else
                {
                    track_flag=0;
                    turn_flag=0;
                    back_flag=0;
                    pathlength=0;
                    state_put=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                }
            }
            else if(state_put==1)
            {
                if(tx_state==0 && rx_state==0)
                    {
                      runActionGroup(1,1);  //执行动作�?
                        tx_state=1;
                        white = 1;
                    }
                    else if(tx_state==1 && rx_state==1)
                    {
                        state_put =0;
                        tx_state=0;
                        rx_state=0;
                        state_catch=1;
                        pathlength = 0;
                       // car_one_task=CAR_END;
											 //car_one_task = ONE_TASK_STOP;
                        car_one_task = ONE_TASK_SPECIAL;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                        break;
                    }
            }
            break;
        case TURN_BLUE:
            if(state_put==0)
            {
                if(pathlength<1375)//蓝色放置点角�?
                    {
                        track_flag=0;
                        turn_flag=1;
                        back_flag=0;
#if PLAN == 1
                        Motor_PID(20,-20);
#endif
                    }
                    else
                    {
                        track_flag=0;
                        turn_flag=0;
                        back_flag=0;
                        pathlength=0;
                        state_put=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
            }
            else if(state_put==1)
            {
                if(tx_state==0 && rx_state==0)
                    {
                      runActionGroup(1,1);  //执行动作�?  
                        tx_state=1;
                        blue = 1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
                    else if(tx_state==1 && rx_state==1)
                    {
                        state_put =0;
                        tx_state=0;
                        rx_state=0;
                        state_catch=1;
                        pathlength = 0;
                       // car_one_task=CAR_END;
                        car_one_task = ONE_TASK_SPECIAL;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                        break;
                    }
            }
        case TURN_GREEN:
            if(state_put==0)
            {
#if PLAN==1
                if(pathlength<1375)
#else
                if(pathlength<2225)//绿色放置点角�?
#endif
                    {
                        track_flag=0;
                        turn_flag=1;
                        back_flag=0;
#if PLAN == 1
                Motor_PID(-20,20);
#endif
                    }
                    else
                    {
                        track_flag=0;
                        turn_flag=0;
                        back_flag=0;
                        pathlength=0;
                        state_put=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
            }
            else if(state_put==1)
            {
                if(tx_state==0 && rx_state==0)
                    {
                      runActionGroup(1,1);  //执行动作�?  
                        tx_state=1;
                        green = 1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
											
                    }
                    else if(tx_state==1 && rx_state==1)
                    {
                        state_put =0;
                        tx_state=0;
                        rx_state=0;
                        state_catch=1;
                        pathlength = 0;
                      //  car_one_task=CAR_END;
                        car_one_task = ONE_TASK_SPECIAL;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                        break;
                    }
            }
        case TURN_RED:
            if(state_put==0)
            {
#if PLAN==1
                if(pathlength<425)
#else
                if(pathlength<3300)//红色放置点角�?
#endif
                    {
                        track_flag=0;
                        turn_flag=1;
                        back_flag=0;
#if PLAN == 1
                Motor_PID(-20,20);
#endif
                    }
                    else
                    {
                        track_flag=0;
                        turn_flag=0;
                        back_flag=0;
                        pathlength=0;
                        state_put=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
            }
            else if(state_put==1)
            {
                if(tx_state==0 && rx_state==0)
                    {
                       runActionGroup(1,1);  //执行动作�?   //执行动作�? //执行动作�?
                        tx_state=1;
                        red = 1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                    }
                    else if(tx_state==1 && rx_state==1)
                    {
                        state_put =0;
                        tx_state=0;
                        rx_state=0;
                        state_catch=1;
                        pathlength = 0;
                      //  car_one_task=CAR_END;
                        car_one_task = ONE_TASK_SPECIAL;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                        break;
                    }
            }
        case TURN_GRAY:
            state_catch=1;
            //car_one_task=CAR_END;
					car_one_task = ONE_TASK_SPECIAL;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
            break;
        default:
            break;
        }
    }
        break;
				case ONE_TASK_SPECIAL:
					if(gray_state == 1)
					{
					if(state_catch == 1) //转弯
					{
					if(pathlength<abs(distance))
					{
                        track_flag=0;
                        turn_flag=1;
                        back_flag=0;
#if PLAN==1
            if(distance>0)
                Motor_PID(20,-20);
            else
                Motor_PID(-20,20);
#endif
					}
					else 
					{
					    car_one_task=ONE_TASK_SPECIAL;
                        pathlength=0;
                        track_flag=0;
                        turn_flag=0;
                        back_flag=0;
                        state_catch = 2;
                        state_put = 1; 
#if PLAN == 1
                        Motor_PID(0,0);
#endif
					}
					}
					else if(state_catch == 2)
					{
					if(pathlength<2000)
					{
                        track_flag=0;
                        turn_flag=0;
                        back_flag=1;
#if PLAN == 1
                        Motor_PID(20,20);
#endif
					}
					else
					{
					    car_one_task=ONE_TASK_SPECIAL;
                        pathlength=0;
                        track_flag=0;
                        turn_flag=0;
                        back_flag=0;
                        state_catch = 0;
                        state_put = 1; 
#if PLAN == 1
                        Motor_PID(0,0);
#endif
					}
					}
					else if(state_put == 1)
					{
					if(tx_state == 0 && rx_state == 0)
					{
					//执行动作组放黑色
						tx_state = 1;
						gray = 1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
					}
					else if(tx_state == 1 && rx_state == 1)
					{
                        state_put =0;
                        tx_state=0;
                        rx_state=0;
                        state_catch=1;
                        car_one_task = CAR_END;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
						break;
					}
					}
					}
					else
					{
						if(state_catch == 1)
						{
						if(pathlength<abs(distance))
						{
                            track_flag=0;
                            turn_flag=1;
                            back_flag=0;
#if PLAN==1
            if(distance>0)
                Motor_PID(20,-20);
            else
                Motor_PID(-20,20);
#endif
						}
						else 
						{
                            pathlength=0;
                            track_flag=0;
                            turn_flag=0;
                            back_flag=0;
						    state_catch = 1;
							car_one_task=CAR_END;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
							break;
						}
						}
					break;
					}
					break;
    case CAR_END:
         if(state_catch ==1)//黑色少走，其他一�?
        {
           if(gray_state == 1)
					 {
					 if(pathlength<0.5*TO_destination_BACK)
					 {
					        track_flag=0;
                            turn_flag=0;
                            back_flag=0;
						    back1_flag = 1;
                //倒车
					 }
					 else
					 {
					        pathlength=0;
                            track_flag=0;
                            turn_flag=0;
                            back_flag=0;
						    back1_flag = 0;
                            car_one_task=CAR_END;
                            state_catch=2;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
					 }
					 }
					else
					{
						if(pathlength<1700)
                        {
                            track_flag=0;
                            turn_flag=1;
                            back_flag=0;
                            back1_flag = 0;
#if PLAN == 1
                        Motor_PID(20,-20);
#endif
                            //直走

                        }
						else if(pathlength <6500)
						{
						    track_flag=1;
                            turn_flag=0;
                            back_flag=0;
							back1_flag = 0;
#if PLAN == 1
                        Track(20);
#endif
                //直走
						}
            else{
                pathlength=0;
                track_flag=0;
                turn_flag=0;
                back_flag=0;
                back1_flag = 0;
                car_one_task=CAR_END;
                state_catch=2;
            }
					}
        }
        else if(state_catch ==2)//到达2点以后转90°
        {
 
             if(pathlength<900)
            {
                track_flag=0;
                turn_flag=1;
                back_flag=0;
#if PLAN == 1
                    Motor_PID(20,-20);
#endif
                //转弯

            }
            else{
                pathlength=0;
                track_flag=0;
                turn_flag=0;
                back_flag=0;
                car_one_task=CAR_END;
                state_catch=3;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
            }
        }
        else if(state_catch ==3)//到达2点转弯以后的巡线
        {
            if(pathlength<3500)
            {
                track_flag=1;
                turn_flag=0;
                back_flag=0;
                //直走
#if PLAN == 1
                        Track(20);
#endif
            }
            else{
                pathlength=0;
                track_flag=0;
                turn_flag=0;
                back_flag=0;
                car_one_task=CAR_END;
                state_catch=4;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
            }
        }
         else if(state_catch ==4)//到达home前十字转90°
        {
            distance=850;
            if(pathlength<distance)
            {
                track_flag=0;
                turn_flag=1;
                back_flag=0;
#if PLAN == 1
                        Motor_PID(20,-20);
#endif

            }
            else{
                pathlength=0;
                track_flag=0;
                turn_flag=0;
                back_flag=0;
                car_one_task=CAR_END;
                state_catch=5;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
            }
        }
        else if(state_catch ==5)//home前十字准备倒车回去
        {
            if(pathlength<1300)
            {
                track_flag=0;
                turn_flag=0;
                back_flag=1;
#if PLAN == 1
                        Motor_PID(20,20);
#endif
            }
            else{
                pathlength=0;
                track_flag=0;
                turn_flag=0;
                back_flag=0;
               // car_one_task=CAR_END;
                car_one_task = ONE_TASK_STOP;
                state_catch=1;
#if PLAN == 1
                        Motor_PID(0,0);
#endif
                break;
            }
        }
        break;
		case  ONE_TASK_STOP:
		//	Motor_PID (0,0);
	            	track_flag=0;
                turn_flag=0;
                back_flag=0;
			break;
    default:
        break;
    }
}

void mode_select_two(void)
{
   switch(car_two_task)
	 {
		 case CAR_CODE:
			 if(rx4_state == 0 && tx4_state == 0)
			 {
			 HAL_UART_Transmit_DMA(&huart4,find_code,1);
			 }
			 else if(rx4_state == 1 && tx4_state == 1)
			 {
			 state_catch = 1;
			 car_two_task = CAR_GO;
			 break;
			 }
		 break;
		 case CAR_GO:
            if(state_catch==3)
            {
                if(pathlength<1200)
                {
                    track_flag=0;
                    turn_flag=0;
                    back_flag=1;
#if PLAN == 1
                    Motor_PID(20,20);
#endif
                }
                else 
                {
                    pathlength=0;
                    track_flag=0;
                    turn_flag=0;
                    back_flag=0;
                    car_two_task = CAR_GO;
                    state_catch=1;
                    break;
                }
            }
			else if(state_catch == 1)
			 {
			    if(pathlength<700)//转弯
                    {
                        track_flag=0;
                        turn_flag=1;
                        back_flag=0;
                    }
                    else{
                        pathlength=0;
                        track_flag=0;
                        turn_flag=0;
                        back_flag=0;
                        car_two_task = CAR_GO;
                        state_catch=2;
                        break;
                    }
			 }
			else if(state_catch == 2)
			 {
                if(stop_flag == 0)
                {
                    track_flag=1;
                    turn_flag=0;
                    back_flag=0;
                }
                else if(stop_flag == 1)
                {
                    pathlength=0;
                    track_flag=0;
                    turn_flag=0;
                    back_flag=0;
                    car_two_task = CAR_GO;
                    state_catch=0;
                }
			 }
			else if(state_catch == 0)
			 {
                if(catch_num == 0) 
                {
                    if(tx_state == 0 && rx_state == 0)
                    {
                        //执行动作组抓第一次，放一号框
                        tx_state = 1;
                    }
                    else if(tx_state == 1 && rx_state == 1)
                    {
                        catch_num = 1;
                        rx_state = 0;
                        tx_state = 0;
                        car_two_task = CAR_GO;
                        state_catch=0;
                        break;
                    } 
                }
                else if(catch_num == 1)
                {
                    if(tx_state == 0 && rx_state == 0)
                    {
                        //执行动作组抓第二次，放二号框
                        tx_state = 1;
                    }
                    else if(tx_state == 1 && rx_state == 1)
                    {
                        catch_num = 2;
                        rx_state = 0;
                        tx_state = 0;
                        car_two_task = CAR_GO;
                        state_catch=0;
                        break;
                    } 
                }
			 else if(catch_num == 2)
			 {
                if(tx_state == 0 && rx_state == 0)
                {
                    //执行动作组抓第三次，放三号框
                    tx_state = 1;
                }
                else if(tx_state == 1 && rx_state == 1)
                {
                    catch_num = 3;
                    rx_state = 0;
                    tx_state = 0;
                    car_two_task = CAR_GO;
                    state_catch=0;
                    break;
                } 
			 }
			 else if(catch_num == 3)
			 {
                if(tx_state == 0 && rx_state == 0)
                {
                    //执行动作组抓第四次，放四号框
                    tx_state = 1;
                }
                else if(tx_state == 1 && rx_state == 1)
                {
                catch_num = 4;
                    rx_state = 0;
                    tx_state = 0;
                    car_two_task = CAR_GO;
                    state_catch=0;
                    break;
                } 
			 }
			 else if(catch_num == 4)
			 {
                if(tx_state == 0 && rx_state == 0)
                {
                    //执行动作组抓第五次，放五号框
                    tx_state = 1;
                }
                else if(tx_state == 1 && rx_state == 1)
                {
                    catch_num = 5;
                    rx_state = 0;
                    tx_state = 0;
                    car_two_task = CAR_PUT_A;
                    state_catch=1;
                    break;
                } 
			 }
			 }
			break;
		 case CAR_PUT_A:
			 if(stop == 0)
			 {
                track_flag=1;
                turn_flag=0;
                back_flag=0;
			 }
			 else if(stop ==1)
			 {
                track_flag=0;
                turn_flag=0;
                back_flag=0;
                stop = 2;
                pathlength = 0;
                car_two_task = CAR_PUT_A;
				 break;
			 }
			 else if(stop == 2)
			 {
                switch(put_state)
                {
                    case PUT_ONE:
                        if(tx_state == 0 && rx_state == 0)
                        {
                            //执行动作组将1放到A�?
                            tx_state = 1;
                        }
                        else if(tx_state == 1 &&rx_state == 1)
                        {
                            rx_state = 0;
                            tx_state = 0;
                            stop = 0;
                            car_two_task = CAR_PUT_D;
                            break;
                        }
                        break;			 
				 	case PUT_TWO:
                        if(tx_state == 0 && rx_state == 0)
                        {
                            //执行动作组将2放到A�?
                            tx_state = 1;
                        }
                        else if(tx_state == 1 &&rx_state == 1)
                        {
                            rx_state = 0;
                            tx_state = 0;
                            stop = 0;
                            car_two_task = CAR_PUT_D;
                            break;
                        }
                        break;		
				 	case PUT_THREE:
                        if(tx_state == 0 && rx_state == 0)
                        {
                            //执行动作组将3放到A�?
                            tx_state = 1;
                        }
                        else if(tx_state == 1 &&rx_state == 1)
                        {
                            rx_state = 0;
                            tx_state = 0;
                            stop = 0;
                            car_two_task = CAR_PUT_D;
                            break;
                        }
                        break;		
				 	case PUT_FOUR:
                        if(tx_state == 0 && rx_state == 0)
                        {
                            //执行动作组将4放到A�?
                            tx_state = 1;
                        }
                        else if(tx_state == 1 &&rx_state == 1)
                        {
                            rx_state = 0;
                            tx_state = 0;
                            stop = 0;
                            car_two_task = CAR_PUT_D;
                            break;
                        }
                        break;	
				 case PUT_FIVE:
                    if(tx_state == 0 && rx_state == 0)
                    {
                        //执行动作组将5放到A�?
                        tx_state = 1;
                    }
                    else if(tx_state == 1 &&rx_state == 1)
                    {
                    rx_state = 0;
                        tx_state = 0;
                        stop = 0;
                        car_two_task = CAR_PUT_D;
                        break;
                    }
                    break;						 
				default:
					break;
			 }
			 }
			break;
		    case CAR_PUT_D:
                if(stop == 0)
                {
                    track_flag=1;
                    turn_flag=0;
                    back_flag=0;
                }
                else if(stop ==1)
                {
                    track_flag=0;
                    turn_flag=0;
                    back_flag=0;
                    stop = 2;
                    pathlength = 0;
                    car_two_task = CAR_PUT_D;
                    break;
                }
                else if(stop == 2)
                {
                    switch(put_state)
                    {
                        case PUT_ONE:
                            if(tx_state == 0 && rx_state == 0)
                            {
                                //执行动作组将1放到D�?
                                tx_state = 1;
                            }
                            else if(tx_state == 1 &&rx_state == 1)
                            {
                                rx_state = 0;
                                tx_state = 0;
                                stop = 0;
                                car_two_task = CAR_PUT_C;
                                break;
                            }
                            break;			 
                        case PUT_TWO:
                            if(tx_state == 0 && rx_state == 0)
                            {
                                //执行动作组将2放到D�?
                                tx_state = 1;
                            }
                            else if(tx_state == 1 &&rx_state == 1)
                            {
                            rx_state = 0;
                                tx_state = 0;
                                stop = 0;
                                car_two_task = CAR_PUT_C;
                                break;
                            }
                            break;		
                        case PUT_THREE:
                            if(tx_state == 0 && rx_state == 0)
                            {
                                //执行动作组将3放到D�?
                                tx_state = 1;
                            }
                            else if(tx_state == 1 &&rx_state == 1)
                            {
                            rx_state = 0;
                                tx_state = 0;
                                stop = 0;
                                car_two_task = CAR_PUT_C;
                                break;
                            }
                            break;		
                        case PUT_FOUR:
                            if(tx_state == 0 && rx_state == 0)
                            {
                                //执行动作组将4放到D�?
                                tx_state = 1;
                            }
                            else if(tx_state == 1 &&rx_state == 1)
                            {
                                rx_state = 0;
                                tx_state = 0;
                                stop = 0;
                                car_two_task = CAR_PUT_C;
                                break;
                            }
                            break;	
                        case PUT_FIVE:
                            if(tx_state == 0 && rx_state == 0)
                            {
                                //执行动作组将5放到D�?
                                tx_state = 1;
                            }
                            else if(tx_state == 1 &&rx_state == 1)
                            {
                                rx_state = 0;
                                tx_state = 0;
                                stop = 0;
                                car_two_task = CAR_PUT_C;
                                break;
                            }
                             break;						 
                        default:
                            break;
                    }
                }
                break;
				 case CAR_PUT_C:
				    if(stop == 0)
                    {
                        track_flag=1;
                        turn_flag=0;
                        back_flag=0;
                    }
                    else if(stop ==1)
                    {
                        track_flag=0;
                        turn_flag=0;
                        back_flag=0;
                        stop = 2;
                        pathlength = 0;
                        car_two_task = CAR_PUT_C;
                        break;
                    }
                    else if(stop == 2)
                    {
                    switch(put_state)
                    {
                        case PUT_ONE:
                            if(tx_state == 0 && rx_state == 0)
                            {
                                //执行动作组将1放到C�?
                                tx_state = 1;
                            }
                            else if(tx_state == 1 &&rx_state == 1)
                            {
                                rx_state = 0;
                                tx_state = 0;
                                stop = 0;
                                car_two_task = CAR_PUT_B;
                                break;
                            }
                            break;			 
                        case PUT_TWO:
                            if(tx_state == 0 && rx_state == 0)
                            {
                                //执行动作组将2放到C�?
                                tx_state = 1;
                            }
                            else if(tx_state == 1 &&rx_state == 1)
                            {
                                rx_state = 0;
                                tx_state = 0;
                                stop = 0;
                                car_two_task = CAR_PUT_B;
                                break;
                            }
                            break;		
                        case PUT_THREE:
                            if(tx_state == 0 && rx_state == 0)
                            {
                                //执行动作组将3放到C�?
                                tx_state = 1;
                            }
                            else if(tx_state == 1 &&rx_state == 1)
                            {
                                rx_state = 0;
                                tx_state = 0;
                                stop = 0;
                                car_two_task = CAR_PUT_B;
                                break;
                            }
                            break;		
                        case PUT_FOUR:
                            if(tx_state == 0 && rx_state == 0)
                            {
                                //执行动作组将4放到C�?
                                tx_state = 1;
                            }
                            else if(tx_state == 1 &&rx_state == 1)
                            {
                            rx_state = 0;
                                tx_state = 0;
                                stop = 0;
                                car_two_task = CAR_PUT_B;
                                break;
                            }
                            break;	
                        case PUT_FIVE:
                            if(tx_state == 0 && rx_state == 0)
                            {
                                //执行动作组将5放到C�?
                                tx_state = 1;
                            }
                            else if(tx_state == 1 &&rx_state == 1)
                            {
                            rx_state = 0;
                                tx_state = 0;
                                stop = 0;
                                car_two_task = CAR_PUT_B;
                                break;
                            }
                            break;						 
                        default:
                            break;
                    }
                    }
                            break;
                    case CAR_PUT_B:
                        if(stop == 0)
                        {
                            track_flag=1;
                            turn_flag=0;
                            back_flag=0;
                        }
                        else if(stop ==1)
                        {
                            track_flag=0;
                            turn_flag=0;
                            back_flag=0;
                            stop = 2;
                            pathlength = 0;
                            car_two_task = CAR_PUT_B;
                            break;
                        }
                        else if(stop == 2)
                        {
                            switch(put_state)
                            {
                                case PUT_ONE:
                                if(tx_state == 0 && rx_state == 0)
                                {
                                    //执行动作组将1放到B�?
                                    tx_state = 1;
                                }
                                else if(tx_state == 1 &&rx_state == 1)
                                {
                                    rx_state = 0;
                                    tx_state = 0;
                                    stop = 0;
                                    car_two_task = CAR_PUT_E;
                                    break;
                                }
                                break;			 
                                case PUT_TWO:
                                    if(tx_state == 0 && rx_state == 0)
                                    {
                                        //执行动作组将2放到B�?
                                        tx_state = 1;
                                    }
                                    else if(tx_state == 1 &&rx_state == 1)
                                    {
                                    rx_state = 0;
                                        tx_state = 0;
                                        stop = 0;
                                        car_two_task = CAR_PUT_E;
                                        break;
                                    }
                                    break;		
                                case PUT_THREE:
                                    if(tx_state == 0 && rx_state == 0)
                                    {
                                        //执行动作组将3放到B�?
                                        tx_state = 1;
                                    }
                                    else if(tx_state == 1 &&rx_state == 1)
                                    {
                                    rx_state = 0;
                                        tx_state = 0;
                                        stop = 0;
                                        car_two_task = CAR_PUT_E;
                                        break;
                                    }
                                    break;		
                                case PUT_FOUR:
                                    if(tx_state == 0 && rx_state == 0)
                                    {
                                        //执行动作组将4放到B�?
                                        tx_state = 1;
                                    }
                                    else if(tx_state == 1 &&rx_state == 1)
                                    {
                                    rx_state = 0;
                                        tx_state = 0;
                                        stop = 0;
                                        car_two_task = CAR_PUT_E;
                                        break;
                                    }
                                    break;	
                                case PUT_FIVE:
                                    if(tx_state == 0 && rx_state == 0)
                                    {
                                        //执行动作组将5放到B�?
                                        tx_state = 1;
                                    }
                                    else if(tx_state == 1 &&rx_state == 1)
                                    {
                                    rx_state = 0;
                                        tx_state = 0;
                                        stop = 0;
                                        car_two_task = CAR_PUT_E;
                                        break;
                                    }
                                    break;						 
                            default:
                                    break;
                        }
                        }
                                break;
				 case CAR_PUT_E:
					 if(white == 0|| red == 0||gray == 0)
					 {
                            if(state_catch == 1)
                            {
                                if(pathlength<700)
                                {
                                    track_flag=0;
                                    turn_flag=1;
                                    back_flag=0;
                                }
                                else 
                                {
                                    pathlength = 0;
                                    track_flag=0;
                                    turn_flag=0;
                                    back_flag=0;
                                    state_catch =2;
                                    car_two_task = CAR_PUT_E; 
                                }
                            }
                        else if(state_catch == 2)
                        {
                            if(pathlength<2000)
                            {
                                track_flag=1;
                                turn_flag=0;
                                back_flag=0;
                            }
                            else 
                            {
                                pathlength = 0;
                                track_flag=0;
                                turn_flag=0;
                                back_flag=0;
                                state_catch =3;
                                car_two_task = CAR_PUT_E; 
                            }
                        }
                        else if(state_catch == 3)
                        {
                            if(gray == 0)
                            {
                                if(tx_state == 0 && rx_state == 0)
                                {
                                //执行动作组放�?
                                    tx_state = 1;
                                }
                                else if(tx_state == 1 && rx_state == 1)
                                {
                                    car_two_task = CAR_BACK;
                                    tx_state = 0;
                                    rx_state = 0;
                                    state_catch = 1;
                                    break;
                                }
                            }
                            else if(white == 0)
                                {
                                    if(state_put == 0)
                                    {
                                        if(pathlength<2100)
                                        {
                                            track_flag=0;
                                            turn_flag=1;
                                            back_flag=0;
                                        }
                                        else 
                                        {
                                            pathlength = 0;
                                            track_flag=0;
                                            turn_flag=0;
                                            back_flag=0;
                                            state_put = 1;
                                        }
                                    }
                                    else if(state_put == 1)
                                    {
                                        if(tx_state == 0 &&rx_state == 0)
                                        {
                                        //执行动作组放�?
                                            tx_state = 1;
                                        }
                                        else if(tx_state == 1 && rx_state == 1)
                                        {
                                            tx_state = 0;
                                            rx_state = 0;
                                            state_catch = 1;
                                            car_two_task = CAR_BACK;
                                            state_put = 0;
                                            break;
                                        }
                                    }
                                }
                            else if(red == 0)
                            {
                                if(state_put == 0)
                                {
                                    if(pathlength<700)
                                    {
                                        track_flag=0;
                                        turn_flag=1;
                                        back_flag=0;
                                    }
                                    else 
                                    {
                                        pathlength = 0;
                                        track_flag=0;
                                        turn_flag=0;
                                        back_flag=0;
                                        state_put = 1;
                                    }
                                }
                                else if(state_put == 1)
                                {
                                    if(tx_state == 0 && rx_state == 0)
                                    {
                                    //执行动作组放�?
                                        tx_state = 1;
                                    }
                                    else if(tx_state == 1 && rx_state == 1)
                                    {
                                        tx_state = 0;
                                        rx_state = 0;
                                        state_catch = 1;
                                        car_two_task = CAR_BACK;
                                        state_put = 0;
                                        break;
                                    }
                                }
                            }
                        }
					}
					else if(blue == 0||green == 0)
					 {
                            if(state_catch == 1)
                            {
                                if(pathlength<10000)//回到2�?
                                {
                                    track_flag=1;
                                    turn_flag=0;
                                    back_flag=0;
                                }
                                else 
                                {
                                        pathlength = 0;
                                        track_flag=0;
                                        turn_flag=0;
                                        back_flag=0;
                                        state_catch = 2;
                                }
                            }
                            else if(state_catch == 2)
                            {
                                if(pathlength <700)
                                {
                                        track_flag=0;
                                        turn_flag=1;
                                        back_flag=0;
                                }
                                else 
                                {
                                        pathlength = 0;
                                        track_flag=0;
                                        turn_flag=0;
                                        back_flag=0;
                                        state_put = 0;
                                        state_catch = 3;
                                }
                            }
                            else if(state_catch == 3)
                            {
                                if(pathlength <2000)
                                {
                                    track_flag=1;
                                    turn_flag=0;
                                    back_flag=0;
                                }
                                else 
                                {
                                        pathlength = 0;
                                        track_flag=0;
                                        turn_flag=0;
                                        back_flag=0;
                                        state_put = 0;
                                        state_catch = 4;
                                }
                            }
                            else if(state_catch == 4)
                            {
                            if(blue == 0)
                            {
                                if(state_put == 0)
                                {
                                    if(pathlength <700)
                                    {
                                        track_flag=0;
                                        turn_flag=1;
                                        back_flag=0;
                                    }
                                    else 
                                    {
                                        pathlength = 0;
                                        track_flag=0;
                                        turn_flag=0;
                                        back_flag=0;
                                        state_put = 1;
                                        state_catch = 4;
                                    }
                                }
                                else if(state_put == 1)
                                {
                                    if(tx_state == 0 && rx_state == 0)
                                    {
                                    //执行动作组放�?
                                        tx_state = 1;
                                    }
                                    else if(tx_state == 1 && rx_state == 1)
                                    {
                                        tx_state = 0;
                                        rx_state = 0;
                                        state_catch = 1;
                                        state_put = 0;
                                        car_two_task = CAR_BACK;
                                        break;
                                    }
                                }
                            }
                            else if(green == 0)
                            {
                                if(state_put == 0)
                                {
                                    if(pathlength <2100)
                                    {
                                        track_flag=0;
                                        turn_flag=1;
                                        back_flag=0;
                                    }
                                    else 
                                    {
                                        pathlength = 0;
                                        track_flag=0;
                                        turn_flag=0;
                                        back_flag=0;
                                        state_put = 1;
                                        state_catch = 4;
                                    }
                                }
                                else if(state_put == 1)
                                {
                                    if(tx_state == 0 && rx_state == 0)
                                    {
                                    //执行动作组放�?
                                        tx_state = 1;
                                    }
                                    else if(tx_state == 1 && rx_state == 1)
                                    {
                                        tx_state = 0;
                                        rx_state = 0;
                                        state_catch = 1;
                                        state_put = 0;
                                        car_two_task = CAR_BACK;
                                        break;
                                    }
                                }
                            }
                        }
					 }
					 break;
			case CAR_BACK:
                if(gray==0)
                {
                    if(state_catch==1)
                    {
                        if(pathlength<1800)
                        {
                            track_flag=0;
                            turn_flag=1;
                            back_flag=0;
                        }
                        else
                        {
                            pathlength = 0;
                            track_flag=0;
                            turn_flag=0;
                            back_flag=0;
                            state_catch=2;
                            car_two_task = CAR_BACK;
                        }
                    }
                    else if(state_catch==2)
                    {
                         if(pathlength<2100)
                        {
                            track_flag=1;
                            turn_flag=0;
                            back_flag=0;
                        }
                        else
                        {
                            pathlength = 0;
                            track_flag=0;
                            turn_flag=0;
                            back_flag=0;
                            state_catch=3;
                            car_two_task = CAR_BACK;
                        }
                    }
                    else if(state_catch ==3)
                    {
                        if(pathlength<700)
                        {
                            track_flag=0;
                            turn_flag=1;
                            back_flag=0;
                        }
                        else
                        {
                            pathlength = 0;
                            track_flag=0;
                            turn_flag=0;
                            back_flag=0;
                            state_catch=4;
                            car_two_task = CAR_BACK;
                        }
                    }
                    else if(state_catch==4)
                    {
                        if(pathlength<14000)
                        {
                            track_flag=1;
                            turn_flag=0;
                            back_flag=0;
                        }
                        else
                        {
                            pathlength = 0;
                            track_flag=0;
                            turn_flag=0;
                            back_flag=0;
                            state_catch=5;
                            car_two_task = CAR_BACK;
                        }
                    }
                    else if(state_catch ==5)
                    {
                         if(pathlength<700)
                        {
                            track_flag=0;
                            turn_flag=1;
                            back_flag=0;
                        }
                        else
                        {
                            pathlength = 0;
                            track_flag=0;
                            turn_flag=0;
                            back_flag=0;
                            state_catch=0;
                            car_two_task = CAR_BACK;
                        }
                    }
                    else if(state_catch==0)
                    {
                         if(pathlength<400)
                        {
                            track_flag=0;
                            turn_flag=0;
                            back_flag=1;
                        }
                        else
                        {
                            pathlength = 0;
                            track_flag=0;
                            turn_flag=0;
                            back_flag=0;
                            state_catch=0;
                            car_two_task = CAR_BACK;
                        }
                    }
                }
				
					break;
		 case CAR_ALL_END:
			 Motor_PID(0,0);
		 break;
		 default:
		 break;
	 }
}
