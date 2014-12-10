/**
  ******************************************************************************
  * @file    Project/STM32F10x_Redbull_Template/main.c 
  * @author  leon@sdulab
  * @version V0.0.1
  * @date    17-July-2014
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
#include <stdio.h>


/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/

  #define MESSAGE1   " STM32 High Density " 
  #define MESSAGE2   " Device running on  " 
  #define MESSAGE3   " STM3210E-RedBull   " 

/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
 
#define ITM_Port8(n)    (*((volatile unsigned char *)(0xE0000000+4*n)))
#define ITM_Port16(n)   (*((volatile unsigned short*)(0xE0000000+4*n)))
#define ITM_Port32(n)   (*((volatile unsigned long *)(0xE0000000+4*n)))

#define DEMCR           (*((volatile unsigned long *)(0xE000EDFC)))
#define TRCENA          0x01000000

//struct __FILE { int handle; /* Add whatever you need here */ };
//FILE __stdout;
//FILE __stdin;

/* Private function prototypes -----------------------------------------------*/
#ifdef __GNUC__
/* With GCC/RAISONANCE, small printf (option LD Linker->Libraries->Small printf
   set to 'Yes') calls __io_putchar() */
#define PUTCHAR_PROTOTYPE int __io_putchar(int ch)
#else
#define PUTCHAR_PROTOTYPE int fputc(int ch, FILE *f)
#endif /* __GNUC__ */

/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f10x_xx.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f10x.c file
     */     

  /* Initialize LEDs, Key Button, LCD and COM port(USART) available on
     STM3210X-REDBULL board ******************************************************/
  STM_REDBULL_LEDInit();


//  /* Initialize the LCD */
//  STM3210E_LCD_Init();


//  /* Display message on STM3210X-REDBULL LCD *************************************/
//  /* Clear the LCD */ 
//  LCD_Clear(LCD_COLOR_WHITE);

//  /* Set the LCD Back Color */
//  LCD_SetBackColor(LCD_COLOR_BLUE);
//  /* Set the LCD Text Color */
//  LCD_SetTextColor(LCD_COLOR_WHITE);
//  LCD_DisplayStringLine(LCD_LINE_0, (uint8_t *)MESSAGE1);
//  LCD_DisplayStringLine(LCD_LINE_1, (uint8_t *)MESSAGE2);
//  LCD_DisplayStringLine(LCD_LINE_2, (uint8_t *)MESSAGE3);

  /* Retarget the C library printf function to the USARTx, can be USART1 or USART2
     depending on the REDBULL board you are using ********************************/
  printf("\n\r %s", MESSAGE1);
  printf(" %s", MESSAGE2);
  printf(" %s\n\r", MESSAGE3);

  /* Turn on leds available on STM3210X-REDBULL **********************************/
  STM_REDBULL_LEDOn(LED1);
  STM_REDBULL_LEDOn(LED2);
  STM_REDBULL_LEDOn(LED3);
  STM_REDBULL_LEDOn(LED4);
	STM_REDBULL_LEDOn(LED5);

  /* Add your application code here
     */

  /* Infinite loop */
  while (1)
  {
  }
}

/**
  * @brief  Retargets the C library printf function to the USART.
  * @param  None
  * @retval None
  */
PUTCHAR_PROTOTYPE
{
  if (DEMCR & TRCENA) 
	{
    while (ITM_Port32(0) == 0);
    ITM_Port8(0) = ch;
   }
  return ch;

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
