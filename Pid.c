#include "stdio.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define PID_realize1_falg 0

typedef struct pid
{
  float target_val; // 目标值
  float actual_val; // 实际值
  float err;        // 偏差值
  float err_last;   // 上一个偏差值
  float err_next;
  float Kp; // 比列，积分 微分
  float Ki;
  float Kd;
  float integral; // 积分值
} pid;

void Position_PIDInit(pid *pid_t, float target_val, float actual_val, float err, float err_last, float err_next, float Kp, float Ki, float Kd, float integral)
{
  pid_t->target_val = target_val;
  pid_t->actual_val = actual_val;
  pid_t->err = err;
  pid_t->err_last = err_last;
  pid_t->Kp = Kp;
  pid_t->Ki = Ki;
  pid_t->Kd = Kd;
  pid_t->integral = integral;
}

/**
 * @brief 位置式PID
 *
 * @param temp_val 传入目标值
 * @return float actual_val实际值
 */
#if PID_realize1_falg == 0
float PID_realize(pid *pid_t, float temp_val)
{
  // 计算实际值与目标值的偏差
  pid_t->err = pid_t->target_val - temp_val;
  // 误差累积
  pid_t->integral += pid_t->err;
  // PID算法的实现
  pid_t->actual_val = pid_t->Kp * pid_t->err + pid_t->Ki * pid_t->integral + pid_t->Kd * (pid_t->err - pid_t->err_last);
  // 误差传递
  pid_t->err_last = pid_t->err;
  // 返回当前的实际值 PID输出的值
  return pid_t->actual_val;
}

/**
 * @brief  增量式PID
 *
 * @param temp_val
 * @return float
 */
#elif PID_realize1_falg == 1
float PID_realize(pid *pid_t,float temp_val)
{
  // 传入目标值
  pid_t->target_val = temp_val;
  // 计算目标值与实际值的误差
  pid_t->err = pid_t->target_val - pid_t->actual_val;
  // PID算法的实现
  float increment_val = pid_t->Kp * (pid_t->err - pid_t->err_next) + pid_t->Ki * pid_t->err + pid_t->Kd * (pid_t->err - 2 * pid_t->err_next + pid_t->err_last);
  // 累加
  pid_t->actual_val += increment_val;
  // 传递误差
  pid_t->err_last = pid_t->err_next;
  pid_t->err_next = pid_t->err;
  // 返回当前实际值
  return pid_t->actual_val;
}
#endif

int main()
{

  pid L;
  float ll;
  srand((unsigned int)time(NULL));
  int ret1;

  Position_PIDInit(&L, 100, 0, 0, 0, 0, 0.2, 0.2, 0.3, 0);

  printf("kp:%f ki:%f kd:%f\n", L.Kp, L.Ki, L.Kd);

  // ll = PID_realize(&L,10);

  /*user*/
  for (int i = 20; i <= 100; i = i + ret1)
  {
    ret1 = rand() % 10 + 1;
    ll = PID_realize(&L, i);
    printf("%.3f\t\v", ll);
  }

  /*uesr*/
#if 0
  for (int i = 0; i < 50;)
  {
    /* code */
    if (i % 10 == 0)
    {
      printf("\n");
    }
    i++;
    printf("%.1f\t", ll);
  }
#endif
  return 0;
}
