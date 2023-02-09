/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
  ******************************************************************************
    * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Includes ------------------------------------------------------------------*/
#include "app_threadx.h"

/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */

/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
extern UART_HandleTypeDef huart1;
TX_THREAD ThreadOne;
TX_THREAD ThreadTwo;
TX_QUEUE queue_0;
TX_TIMER Timerone;
TX_TIMER Timertwo;
TX_TIMER Timerthree;
extern volatile uint8_t flag;
VOID timerCB1(ulong);
VOID timerCB2(ulong);
VOID timerCB3(ulong);

char str1[1000]="thread green.\n\r";
char str2[1000]="Thread red\n\r";

/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
//extern UART_HandleTypeDef huart1;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void ThreadOne_Entry(ULONG thread_input);
void ThreadTwo_Entry(ULONG thread_input);
void App_Delay(uint32_t Delay);

/* USER CODE END PFP */

/**
  * @brief  Application ThreadX Initialization.
  * @param memory_ptr: memory pointer
  * @retval int
  */
UINT App_ThreadX_Init(VOID *memory_ptr)
{
  UINT ret = TX_SUCCESS;
  TX_BYTE_POOL *byte_pool = (TX_BYTE_POOL*)memory_ptr;

   /* USER CODE BEGIN App_ThreadX_MEM_POOL */
  (void)byte_pool;
  /* USER CODE END App_ThreadX_MEM_POOL */

  /* USER CODE BEGIN App_ThreadX_Init */
  CHAR *pointer_1;
  CHAR *pointer_2;
  CHAR *pointer_3;


    /* Allocate the stack for ThreadOne.  */
    if (tx_byte_allocate(byte_pool, (VOID **) &pointer_1,
                         APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
    {
      ret = TX_POOL_ERROR;
    }

    /* Create ThreadOne.  */
    if (tx_thread_create(&ThreadOne, "Thread One", ThreadOne_Entry, 0,
                         pointer_1, APP_STACK_SIZE,
                         THREAD_ONE_PRIO, THREAD_ONE_PREEMPTION_THRESHOLD,
                         1, TX_AUTO_START) != TX_SUCCESS)
    {
      ret = TX_THREAD_ERROR;
    }


    /* Allocate the stack for ThreadTwo.  */
       if (tx_byte_allocate(byte_pool, (VOID **) &pointer_2,
                            APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
       {
         ret = TX_POOL_ERROR;
       }

       /* Create ThreadTwo.  */
       if (tx_thread_create(&ThreadTwo, "Thread two", ThreadTwo_Entry, 0,
                            pointer_2, APP_STACK_SIZE,
                            THREAD_TWO_PRIO, THREAD_TWO_PREEMPTION_THRESHOLD,
                            1, TX_AUTO_START) != TX_SUCCESS)
       {
         ret = TX_THREAD_ERROR;
       }

    if (tx_byte_allocate(byte_pool, (VOID **) &pointer_3,
                             APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
        {
          ret = TX_POOL_ERROR;
        }

    if (tx_queue_create(&queue_0, "queue_0", 16,(VOID*)pointer_3, 1000) != TX_SUCCESS)
        {
          ret = TX_QUEUE_ERROR;
        }

    if(tx_timer_create(&Timerone,"timer one",timerCB1,1,100,100,TX_AUTO_ACTIVATE))
         {
       	  ret = TX_THREAD_ERROR;
         }

    if(tx_timer_create(&Timertwo,"timer two",timerCB2,1,100,100,TX_AUTO_ACTIVATE))
             {
           	  ret = TX_THREAD_ERROR;
             }

    if(tx_timer_create(&Timerthree,"timer three",timerCB3,1,100,100,TX_AUTO_ACTIVATE))
             {
           	  ret = TX_THREAD_ERROR;
             }

    return ret;
}

  /**
  * @brief  MX_ThreadX_Init
  * @param  None
  * @retval None
  */
void MX_ThreadX_Init(void)
{
  /* USER CODE BEGIN  Before_Kernel_Start */

  /* USER CODE END  Before_Kernel_Start */

  tx_kernel_enter();

  /* USER CODE BEGIN  Kernel_Start_Error */

  /* USER CODE END  Kernel_Start_Error */
}

/* USER CODE BEGIN 1 */

void timerCB1(ulong)
{
	HAL_UART_Transmit(&huart1, (uint8_t*)"\n\r !!!!!!!!!!! timer1 expired !!!!!!!!\n\r", 43, 100);
}

void timerCB2(ulong)
{
	HAL_UART_Transmit(&huart1, (uint8_t*)"\n\r !!!!!!!!!!! timer2 expired !!!!!!!!\n\r", 43, 100);
}

void timerCB3(ulong)
{
	HAL_UART_Transmit(&huart1, (uint8_t*)"\n\r !!!!!!!!!!! timer3 expired !!!!!!!!\n\r", 43, 100);
}
/**
  * @brief  Function implementing the ThreadOne thread.
  * @param  thread_input: Not used
  * @retval None
  */
void ThreadOne_Entry(ULONG thread_input)
{

//  while(1)									/* Infinite loop */
  //{
//	if(1 == flag)
//	{
//		HAL_UART_Transmit(&huart1,"odd function\n\r", 20, 100);
//		HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_7);	/* Toggle GREEN LED */
//		App_Delay(100);						/* Delay for 100=1000ms */
//	}
 //   else if(0 == flag)
  //  {
   // 	HAL_UART_Transmit(&huart1,"even function\n\r", 20, 100);
   // 	HAL_GPIO_TogglePin(GPIOH,GPIO_PIN_6);	/* Toggle RED LED */
   // 	App_Delay(200);							/* Delay for 100=1000ms */
    //}
 // }

	/*uint8_t msg[100]="\n\r welcome";
	UINT status;
	while(1)
	{
		HAL_UART_Transmit(&huart1,"\n\r..........Thread 1 send msg to queue........\n\r", 44, 100);
		status=tx_queue_send(&queue_0,msg,TX_WAIT_FOREVER);
		if(TX_SUCCESS == status)
		{
			HAL_UART_Transmit(&huart1,"\n\r..........Thread 1 sent msg into queue........\n\r", 46, 100);
			tx_thread_sleep(100);
		}
		else
		{
			HAL_UART_Transmit(&huart1,"\n\r.......Thread 1 failed tosend msg into queue........\n\r", 52, 100);
		}
	}*/

}

void ThreadTwo_Entry(ULONG thread_input)
{
	/*uint8_t msg_rx[100]="\n\r temp data";
	UINT status;
	while(1)
	{
		HAL_UART_Transmit(&huart1,"\n\r..........Thread 2 recieve queue data........\n\r", 45, 100);
		status=tx_queue_receive(&queue_0,msg_rx,TX_WAIT_FOREVER);
		if(TX_SUCCESS == status)
		{
			HAL_UART_Transmit(&huart1,"\n\r...........Thread 2 recieved the msg........\n\r", 45, 100);
			HAL_UART_Transmit(&huart1,msg_rx, 100, 100);
		}

	}*/
}

/**
  * @brief  Function implementing the ThreadOne thread.
  * @param  thread_input: Not used
  * @retval None
  */

/**
  * @brief  Application Delay function.
  * @param  Delay : number of ticks to wait
  * @retval None
  */
void App_Delay(uint32_t Delay)
{
  UINT initial_time = tx_time_get();
  while ((tx_time_get() - initial_time) < Delay);
}
/* USER CODE END 1 */
