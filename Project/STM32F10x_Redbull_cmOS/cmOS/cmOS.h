/*******************************************************************************
  * @file    cmOS.h
  * @author  南永涛
  * @version V1.0.0
  * @date    2014-12-22
  * @brief   与cmOS有关的宏定义，结构体，及函数声明。
  ******************************************************************************/
#ifndef _CMOS_H
#define _CMOS_H
#include <stdio.h>
#include <stdint.h>

#define TRUE 0x01
#define FALSE 0x00

#define MaxTaskNum        	255 //2^8-1
#define TaskNum             6 //用户自定义
#define MinTaskStkSize      20  //如何确定堆栈的大小
#define MaxPrioty						255//2^8-1,值越大优先级越小

#define MaxTimer            16
#define MaxLayMesg      		20  
#define HARD_TIMER_NULL 		7
#define HARD_TIMER_WORK 		6
/******************任务状态**********************/
#define RUNNING			  			00			//运行
#define READY			  				01			//就绪
#define WAIT		            02	    //等待资源就绪
#define TASKNULL						15			//空任务

#define MES_NULL 						0


typedef struct TaskControlBlock
{
	  uint32_t  * TaskSP;			//任务堆栈指针
    uint8_t   TaskId;   		//任务ID,是否可以和优先级合到一起
	  uint8_t   TaskStatus;		//任务状态
	  uint8_t   TaskPrioty;   //每个任务的优先级都不一样，不支持具有相同优先级的任务
}OS_TCB;
   
typedef struct SystemMessage                
{
	uint8_t TxMessageTaskId;
	uint8_t MessageContext;
}OS_MCB;

/*************************系统相关****************************/
extern uint32_t  DisInt(void);
extern void 	   EnInt(uint32_t cpu_sr); 

extern void OS_START(void);		
extern void OS_CONTEX_SWITCH(void);//任务上下文切换

void 				SetTimerTick(uint32_t Tick); 		//设置心跳定时器，tick为心跳周期
void 				emSysInit(void);
void 				StartTask(void);			//???????,?????????????
/*************************任务相关****************************/
void CreateTask(void (* TaskName)(), uint8_t Id, uint8_t Prio, uint8_t stat, uint32_t * TaskStk, uint32_t TaskStkSize, void * const Parameters);
void 			SchedTask(void); 
void 			CurrentTaskWait(void);		//g??????
void 			ChangeStatus(uint8_t id);			//?????
/*************************消息相关****************************/
unsigned char TxMessage(unsigned char RxMesgTaskId,unsigned char message);
unsigned char RxMessage(unsigned char message);
void emTxSysMesg(unsigned char message);
unsigned char emRxSysMesg(void);
void emDelSysMesg(void);
/*************************时间相关****************************/
//unsigned char emSetHardTimer(unsigned char tid, unsigned int value);
//unsigned char emStartHardTimer(unsigned char tid);
//unsigned char emCheckHardTimer(unsigned char tid);
//void emDelHardTimer(unsigned char tid);

/************************层消息，貌似是WSN中用的****************************/
//int 					emWaitMesg(unsigned char message,unsigned char state,unsigned char **ptr,unsigned char *size);
//unsigned char emTxMesg(unsigned char message,unsigned char state,unsigned char *ptr,unsigned char size);
//unsigned char emSearchMesg(unsigned char message);
//unsigned char emRxMesg(unsigned char Index,unsigned char state,unsigned char *ptr,unsigned char size);
//void 					emDelMesg(unsigned char message);	
#endif







