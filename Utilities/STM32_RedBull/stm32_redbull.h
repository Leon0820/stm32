/**
  ******************************************************************************
  * @file    stm32_redbull.h
  * @author  leon@sdulab
  * @version V0.0.1
  * @date    17-July-2014
  * @brief   Header file for stm32_REDBULL.c module.
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
  
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM32_REDBULL_H
#define __STM32_REDBULL_H

#ifdef __cplusplus
 extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/

/** @addtogroup Utilities
  * @{
  */ 
  
/** @addtogroup STM32_REDBULL
  * @{
  */ 

/** @defgroup STM32_REDBULL_Abstraction_Layer
  * @{
  */
  
/** @defgroup STM32_REDBULL_HARDWARE_RESOURCES
  * @{
  */

/**
@code  
 The table below gives an overview of the hardware resources supported by STM32 REDBULL board.
●  CPU：STM32F103ZET6，片上集成512K flash、64KRAM、
			5 × USARTs
			4 × 16-bit timers, 2 × basic timers
			3 × SPIs, 2 × I2Ss, 2 × I2Cs
			USB, CAN, 2 × PWM timers
			3 × ADCs, 1 × DAC, 1 × SDIO
			FSMC
●  板上外扩512K SRAM, FSMC
●  板上外扩2M NOR FLASH，  FSMC
●  板上外扩128M NAND FLASH， FSMC
●  TFT真彩触摸屏模块，FSMC控制，配置触摸控制器芯片XPT2046
●  一路CAN通信接口,驱动器芯片SN65VHD230 
●  两路RS232接口 
●  一路RS485通信接口 
●  一个SD卡座SDIO控制方式  
●  一个I2C存储器接口，标配24LC02(EEPROM)  
●  一个SPI存储器接口，标配AT45DB161D(DATA FLASH) 
●  一路ADC调节电位器输入 
●  三路ADC输入接线端子引出 
●  两路PWM输出接线端子引出 
●  两路DAC输出接线端子引出  
●  一个蜂鸣器、五个用户LED灯、一个电源指示灯，一个USB通信指示灯，
●  四个用户按键，一个系统复位按键
@endcode
*/

/**
  * @}
  */
  
/** @defgroup STM32_REDBULL_Exported_Types
  * @{
  */
typedef enum 
{
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  LED4 = 3,
	LED5 = 4
} Led_TypeDef;

typedef enum 
{  
  BUTTON_WAKEUP = 0,
  BUTTON_TAMPER = 1,
  BUTTON_USER1 = 2,
  BUTTON_USER2 = 3,
} Button_TypeDef;

typedef enum 
{  
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;


typedef enum 
{
  COM1 = 0,
  COM2 = 1
} COM_TypeDef;   
/**
  * @}
  */ 
  
/** @defgroup STM32_REDBULL_Exported_Constants
  * @{
  */
	
/** 
  * @brief  Uncomment the line corresponding to the STMicroelectronics REDBULLuation
  *   board used in your application.
  *   
  *  Tip: To avoid modifying this file each time you need to switch between these
  *       boards, you can define the board in your toolchain compiler preprocessor.    
  */ 
#if !defined (USE_STM32_REDBULL) 
 #define USE_STM32_REDBULL
#endif

#ifdef USE_STM32_REDBULL
 #include "stm32f10x.h"
 #include "stm32_REDBULL.h"
#else 
 #error "Please select first the STM32 REDBULL board to be used (in stm32_REDBULL.h)"
#endif                      

/** @addtogroup STM3210E_EVAL_LOW_LEVEL_LED
  * @{
  */
#define LEDn                             5

#define LED1_PIN                         GPIO_Pin_6
#define LED1_GPIO_PORT                   GPIOF
#define LED1_GPIO_CLK                    RCC_APB2Periph_GPIOF  
  
#define LED2_PIN                         GPIO_Pin_7
#define LED2_GPIO_PORT                   GPIOF
#define LED2_GPIO_CLK                    RCC_APB2Periph_GPIOF  

#define LED3_PIN                         GPIO_Pin_8  
#define LED3_GPIO_PORT                   GPIOF
#define LED3_GPIO_CLK                    RCC_APB2Periph_GPIOF  

#define LED4_PIN                         GPIO_Pin_9
#define LED4_GPIO_PORT                   GPIOF
#define LED4_GPIO_CLK                    RCC_APB2Periph_GPIOF

#define LED5_PIN                         GPIO_Pin_10
#define LED5_GPIO_PORT                   GPIOF
#define LED5_GPIO_CLK                    RCC_APB2Periph_GPIOF
/**
  * @}
  */

/** @addtogroup STM3210E_EVAL_LOW_LEVEL_BUTTON
  * @{
  */  
#define BUTTONn                          4

/**
 * @brief Wakeup push-button
 */
#define WAKEUP_BUTTON_PIN                GPIO_Pin_0
#define WAKEUP_BUTTON_GPIO_PORT          GPIOA
#define WAKEUP_BUTTON_GPIO_CLK           RCC_APB2Periph_GPIOA
#define WAKEUP_BUTTON_EXTI_LINE          EXTI_Line0
#define WAKEUP_BUTTON_EXTI_PORT_SOURCE   GPIO_PortSourceGPIOA
#define WAKEUP_BUTTON_EXTI_PIN_SOURCE    GPIO_PinSource0
#define WAKEUP_BUTTON_EXTI_IRQn          EXTI0_IRQn 
/**
 * @brief Tamper push-button
 */
#define TAMPER_BUTTON_PIN                GPIO_Pin_13
#define TAMPER_BUTTON_GPIO_PORT          GPIOC
#define TAMPER_BUTTON_GPIO_CLK           RCC_APB2Periph_GPIOC
#define TAMPER_BUTTON_EXTI_LINE          EXTI_Line13
#define TAMPER_BUTTON_EXTI_PORT_SOURCE   GPIO_PortSourceGPIOC
#define TAMPER_BUTTON_EXTI_PIN_SOURCE    GPIO_PinSource13
#define TAMPER_BUTTON_EXTI_IRQn          EXTI15_10_IRQn 
/**
 * @brief User1 push-button
 */
#define USR1_BUTTON_PIN                   GPIO_Pin_8
#define USR1_BUTTON_GPIO_PORT             GPIOA
#define USR1_BUTTON_GPIO_CLK              RCC_APB2Periph_GPIOA
#define USR1_BUTTON_EXTI_LINE             EXTI_Line8
#define USR1_BUTTON_EXTI_PORT_SOURCE      GPIO_PortSourceGPIOA
#define USR1_BUTTON_EXTI_PIN_SOURCE       GPIO_PinSource8
#define USR1_BUTTON_EXTI_IRQn             EXTI9_5_IRQn

/**
 * @brief Usr2 push-button
 */
#define USR2_BUTTON_PIN                   GPIO_Pin_3
#define USR2_BUTTON_GPIO_PORT             GPIOD
#define USR2_BUTTON_GPIO_CLK              RCC_APB2Periph_GPIOD
#define USR2_BUTTON_EXTI_LINE             EXTI_Line3
#define USR2_BUTTON_EXTI_PORT_SOURCE      GPIO_PortSourceGPIOG
#define USR2_BUTTON_EXTI_PIN_SOURCE       GPIO_PinSource8
#define USR2_BUTTON_EXTI_IRQn             EXTI9_5_IRQn
     
/**
  * @}
  */ 
	
/** @addtogroup STM32100E_REDBULL_LOW_LEVEL_COM
  * @{
  */
#define COMn                             2

/**
 * @brief Definition for COM port1, connected to USART1
 */ 
#define REDBULL_COM1                        USART1
#define REDBULL_COM1_CLK                    RCC_APB2Periph_USART1
#define REDBULL_COM1_TX_PIN                 GPIO_Pin_9
#define REDBULL_COM1_TX_GPIO_PORT           GPIOA
#define REDBULL_COM1_TX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define REDBULL_COM1_RX_PIN                 GPIO_Pin_10
#define REDBULL_COM1_RX_GPIO_PORT           GPIOA
#define REDBULL_COM1_RX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define REDBULL_COM1_IRQn                   USART1_IRQn

/**
 * @brief Definition for COM port2, connected to USART2
 */ 
#define REDBULL_COM2                        USART2
#define REDBULL_COM2_CLK                    RCC_APB1Periph_USART2
#define REDBULL_COM2_TX_PIN                 GPIO_Pin_2
#define REDBULL_COM2_TX_GPIO_PORT           GPIOA
#define REDBULL_COM2_TX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define REDBULL_COM2_RX_PIN                 GPIO_Pin_3
#define REDBULL_COM2_RX_GPIO_PORT           GPIOA
#define REDBULL_COM2_RX_GPIO_CLK            RCC_APB2Periph_GPIOA
#define REDBULL_COM2_IRQn                   USART2_IRQn

/**
  * @}
  */ 
	
/** @addtogroup STM32100E_REDBULL_LOW_LEVEL_LCD
  * @{
  */
#define LCD_RSNWR_GPIO_CLK  LCD_NWR_GPIO_CLK
#define LCD_SPI_GPIO_PORT   LCD_SPI_SCK_GPIO_PORT
#define LCD_SPI_GPIO_CLK    LCD_SPI_SCK_GPIO_CLK
#define R0                  LCD_REG_0
#define R1                  LCD_REG_1
#define R2                  LCD_REG_2
#define R3                  LCD_REG_3
#define R4                  LCD_REG_4
#define R5                  LCD_REG_5
#define R6                  LCD_REG_6
#define R7                  LCD_REG_7
#define R8                  LCD_REG_8
#define R9                  LCD_REG_9
#define R10                 LCD_REG_10
#define R12                 LCD_REG_12
#define R13                 LCD_REG_13
#define R14                 LCD_REG_14
#define R15                 LCD_REG_15
#define R16                 LCD_REG_16
#define R17                 LCD_REG_17
#define R18                 LCD_REG_18
#define R19                 LCD_REG_19
#define R20                 LCD_REG_20
#define R21                 LCD_REG_21
#define R22                 LCD_REG_22
#define R23                 LCD_REG_23
#define R24                 LCD_REG_24
#define R25                 LCD_REG_25
#define R26                 LCD_REG_26
#define R27                 LCD_REG_27
#define R28                 LCD_REG_28
#define R29                 LCD_REG_29
#define R30                 LCD_REG_30
#define R31                 LCD_REG_31
#define R32                 LCD_REG_32
#define R33                 LCD_REG_33
#define R34                 LCD_REG_34
#define R36                 LCD_REG_36
#define R37                 LCD_REG_37
#define R40                 LCD_REG_40
#define R41                 LCD_REG_41
#define R43                 LCD_REG_43
#define R45                 LCD_REG_45
#define R48                 LCD_REG_48
#define R49                 LCD_REG_49
#define R50                 LCD_REG_50
#define R51                 LCD_REG_51
#define R52                 LCD_REG_52
#define R53                 LCD_REG_53
#define R54                 LCD_REG_54
#define R55                 LCD_REG_55
#define R56                 LCD_REG_56
#define R57                 LCD_REG_57
#define R59                 LCD_REG_59
#define R60                 LCD_REG_60
#define R61                 LCD_REG_61
#define R62                 LCD_REG_62
#define R63                 LCD_REG_63
#define R64                 LCD_REG_64
#define R65                 LCD_REG_65
#define R66                 LCD_REG_66
#define R67                 LCD_REG_67
#define R68                 LCD_REG_68
#define R69                 LCD_REG_69
#define R70                 LCD_REG_70
#define R71                 LCD_REG_71
#define R72                 LCD_REG_72
#define R73                 LCD_REG_73
#define R74                 LCD_REG_74
#define R75                 LCD_REG_75
#define R76                 LCD_REG_76
#define R77                 LCD_REG_77
#define R78                 LCD_REG_78
#define R79                 LCD_REG_79
#define R80                 LCD_REG_80
#define R81                 LCD_REG_81
#define R82                 LCD_REG_82
#define R83                 LCD_REG_83
#define R96                 LCD_REG_96
#define R97                 LCD_REG_97
#define R106                LCD_REG_106
#define R118                LCD_REG_118
#define R128                LCD_REG_128
#define R129                LCD_REG_129
#define R130                LCD_REG_130
#define R131                LCD_REG_131
#define R132                LCD_REG_132
#define R133                LCD_REG_133
#define R134                LCD_REG_134
#define R135                LCD_REG_135
#define R136                LCD_REG_136
#define R137                LCD_REG_137
#define R139                LCD_REG_139
#define R140                LCD_REG_140
#define R141                LCD_REG_141
#define R143                LCD_REG_143
#define R144                LCD_REG_144
#define R145                LCD_REG_145
#define R146                LCD_REG_146
#define R147                LCD_REG_147
#define R148                LCD_REG_148
#define R149                LCD_REG_149
#define R150                LCD_REG_150
#define R151                LCD_REG_151
#define R152                LCD_REG_152
#define R153                LCD_REG_153
#define R154                LCD_REG_154
#define R157                LCD_REG_157
#define R192                LCD_REG_192
#define R193                LCD_REG_193
#define R227                LCD_REG_227
#define R229                LCD_REG_229
#define R231                LCD_REG_231
#define R239                LCD_REG_239
#define White               LCD_COLOR_WHITE
#define Black               LCD_COLOR_BLACK
#define Grey                LCD_COLOR_GREY
#define Blue                LCD_COLOR_BLUE
#define Blue2               LCD_COLOR_BLUE2
#define Red                 LCD_COLOR_RED
#define Magenta             LCD_COLOR_MAGENTA
#define Green               LCD_COLOR_GREEN
#define Cyan                LCD_COLOR_CYAN
#define Yellow              LCD_COLOR_YELLOW
#define Line0               LCD_LINE_0
#define Line1               LCD_LINE_1
#define Line2               LCD_LINE_2
#define Line3               LCD_LINE_3
#define Line4               LCD_LINE_4
#define Line5               LCD_LINE_5
#define Line6               LCD_LINE_6
#define Line7               LCD_LINE_7
#define Line8               LCD_LINE_8
#define Line9               LCD_LINE_9
#define Horizontal          LCD_DIR_HORIZONTAL
#define Vertical            LCD_DIR_VERTICAL

/**
  * @}
  */ 

	
/** @addtogroup STM3210E_EVAL_LOW_LEVEL_SD_FLASH
  * @{
  */
/**
  * @brief  SD FLASH SDIO Interface
  */ 

#define SD_DETECT_PIN                    GPIO_Pin_11                 /* PF.11 */
#define SD_DETECT_GPIO_PORT              GPIOF                       /* GPIOF */
#define SD_DETECT_GPIO_CLK               RCC_APB2Periph_GPIOF

#define SDIO_FIFO_ADDRESS                ((uint32_t)0x40018080)
/** 
  * @brief  SDIO Intialization Frequency (400KHz max)
  */
#define SDIO_INIT_CLK_DIV                ((uint8_t)0xB2)
/** 
  * @brief  SDIO Data Transfer Frequency (25MHz max) 
  */
#define SDIO_TRANSFER_CLK_DIV            ((uint8_t)0x00) 

/**
  * @}
  */ 


	
/** @defgroup STM3210E_REDBULL_LOW_LEVEL_Private_Functions
  * @{
  */ 
void STM_REDBULL_LEDInit(void);
void STM_REDBULL_LEDOn(Led_TypeDef Led);
void STM_REDBULL_LEDOff(Led_TypeDef Led);
void STM_REDBULL_LEDToggle(Led_TypeDef Led);

void STM_REDBULL_COMInit(COM_TypeDef COM, USART_InitTypeDef* USART_InitStruct);

/**
  * @}
  */ 

#ifdef __cplusplus
}
#endif


#endif /* __STM32_REDBULL_H */

/**
  * @}
  */ 

/**
  * @}
  */ 

/**
  * @}
  */   
	
/**
  * @}
  */  

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
