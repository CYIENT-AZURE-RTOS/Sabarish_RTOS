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
TX_THREAD ThreadThree;
TX_EVENT_FLAGS_GROUP Event_group_1;
ULONG actual_evenets;


//TX_MUTEX MutexOne;
extern UART_HandleTypeDef huart1;

uint8_t text1[600] = "eeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeeee\r\n";
uint8_t text2[600] = "uuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuuu\r\n";
uint8_t status_event=0;



/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void ThreadOne_Entry(ULONG thread_input);
void ThreadTwo_Entry(ULONG thread_input);
void ThreadThree_Entry(ULONG thread_input);
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

  /* Allocate the stack for ThreadOne.  */
  if (tx_byte_allocate(byte_pool, (VOID **) &pointer1,
                       APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    ret = TX_POOL_ERROR;
  }

  /* Create ThreadOne.  */
  if (tx_thread_create(&ThreadOne, "Thread One", ThreadOne_Entry, 0,
                       pointer1, APP_STACK_SIZE,
                       THREAD_ONE_PRIO, THREAD_ONE_PREEMPTION_THRESHOLD,
                       1, TX_AUTO_START) != TX_SUCCESS)
  {
    ret = TX_THREAD_ERROR;
  }





  /* Allocate the stack for ThreadTwo.  */
    if (tx_byte_allocate(byte_pool, (VOID **) &pointer2,
                         APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
    {
      ret = TX_POOL_ERROR;
    }

    /* Create ThreadTwo.  */
    if (tx_thread_create(&ThreadTwo, "Thread Two", ThreadTwo_Entry, 0,
                         pointer2, APP_STACK_SIZE,
                         THREAD_ONE_PRIO, THREAD_ONE_PREEMPTION_THRESHOLD,
                         1, TX_AUTO_START) != TX_SUCCESS)
    {
      ret = TX_THREAD_ERROR;
    }
    /* Allocate the stack for ThreadOne.  */
      if (tx_byte_allocate(byte_pool, (VOID **) &pointer3,
                           APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
      {
        ret = TX_POOL_ERROR;
      }

      /* Create ThreaThree  */
        if (tx_thread_create(&ThreadThree, "Thread Three", ThreadThree_Entry, 0,
                             pointer3, APP_STACK_SIZE,
                             THREAD_ONE_PRIO, THREAD_ONE_PREEMPTION_THRESHOLD,
                             1, TX_AUTO_START) != TX_SUCCESS)
        {
          ret = TX_THREAD_ERROR;
        }

ret = tx_event_flags_create(&Event_group_1,"Event_Group1");
if(TX_SUCCESS != ret)
{
	HAL_UART_Transmit(&huart1,(uint8_t*)"\n\r\r\r Could not create the Event\r\r\n", 60, 100);
}


//    tx_mutex_create(&MutexOne,"Mutex one",TX_NO_INHERIT);

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


  while(1)									/* Infinite loop */
  {
	HAL_GPIO_TogglePin(LED_RED_GPIO_Port,LED_RED_Pin);	/* Toggle Green LED */
	App_Delay(10);							/* Delay for 100=1000ms */
	status_event = tx_event_flags_get(&Event_group_1,0x111,TX_AND_CLEAR,&actual_evenets,20);
	if(TX_SUCCESS == status_event)
	{
	HAL_UART_Transmit(&huart1,(uint8_t*)"\n\r\r\r Done successfully  \r\r\n", 60, 100);
	}
	  }//end while
}

void ThreadTwo_Entry(ULONG thread_input)
{

  while(1)									/* Infinite loop */
  {
HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin);	/* Toggle Green LED */
	App_Delay(10);
	status_event = tx_event_flags_set(&Event_group_1,0x11,TX_OR);
		if(TX_SUCCESS == status_event)
		{
	HAL_UART_Transmit(&huart1,(uint8_t*)"\n\r\r\r EVENT - 0 & 4  \r\r\n", 60, 100);
		}
  }//End while
}

void ThreadThree_Entry(ULONG thread_input)
{

  while(1)									/* Infinite loop */
  {
	  HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port,LED_GREEN_Pin);	/* Toggle Green LED */
	  status_event = tx_event_flags_set(&Event_group_1,0x100,TX_OR);
		if(TX_SUCCESS == status_event)
		{
	HAL_UART_Transmit(&huart1,(uint8_t*)"\n\r\r\r EVENT - 0 & 4  \r\r\n", 60, 100);
		}
	App_Delay(10);
  }//End while
}




void App_Delay(uint32_t Delay)
{
  UINT initial_time = tx_time_get();
  while ((tx_time_get() - initial_time) < Delay);
}



/* USER CODE END 1 */
