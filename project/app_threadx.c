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
#include <stdio.h>
#include <string.h>
#include "ism330dhcx.h"
#include "b_u585i_iot02a_bus.h"

#include "hts221.h"
//#include "custom_bus.h"
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
extern RTC_HandleTypeDef hrtc;
extern UART_HandleTypeDef huart1;
TX_THREAD ThreadOne;
TX_THREAD ThreadTwo;
TX_THREAD ThreadThree;
TX_THREAD ThreadFour;
TX_SEMAPHORE semaphoreOne;
TX_SEMAPHORE semaphoretwo;
TX_TIMER timerOne;

extern ISM330DHCX_Object_t pobj;

uint8_t          ISM330DHCX_Id;
//float            ISM330DHCX_Odr;
uint8_t          ISM330DHCX_Status;
//float            ISM330DHCX_ACCL_Value;
//float            ISM330DHCX_ACCL_Odr;
//float            ISM330DHCX_GYRO_Value;
//float            ISM330DHCX_GYRO_Odr;



extern HTS221_Object_t HTS221_Obj;
uint8_t          HTS221_Id;
float            HTS221_Odr;
uint8_t          HTS221_Status;
float            HTS221_HUM_Value;
float            HTS221_HUM_Odr;
float            HTS221_TEMP_Value;
float            HTS221_TEMP_Odr;



ISM330DHCX_Axes_t accl_val;
uint8_t tx_buf[100];
uint8_t len;





char time[30];
char date[30];
char convert[8];
uint8_t value_1;
uint8_t value_2;
uint8_t value_3;
uint8_t hr_buf[10], min_buf[10], sec_buf[10], dt_buf[11];

RTC_DateTypeDef sDate;
RTC_TimeTypeDef sTime;


char msg[50];
//uint8_t tf_buf[20];
uint8_t  rx_buf[10], str_buf[20];
uint8_t length;
/* USER CODE END PV */

/* Private function prototypes -----------------------------------------------*/
/* USER CODE BEGIN PFP */
void ThreadOne_Entry(ULONG thread_input);
void ThreadTwo_Entry(ULONG thread_input);
void ThreadThree_Entry(ULONG thread_input);
void ThreadFour_Entry(ULONG thread_input);


void App_Delay(uint32_t Delay);
void timerCB(ulong);
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
  CHAR *pointer1;
  CHAR *pointer2;
  CHAR *pointer3;
  CHAR *pointer4;


  if (tx_byte_allocate(byte_pool, (VOID **) &pointer1,
                       APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    ret = TX_POOL_ERROR;
  }

  if (tx_byte_allocate(byte_pool, (VOID **) &pointer2,
                       APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    ret = TX_POOL_ERROR;
  }

  if (tx_byte_allocate(byte_pool, (VOID **) &pointer3,
                       APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    ret = TX_POOL_ERROR;
  }

  if (tx_byte_allocate(byte_pool, (VOID **) &pointer4,
                       APP_STACK_SIZE, TX_NO_WAIT) != TX_SUCCESS)
  {
    ret = TX_POOL_ERROR;
  }


  if (tx_thread_create(&ThreadOne, "Thread One", ThreadOne_Entry, 0,
                       pointer1, APP_STACK_SIZE,
                       THREAD_ONE_PRIO, THREAD_ONE_PREEMPTION_THRESHOLD,
                       4, TX_AUTO_START) != TX_SUCCESS)
  {
    ret = TX_THREAD_ERROR;
  }

  if (tx_thread_create(&ThreadTwo, "Thread Two", ThreadTwo_Entry, 0,
                       pointer2, APP_STACK_SIZE,
                       THREAD_ONE_PRIO, THREAD_ONE_PREEMPTION_THRESHOLD,
                       1, TX_AUTO_START) != TX_SUCCESS)
  {
    ret = TX_THREAD_ERROR;
  }

  if (tx_thread_create(&ThreadThree, "Thread Three", ThreadThree_Entry, 0,
                       pointer3, APP_STACK_SIZE,
                       THREAD_ONE_PRIO, THREAD_ONE_PREEMPTION_THRESHOLD,
                       1, TX_AUTO_START) != TX_SUCCESS)
  {
    ret = TX_THREAD_ERROR;
  }

  if (tx_thread_create(&ThreadFour, "Thread Four", ThreadFour_Entry, 0,
                       pointer4, APP_STACK_SIZE,
                       THREAD_ONE_PRIO, THREAD_ONE_PREEMPTION_THRESHOLD,
                       1, TX_AUTO_START) != TX_SUCCESS)
  {
    ret = TX_THREAD_ERROR;
  }

  if(tx_timer_create(&timerOne,"timer one",timerCB,1,100,100,TX_AUTO_ACTIVATE))
  {
	  ret = TX_THREAD_ERROR;
  }
  /* USER CODE END App_ThreadX_Init */

  tx_semaphore_create(&semaphoreOne, "semaphoreOne", 1);
  tx_semaphore_create(&semaphoretwo, "semaphoretwo", 1);

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


void timerCB(ulong var)
{

	HAL_UART_Transmit(&huart1, "\n\r !!!!!!!!!!! timer expired !!!!!!!!\n\r", 43, 100);
}


void ThreadOne_Entry(ULONG thread_input)
{
	UINT status;
	while(1)
	{
		status = tx_semaphore_get(&semaphoreOne, TX_WAIT_FOREVER);
		if(TX_SUCCESS == status)
		{
	    if(ISM330DHCX_ACC_GetAxes(&pobj, &accl_val) != ISM330DHCX_OK)
	    {
	      __BKPT(0);
	    }
	    len = sprintf(tx_buf,"acc_data: x = %d\ty = %d\tz = %d\n\r",accl_val.x,accl_val.y,accl_val.z);
	    HAL_UART_Transmit(&huart1, tx_buf, len, 1000);

	    if(ISM330DHCX_GYRO_GetAxes(&pobj, &accl_val) != ISM330DHCX_OK)
	    {
	      __BKPT(0);
	    }
	    len = sprintf(tx_buf,"gyro_data: x = %d\ty = %d\tz = %d\n\r",accl_val.x,accl_val.y,accl_val.z);
	    HAL_UART_Transmit(&huart1, tx_buf, len, 1000);
		//HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);


		HTS221_TEMP_GetTemperature(&HTS221_Obj, &HTS221_TEMP_Value);
	    len = sprintf(tx_buf,"temp:%f \n\r",HTS221_TEMP_Value);
	    HAL_UART_Transmit(&huart1, tx_buf, len, 100);
		App_Delay(100);
		}
	}


}

void ThreadTwo_Entry(ULONG thread_input)
{
	UINT status;
	while(1)
	{
		status = tx_semaphore_get(&semaphoretwo, TX_WAIT_FOREVER);
		    if(TX_SUCCESS == status)
			{
		HAL_RTC_GetTime(&hrtc, &sTime, RTC_FORMAT_BIN);
		HAL_RTC_GetDate(&hrtc, &sDate, RTC_FORMAT_BIN);

		sprintf(time,"Time: %02d.%02d.%02d\t",sTime.Hours,sTime.Minutes,sTime.Seconds);
		sprintf(date,"Date: %02d.%02d.%02d\r\n",sDate.Date,sDate.Month,sDate.Year);

			  //	HAL_UART_Transmit(&huart1, (uint8_t *)date, sizeof(date), 300);
		HAL_UART_Transmit(&huart1, (uint8_t *)time, sizeof(time), 300);
		HAL_UART_Transmit(&huart1, (uint8_t *)"\n\r", 3, 300);
		//HAL_GPIO_TogglePin(LED_RED_GPIO_Port, LED_RED_Pin);
		App_Delay(100);
			}
	}

}


void ThreadThree_Entry(ULONG thread_input)
{
	while(1)
	{
		//HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		App_Delay(50);
	}


}


void ThreadFour_Entry(ULONG thread_input)
{
	while(1)
	{
		//HAL_GPIO_TogglePin(LED_GREEN_GPIO_Port, LED_GREEN_Pin);
		App_Delay(50);
	}


}

void App_Delay(uint32_t Delay)
{
  UINT initial_time = tx_time_get();
  while ((tx_time_get() - initial_time) < Delay);
}
/* USER CODE END 1 */
