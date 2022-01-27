/*  2. Create 3 realtime tasks each with the periodcity T1=1000ms, T2=2000ms, T3=5000ms. Also create use oneshot software timer to trigger a callback function from T3 after 10000ms.           */



#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/timers.h>

TimerHandle_t motor_timer_handle;

int count=0;

void task_1(void *pv)
{
  while(1)
  {
      printf("In Task_1............\n");
      vTaskDelay(1000/portTICK_PERIOD_MS);
   }
}

void task_2(void *pv)
{
  while(1)
  {
      printf("In Task_2............\n");
      vTaskDelay(2000/portTICK_PERIOD_MS);
   }
}

void task_3(void *pv)
{
  while(1)
  {
      printf("In Task_3............\n");
      vTaskDelay(5000/portTICK_PERIOD_MS);
   }
}

void TurnMotorOFF(TimerHandle_t xTimer)
{
    count++;
    printf("Turning motor off\n");

    if(count==5)
    {
        printf("turning off the time\n");
        xTimerStop(xTimer,0);
    }
}

/*void AlarmTask(void *pv)
{
       motor_timer_handle=xTimerCreate("MotorOFF",pdMS_TO_TICKS(2000),pdTRUE,NULL,TurnMotorOFF);
       xTimerStart(motor_timer_handle,0);
}*/

void app_main()
{
     motor_timer_handle=xTimerCreate("MotorOFF",pdMS_TO_TICKS(10000),pdTRUE,NULL,TurnMotorOFF);
       xTimerStart(motor_timer_handle,0);
     //xTaskCreate(AlarmTask,"AlarmTask",2048,NULL,5,NULL);
        xTaskCreate(task_1,"task_1",2048,NULL,5,NULL);
         xTaskCreate(task_2,"task_1",2048,NULL,6,NULL);
          xTaskCreate(task_3,"task_1",2048,NULL,7,NULL);
       while(1)
       {
            printf("main task\n");
            vTaskDelay(pdMS_TO_TICKS(1000));
      }
}
