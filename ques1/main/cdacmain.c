/*   1. Create 3 realtime tasks each with the periodcity T1=1000ms, T2=2000ms, T3=5000ms. Also create two additional task T4 and T5 where T4 sends integer data to T5 using Messsage Queues.    */



#include <stdio.h>
#include<freertos/FreeRTOS.h>
#include<freertos/task.h>
#include<freertos/queue.h>



QueueHandle_t mq_data;


void task_1(void *pv)
{
   while(1)
   {
        printf("In Task_1.............\n");
        vTaskDelay(1000/portTICK_PERIOD_MS);
    }
}

void task_2(void *pv)
{
   while(1)
   {
        printf("In Task_2.............\n");
        vTaskDelay(2000/portTICK_PERIOD_MS);
    }
}

void task_3(void *pv)
{
   while(1)
   {
        printf("In Task_3.............\n");
        vTaskDelay(5000/portTICK_PERIOD_MS);
    }
}
void task_4(void *pv)
{
    int send_data=0;
    while(1)
    {
        send_data++;
       printf("In Task_4:send_data %d\n",send_data);
       xQueueSend(mq_data,&send_data,portMAX_DELAY);
       vTaskDelay(1000/portTICK_PERIOD_MS);
        
      }
}

void task_5(void *pv)
{
    int recv_data=0;
    while(1)
    {
        xQueueReceive(mq_data,&recv_data,portMAX_DELAY);
        printf("In Task_5:recv_data %d\n",recv_data);
    }
}
       

void app_main()
{
    mq_data=xQueueCreate(10,sizeof(int));
    xTaskCreate(task_1,"task_1",2048,NULL,5,NULL);
    xTaskCreate(task_2,"task_2",2048,NULL,6,NULL);
    xTaskCreate(task_3,"task_3",2048,NULL,7,NULL);
    xTaskCreate(task_4,"task_5",2048,NULL,8,NULL);
    xTaskCreate(task_5,"task_5",2048,NULL,9,NULL);
    
    printf("Hello world\n");
}
