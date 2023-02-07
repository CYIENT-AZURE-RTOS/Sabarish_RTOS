/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_threadx.c
  * @author  MCD Application Team
  * @brief   ThreadX applicative file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2022 STMicroelectronics.
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
#include <string.h>
/* USER CODE END Includes */

/* Private typedef -----------------------------------------------------------*/
/* USER CODE BEGIN PTD */
uint8_t Thead_count=0;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
TX_THREAD ThreadOne;
TX_THREAD ThreadTwo;

TX_MUTEX MutexOne;
extern UART_HandleTypeDef huart1;

uint8_t text1[] = "\n\r Thread 1 is runing \n\r";
uint8_t text2[] = "\n\r Thread 2 is runing \n\r";

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

  /* USER CODE END App_ThreadX_MEM_POOL */

  /* USER CODE BEGIN App_ThreadX_Init */
  CHAR *pointer1;
  CHAR *pointer2;
  CHAR *pointer3;
  CHAR *pointer4;

  /* Allocate the stack for ThreadOne.  */
  ret = tx_byte_allocate(byte_pool, (VOID **) &pointer3,
                           4096, TX_NO_WAIT);

  ret = tx_byte_allocate(byte_pool, (VOID **) &pointer4,
                            80000, TX_NO_WAIT);


  ret = tx_byte_allocate(byte_pool, (VOID **) &pointer1,
                         40960, TX_NO_WAIT);

 /* if(ret != TX_SUCCESS)
  {
	  ret = TX_POOL_ERROR;
  }*/

  HAL_UART_Transmit(&huart1,ret, sizeof(ret), 100);

  /*if (tx_byte_allocate(byte_pool, (VOID **) &pointer1,
                       APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    ret = TX_POOL_ERROR;
  }*/

  /* Create ThreadOne.  */

  if (tx_thread_create(&ThreadOne, "Thread One", ThreadOne_Entry, 0,
                       pointer1, APP_STACK_SIZE,
                       THREAD_ONE_PRIO, THREAD_ONE_PREEMPTION_THRESHOLD,
                       1, TX_AUTO_START) != TX_SUCCESS)
  {
    ret = TX_THREAD_ERROR;
  }

  HAL_UART_Transmit(&huart1,ret, sizeof(ret), 100);

  /* Allocate the stack for ThreadTwo.  */
  ret = tx_byte_allocate(byte_pool, (VOID **) &pointer2,
                           80960, TX_NO_WAIT);

    /*if(ret != TX_SUCCESS)
    {
  	  ret = TX_POOL_ERROR;
    }*/
    HAL_UART_Transmit(&huart1,ret, sizeof(ret), 100);

    /*if (tx_byte_allocate(byte_pool, (VOID **) &pointer2,
                         APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
    {
      ret = TX_POOL_ERROR;
    }*/

    /* Create ThreadTwo.  */
    if (tx_thread_create(&ThreadTwo, "Thread Two", ThreadTwo_Entry, 0,
                         pointer2, APP_STACK_SIZE,
                         THREAD_ONE_PRIO, THREAD_ONE_PREEMPTION_THRESHOLD,
                         1, TX_AUTO_START) != TX_SUCCESS)
    {
      ret = TX_THREAD_ERROR;
    }

   // tx_mutex_create(&MutexOne,"Mutex one",TX_NO_INHERIT);

    HAL_UART_Transmit(&huart1,ret, sizeof(ret), 100);

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

void ThreadOne_Entry(ULONG thread_input)
{
	//UINT status_mutex;
  //uint8_t t1_count=0;
  while(1)									/* Infinite loop */
  {
	HAL_GPIO_TogglePin(LED_RED_GPIO_Port,LED_RED_Pin);	/* Toggle Green LED */
	App_Delay(10);							/* Delay for 100=1000ms */


	  //status_mutex =  tx_mutex_get(&MutexOne,TX_WAIT_FOREVER);

		  //HAL_UART_Transmit(&huart1,text1, sizeof(text1), 100);
		  //tx_mutex_put(&MutexOne);
		  App_Delay(10);
		  Thead_count++;


  }
}

void ThreadTwo_Entry(ULONG thread_input)
{
  //uint8_t t1_count=0;
	//UINT status_mutex;
  while(1)									/* Infinite loop */
  {
	HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin);	/* Toggle Green LED */
	App_Delay(10);							/* Delay for 100=1000ms */

		//HAL_UART_Transmit(&huart1,text2, sizeof(text2), 100);
		App_Delay(10);
		/*if(Thead_count>5)
		{
			tx_thread_terminate(&ThreadOne);
			tx_thread_delete(&ThreadOne);


		}*/
  }
}




void App_Delay(uint32_t Delay)
{
  UINT initial_time = tx_time_get();
  while ((tx_time_get() - initial_time) < Delay);
}



/* USER CODE END 1 */
