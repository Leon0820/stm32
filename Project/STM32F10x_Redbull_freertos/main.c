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

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
xTaskHandle                   Task_Handle;

/* Private function prototypes -----------------------------------------------*/
static void Background_Task(void * pvParameters);


/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_4);
  
  /* Create background task */
  xTaskCreate(Background_Task,
              (signed char const*)"BK_GND",
              Background_Task_STACK,
              NULL,
              Background_Task_PRIO,
              &Task_Handle);
  
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
  
  /* Initilize the BSP layer */
  STM_REDBULL_LEDInit();
  
 
  /* Run the background task */
  while (1)
  {
    if ( ticks++ > 1000000 )
    {
      ticks = 0;

      /* toggle LED1..4 each 100ms */
      STM_REDBULL_LEDToggle(LED1);
      STM_REDBULL_LEDToggle(LED2);
      STM_REDBULL_LEDToggle(LED3);
      STM_REDBULL_LEDToggle(LED4);
    }
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
