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
TX_MUTEX mutex1;
TX_MUTEX mutex2;

char str1[1000]="A semaphore is a signalling mechanism and a thread that is waiting on a semaphore can be signaled by another thread.\n\r";
char str2[1000]="Mutex is a mutual exclusion object that synchronizes access to a resource. It is created with a unique name at the start of a program\n\r";
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

    tx_mutex_create(&mutex1,"Mutex_1",TX_NO_INHERIT);


    /* Allocate the stack for ThreadTwo.*/
    if (tx_byte_allocate(byte_pool, (VOID **) &pointer_2,
                         APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
    {
      ret = TX_POOL_ERROR;
    }

    /* Create ThreadTwo.*/
    if (tx_thread_create(&ThreadTwo, "Thread Two", ThreadTwo_Entry, 0,
                         pointer_2, APP_STACK_SIZE,
                         THREAD_TWO_PRIO, THREAD_TWO_PREEMPTION_THRESHOLD,
                         1, TX_AUTO_START) != TX_SUCCESS)
    {
      ret = TX_THREAD_ERROR;
    }

    tx_mutex_create(&mutex2,"Mutex_2",TX_NO_INHERIT);


  /* USER CODE END App_ThreadX_Init */

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
/**
  * @brief  Function implementing the ThreadOne thread.
  * @param  thread_input: Not used
  * @retval None
  */
void ThreadOne_Entry(ULONG thread_input)
{
  uint8_t t1_count=0;
  uint8_t i;
  UINT status;

  while(1)									/* Infinite loop */
  {
	  status=tx_mutex_get(&mutex1,TX_WAIT_FOREVER);
	  if(TX_SUCCESS==status)
	  {
	  HAL_UART_Transmit(&huart1,str1, strlen(str1), 100);
	  }
	  tx_mutex_put(&mutex1);
//	HAL_GPIO_TogglePin(GPIOH, GPIO_PIN_7);	/* Toggle GREEN LED */
//	App_Delay(500);							/* Delay for 100=1000ms */
	/*t1_count++;

	if(t1_count == 10)
	{
		t1_count = 0;
		tx_thread_sleep(100);//100 ticks
	}*/
  }
}

/**
  * @brief  Function implementing the ThreadOne thread.
  * @param  thread_input: Not used
  * @retval None
  */
void ThreadTwo_Entry(ULONG thread_input)
{
  uint8_t t2_count=0;
  uint8_t status;
    while(1)									/* Infinite loop */
  {
    status=tx_mutex_get(&mutex2,TX_WAIT_FOREVER);
    if(TX_SUCCESS==status)
     {
	  HAL_UART_Transmit(&huart1,str2, strlen(str2), 100);
     }
    tx_mutex_put(&mutex2);
//	HAL_GPIO_TogglePin(GPIOH,GPIO_PIN_6);	/* Toggle RED LED */
//	App_Delay(200);							/* Delay for 100=1000ms */
	/*t2_count++;

	if(t2_count == 5)
	{
		t2_count = 0;
		tx_thread_sleep(100);
	}*/
  }
}

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
