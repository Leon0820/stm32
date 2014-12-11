/**
  ******************************************************************************
  * @file    Project/STM32F10x_Redbull_freertos/main.c 
  * @author  leon@sdulab
  * @version V0.0.1
  * @date    1-12-2014
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2014 SDUlab</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32_redbull.h"
#include "stm32_redbull_lcd.h"
#include <stdio.h>

#include "FreeRTOSConfig.h"
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

#define Background_Task_PRIO    ( tskIDLE_PRIORITY  + 10 )
#define Background_Task_STACK   ( 512 )
#define LED_Task_PRIO    ( tskIDLE_PRIORITY  + 10 )
#define LED_Task_STACK   ( 512 )

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
xTaskHandle                   Background_Task_Handle;
xTaskHandle                   LED_Task_Handle;

/* Private function prototypes -----------------------------------------------*/
static void Background_Task(void * pvParameters);
static void LED_Task(void * pvParameters);


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
	  /* Initilize the BSP layer */
  STM_REDBULL_LEDInit();
	STM3210E_LCD_Init();

  /* Display message on STM3210X-REDBULL LCD *************************************/
  /* Clear the LCD */ 
  LCD_Clear(LCD_COLOR_WHITE);

  /* Set the LCD Back Color */
  LCD_SetBackColor(LCD_COLOR_BLUE);
  /* Set the LCD Text Color */
  LCD_SetTextColor(LCD_COLOR_WHITE);
  
  
  /* Create background task */
  xTaskCreate(Background_Task,
              "BK_GND",
              Background_Task_STACK,
              NULL,
              Background_Task_PRIO,
              &Background_Task_Handle);
	  xTaskCreate(LED_Task,"LED1_Task",LED_Task_STACK,(void *)1,LED_Task_PRIO,&LED_Task_Handle);
		xTaskCreate(LED_Task,"LED2_Task",LED_Task_STACK,(void *)2,LED_Task_PRIO,&LED_Task_Handle);
    xTaskCreate(LED_Task,"LED2_Task",LED_Task_STACK,(void *)3,LED_Task_PRIO,&LED_Task_Handle);
		xTaskCreate(LED_Task,"LED2_Task",LED_Task_STACK,(void *)4,LED_Task_PRIO,&LED_Task_Handle);
  /* Start the FreeRTOS scheduler */
  vTaskStartScheduler();
  
}
/**
  * @brief  Background task
  * @param  pvParameters not used
  * @retval None
  */
static void Background_Task(void * pvParameters)
{
  static uint32_t ticks = 0;
	static uint32_t minutes = 0;
	static uint32_t hours = 0;
	char str[9]="00:00:00";
	portTickType xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
 
  /* Run the background task */
  while (1)
  {
		//STM_REDBULL_LEDToggle(LED1);
		vTaskDelayUntil( &xLastWakeTime, ( 1000 / portTICK_RATE_MS ) );
		ticks++;
		if(ticks==60){ticks=0;minutes++;}
		if(minutes==60){minutes=0;hours++;}
		sprintf(str,"%02d:%02d:%02d", hours, minutes, ticks);
		LCD_DisplayStringLine(LCD_LINE_0, (uint8_t *)str);
  }
}

static void LED_Task(void * pvParameters)
{
	int LedNum;
	portTickType xLastWakeTime;
  xLastWakeTime = xTaskGetTickCount();
  LedNum = (int)pvParameters;
  /* Run the background task */
  while (1)
  {
		STM_REDBULL_LEDToggle(LedNum);
		vTaskDelayUntil( &xLastWakeTime, ( 200 * LedNum / portTICK_RATE_MS ) );
  }
}

/**
  * @brief  Error callback function
  * @param  None
  * @retval None
  */
void vApplicationMallocFailedHook( void )
{
  while (1)
  {}
}


#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */


/******************* (C) COPYRIGHT 2014 SDUlab *****END OF FILE****/
