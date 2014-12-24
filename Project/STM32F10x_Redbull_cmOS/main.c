
/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include "stm32_redbull.h"
#include "stm32_redbull_lcd.h"
#include "cmOS.h"
#include <stdio.h>


static uint32_t LEDTaskStk[5][20];


/* Private functions ---------------------------------------------------------*/
static void Delay(vu32 nCount)
{
  vu32 index = 0; 
  for(index = (100000 * nCount); index != 0; index--)
  {
  }
}

void LedTask(void * Parameters)
{
	int LedNum;
	LedNum = (int)Parameters;
	while(1)
	{
		STM_REDBULL_LEDToggle(LedNum);
		Delay(100);
		if(LedNum < 4)
			ChangeStatus(LedNum+2);
		else 
			ChangeStatus(1);
		CurrentTaskWait();
		SchedTask();
	}
}

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  STM_REDBULL_LEDInit();

	emSysInit();
	
	CreateTask(LedTask, 1, 3, READY,LEDTaskStk[0],20,(void *)0);
  CreateTask(LedTask, 2, 4, READY,LEDTaskStk[1],20,(void *)1);
  CreateTask(LedTask, 3, 5, READY,LEDTaskStk[2],20,(void *)2);
  CreateTask(LedTask, 4, 6, READY,LEDTaskStk[3],20,(void *)3);
	CreateTask(LedTask, 5, 7, READY,LEDTaskStk[4],20,(void *)4);
	
	StartTask();
  /* Infinite loop */
  while (1)
  {
  }
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
