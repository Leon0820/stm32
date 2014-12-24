/*******************************************************************************
  * @file    cmOS.h
  * @author  ������
  * @version V1.0.0
  * @date    2014-12-22
  * @brief   ��cmOS�йصĺ궨�壬�ṹ�壬������������
  ******************************************************************************/
#ifndef _CMOS_H
#define _CMOS_H
#include <stdio.h>
#include <stdint.h>

#define TRUE 0x01
#define FALSE 0x00

#define MaxTaskNum        	255 //2^8-1
#define TaskNum             6 //�û��Զ���
#define MinTaskStkSize      20  //���ȷ����ջ�Ĵ�С
#define MaxPrioty						255//2^8-1,ֵԽ�����ȼ�ԽС

#define MaxTimer            16
#define MaxLayMesg      		20  
#define HARD_TIMER_NULL 		7
#define HARD_TIMER_WORK 		6
/******************����״̬**********************/
#define RUNNING			  			00			//����
#define READY			  				01			//����
#define WAIT		            02	    //�ȴ���Դ����
#define TASKNULL						15			//������

#define MES_NULL 						0


typedef struct TaskControlBlock
{
	  uint32_t  * TaskSP;			//�����ջָ��
    uint8_t   TaskId;   		//����ID,�Ƿ���Ժ����ȼ��ϵ�һ��
	  uint8_t   TaskStatus;		//����״̬
	  uint8_t   TaskPrioty;   //ÿ����������ȼ�����һ������֧�־�����ͬ���ȼ�������
}OS_TCB;
   
typedef struct SystemMessage                
{
	uint8_t TxMessageTaskId;
	uint8_t MessageContext;
}OS_MCB;

/*************************ϵͳ���****************************/
extern uint32_t  DisInt(void);
extern void 	   EnInt(uint32_t cpu_sr); 

extern void OS_START(void);		
extern void OS_CONTEX_SWITCH(void);//�����������л�

void 				SetTimerTick(uint32_t Tick); 		//����������ʱ����tickΪ��������
void 				emSysInit(void);
void 				StartTask(void);			//???????,?????????????
/*************************�������****************************/
void CreateTask(void (* TaskName)(), uint8_t Id, uint8_t Prio, uint8_t stat, uint32_t * TaskStk, uint32_t TaskStkSize, void * const Parameters);
void 			SchedTask(void); 
void 			CurrentTaskWait(void);		//g??????
void 			ChangeStatus(uint8_t id);			//?????
/*************************��Ϣ���****************************/
unsigned char TxMessage(unsigned char RxMesgTaskId,unsigned char message);
unsigned char RxMessage(unsigned char message);
void emTxSysMesg(unsigned char message);
unsigned char emRxSysMesg(void);
void emDelSysMesg(void);
/*************************ʱ�����****************************/
//unsigned char emSetHardTimer(unsigned char tid, unsigned int value);
//unsigned char emStartHardTimer(unsigned char tid);
//unsigned char emCheckHardTimer(unsigned char tid);
//void emDelHardTimer(unsigned char tid);

/************************����Ϣ��ò����WSN���õ�****************************/
//int 					emWaitMesg(unsigned char message,unsigned char state,unsigned char **ptr,unsigned char *size);
//unsigned char emTxMesg(unsigned char message,unsigned char state,unsigned char *ptr,unsigned char size);
//unsigned char emSearchMesg(unsigned char message);
//unsigned char emRxMesg(unsigned char Index,unsigned char state,unsigned char *ptr,unsigned char size);
//void 					emDelMesg(unsigned char message);	
#endif







