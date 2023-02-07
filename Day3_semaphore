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
TX_THREAD ThreadOne;
TX_THREAD ThreadTwo;
TX_THREAD ThreadThree;
TX_THREAD ThreadFour;
TX_SEMAPHORE Semaphore1;
TX_SEMAPHORE Semaphore2;
/* USER CODE END PTD */

/* Private define ------------------------------------------------------------*/
/* USER CODE BEGIN PD */
extern UART_HandleTypeDef huart1;
/* USER CODE END PD */

/* Private macro -------------------------------------------------------------*/
/* USER CODE BEGIN PM */

/* USER CODE END PM */

/* Private variables ---------------------------------------------------------*/
/* USER CODE BEGIN PV */
//char str1[500]="####Number of timer-ticks this thread is allowed to run before other ready threads of the same priority are given a chance####\r\n";
//char str2[500]="$$$$This service deletes the specified application thread. Since the specified thread must be in a ing to delete itself$$$$$\r\n";
uint8_t LED_STAT[2]= {0,0};// status of red led and
//uint8_t i;

/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void ThreadOne_Entry(ULONG thread_input);
void ThreadTwo_Entry(ULONG thread_input);
void ThreadThree_Entry(ULONG thread_input);
void ThreadFour_Entry(ULONG thread_input);
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
  CHAR *pointer_4;

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
//    create semaphore one

   if( tx_semaphore_create(&Semaphore1, "Semaphore1", 1) != TX_SUCCESS)
   {
	   ret = TX_THREAD_ERROR;
   }

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

    //    create semaphore two
    if( tx_semaphore_create(&Semaphore2, "Semaphore2", 1) != TX_SUCCESS)
    {
 	   ret = TX_THREAD_ERROR;
    }

    /* Allocate the stack for ThreadThree.  */
        if (tx_byte_allocate(byte_pool, (VOID **) &pointer_3,
                             APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
        {
          ret = TX_POOL_ERROR;
        }

        /* Create ThreadThree.  */
        if (tx_thread_create(&ThreadThree, "Thread Three", ThreadThree_Entry, 0,
                             pointer_3, APP_STACK_SIZE,
                             THREAD_THREE_PRIO, THREAD_THREE_PREEMPTION_THRESHOLD,
                             1, TX_AUTO_START) != TX_SUCCESS)
        {
          ret = TX_THREAD_ERROR;
        }

        /* Allocate the stack for ThreadFour.  */
            if (tx_byte_allocate(byte_pool, (VOID **) &pointer_4,
                                 APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
            {
              ret = TX_POOL_ERROR;
            }

            /* Create ThreadOne.  */
            if (tx_thread_create(&ThreadFour, "Thread Four", ThreadFour_Entry, 0,
                                 pointer_4, APP_STACK_SIZE,
                                 THREAD_FOUR_PRIO, THREAD_FOUR_PREEMPTION_THRESHOLD,
                                 1, TX_AUTO_START) != TX_SUCCESS)
            {
              ret = TX_THREAD_ERROR;
            }
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
  uint8_t status,pin,i;
//  uint8_t LED_STAT[2]= {0,0};
  while(1)									/* Infinite loop */
  {
	//HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);	/* Toggle Green LED */
	status = tx_semaphore_get(&Semaphore1, TX_WAIT_FOREVER);
	if(TX_SUCCESS == status)
	{
	HAL_UART_Transmit(&huart1, "SEMAPHORE 1 Locked\n\r", 22, 100);
		if(0==LED_STAT[0])
		{
			LED_STAT[0]=1;
			pin = RED_LED_Pin;
		}
		else if(0==LED_STAT[1])
		{
			LED_STAT[1]=1;
			pin = GREEN_LED_Pin;
		}
		i=0;

		while(i<20)
		{
		HAL_GPIO_TogglePin(GPIOH, pin);	/* Toggle Green LED */
		App_Delay(10);
		i++;
		}

		if(pin==RED_LED_Pin)
		{
		LED_STAT[0] = 0;
		}
		else if(pin == GREEN_LED_Pin)
		{
		LED_STAT[1] = 0;
		}
		HAL_UART_Transmit(&huart1, "SEMAPHORE 1 Released\n\r", 22, 100);
			tx_semaphore_put(&Semaphore1);
	}



  }
}

/**
  * @brief  Function implementing the ThreadThree thread.
  * @param  thread_input: Not used
  * @retval None
  */
void ThreadTwo_Entry(ULONG thread_input)
{
  uint8_t t2_count=0;
  uint8_t status, pin,i;
 // uint8_t LED_STAT[2]= {0,0};
  while(1)									/* Infinite loop */
   {
 	//HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);	/* Toggle Green LED */
 	status = tx_semaphore_get(&Semaphore1, TX_WAIT_FOREVER);
 	if(TX_SUCCESS == status)
 	{
 	HAL_UART_Transmit(&huart1, "SEMAPHORE 2 Locked\n\r", 22, 100);
 		if(0==LED_STAT[0])
 		{
 			LED_STAT[0]=1;
 			pin = RED_LED_Pin;
 		}
 		else if(0==LED_STAT[1])
 		{
 			LED_STAT[1]=1;
 			pin = GREEN_LED_Pin;
 		}
 		i=0;

 		while(i<9)
 		{
			HAL_GPIO_TogglePin(GPIOH, pin);	/* Toggle Green LED */
			App_Delay(100);
			i++;
 		}

 		if(pin==RED_LED_Pin)
 		{
 		LED_STAT[0] = 0;
 		}
 		else if(pin == GREEN_LED_Pin)
 		{
 		LED_STAT[1] = 0;
 		}
 		HAL_UART_Transmit(&huart1, "SEMAPHORE 2 Released\n\r", 22, 100);
 	 	tx_semaphore_put(&Semaphore1);
 	}


   }
}
/* USER CODE BEGIN 1 */
/**
  * @brief  Function implementing the ThreadFour thread.
  * @param  thread_input: Not used
  * @retval None
  */
void ThreadThree_Entry(ULONG thread_input)
{
  uint8_t t3_count=0;
  uint8_t status,pin,i;
 // uint8_t LED_STAT[2]= {0,0};
  while(1)									/* Infinite loop */
   {
 	//HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);	/* Toggle Green LED */
 	status = tx_semaphore_get(&Semaphore1, TX_WAIT_FOREVER);
 	if(TX_SUCCESS == status)
 	{
 	HAL_UART_Transmit(&huart1, "SEMAPHORE 3 Locked\n\r", 22, 100);
 		if(0==LED_STAT[0])
 		{
 			LED_STAT[0]=1;
 			pin = RED_LED_Pin;
 		}
 		else if(0==LED_STAT[1])
 		{
 			LED_STAT[1]=1;
 			pin = GREEN_LED_Pin;
 		}
 		i=0;

 		while(i<5)
 		{
 		HAL_GPIO_TogglePin(GPIOH, pin);	/* Toggle Green LED */
 		App_Delay(250);
 		i++;
 		}

 		if(pin==RED_LED_Pin)
 		{
 		LED_STAT[0] = 0;
 		}
 		else if(pin == GREEN_LED_Pin)
 		{
 		LED_STAT[1] = 0;
 		}
 	 	HAL_UART_Transmit(&huart1, "SEMAPHORE 3 Released\n\r", 22, 100);
 	 	tx_semaphore_put(&Semaphore1);
 	}

   }
}

/* USER CODE BEGIN 1 */
/**
  * @brief  Function implementing the ThreadOne thread.
  * @param  thread_input: Not used
  * @retval None
  */
void ThreadFour_Entry(ULONG thread_input)
{
  uint8_t t4_count=0;
  uint8_t status,pin,i;
 // uint8_t LED_STAT[2]= {0,0};
  while(1)									/* Infinite loop */
   {
 	//HAL_GPIO_TogglePin(RED_LED_GPIO_Port, RED_LED_Pin);	/* Toggle Green LED */
 	status = tx_semaphore_get(&Semaphore1, TX_WAIT_FOREVER);
 	if(TX_SUCCESS == status)
 	{
 	HAL_UART_Transmit(&huart1, "SEMAPHORE 4 Locked\n\r", 22, 100);
 		if(0==LED_STAT[0])
 		{
 			LED_STAT[0]=1;
 			pin = RED_LED_Pin;
 		}
 		else if(0==LED_STAT[1])
 		{
 			LED_STAT[1]=1;
 			pin = GREEN_LED_Pin;
 		}
 		i=0;

 		while(i<3)
 		{
 		HAL_GPIO_TogglePin(GPIOH, pin);	/* Toggle Green LED */
 		App_Delay(500);
 		i++;
 		}

 		if(pin==RED_LED_Pin)
 		{
 		LED_STAT[0] = 0;
 		}
 		else if(pin == GREEN_LED_Pin)
 		{
 		LED_STAT[1] = 0;
 		}
 	 	HAL_UART_Transmit(&huart1, "SEMAPHORE 4 Released\n\r", 22, 100);
 	 	tx_semaphore_put(&Semaphore1);
 	}

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
