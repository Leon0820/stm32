
#include "cmOS.h"

OS_TCB pTCB[TaskNum];
//OS_MCB pMCB[TaskNum];


OS_TCB  	*OSTCBCur;	 //当前运行任务的任务控制块
OS_TCB  	*OSTCBHighRdy;//就绪任务中优先级最高的任务控制块
uint8_t   OSPrioCur;		//当前运行任务的优先级
uint8_t   OSPrioHighRdy;//就绪任务中优先级最高的任务的优先级

//uint32_t  mSeconds;



void emSysInit(void)
{						
  int j;
  for(j=0;j<TaskNum;j++)
	{
		pTCB[j].TaskStatus=TASKNULL; //先将所有任务设为空，以备后面应用
    pTCB[j].TaskPrioty=MaxPrioty;		 
	}
}

void CreateTask(void (* TaskName)(), uint8_t Id, uint8_t Prio, uint8_t stat, uint32_t * TaskStk, uint32_t TaskStkSize, void * const Parameters)
{
	uint32_t * stk;
	stk  =  TaskStk + TaskStkSize;

	/*  模拟成异常，自动把寄存器压栈*/
	  *(stk)    = (uint32_t)0x01000000L;           /* xPSR                                                   */
    *(--stk)  = (uint32_t)TaskName;              /* Entry Point                                            */
    *(--stk)  = (uint32_t)0xFFFFFFFEL;           /* R14 (LR) (init value will cause fault if ever used)    */
    *(--stk)  = (uint32_t)0x12121212L;           /* R12                                                    */
    *(--stk)  = (uint32_t)0x03030303L;           /* R3                                                     */
    *(--stk)  = (uint32_t)0x02020202L;           /* R2                                                     */
    *(--stk)  = (uint32_t)0x01010101L;           /* R1                                                     */
    *(--stk)  = (uint32_t)Parameters;           /* R0 : argument                                          */
		/*R13堆栈指针在哪？？？？*/
                                                 /* Remaining registers saved on process stack             */
    *(--stk)  = (uint32_t)0x11111111L;           /* R11                                                    */
    *(--stk)  = (uint32_t)0x10101010L;           /* R10                                                    */
    *(--stk)  = (uint32_t)0x09090909L;           /* R9                                                     */
    *(--stk)  = (uint32_t)0x08080808L;           /* R8                                                     */
    *(--stk)  = (uint32_t)0x07070707L;           /* R7                                                     */
    *(--stk)  = (uint32_t)0x06060606L;           /* R6                                                     */
    *(--stk)  = (uint32_t)0x05050505L;           /* R5                                                     */
    *(--stk)  = (uint32_t)0x04040404L;           /* R4                                                     */
		
	pTCB[Id].TaskSP     = stk;
	pTCB[Id].TaskId     = Id;
	pTCB[Id].TaskStatus = stat;
	pTCB[Id].TaskPrioty = Prio;
}

void StartTask(void)
{                       
	uint8_t i = 0;
	uint8_t MaxPrioTaskId = 0;     
	uint8_t MaxPrio = MaxPrioty;   
   
  for(i=0; i<TaskNum; i++)
	 {
		if( (pTCB[i].TaskStatus == READY )&& (pTCB[i].TaskPrioty < MaxPrio ))
		 {
			MaxPrio = pTCB[i].TaskPrioty;
			MaxPrioTaskId = i;
		 }
	 }
	
	OSPrioHighRdy = MaxPrio;	  
  OSPrioCur = OSPrioHighRdy;
	OSTCBHighRdy = &pTCB[MaxPrioTaskId];
  OSTCBCur = OSTCBHighRdy;  
	OS_START();  
}

void SchedTask(void) //??????
{
	uint8_t i = 0;
	uint8_t MaxPrioTaskId = 0;      // 这里可以把这两个临时变量去掉 直接用CurrentId来进入循环判断
	uint8_t MaxPrio = MaxPrioty;               //优先级越高 值越小
   
  for(i=0; i<TaskNum; i++)
	 {
		if( (pTCB[i].TaskStatus == READY )&& (pTCB[i].TaskPrioty < MaxPrio ))
		 {
			MaxPrio = pTCB[i].TaskPrioty;
			MaxPrioTaskId = i;
		 }
	 }
	if(OSPrioCur == MaxPrioTaskId)		   //如果当前任务在时间片来临时，仍然是最高优先级任务则继续
		 {
				return;//返回值被放到r0
		 }
	else
		{  
	    OSPrioHighRdy=MaxPrio;	       //这里需要注意，有两种情况：1如果当时间片来临时当前任务非最高优先级2所有任务进入了wait状态（这时会默认去跑0任务。但是却不会修改优先级）
			OSTCBHighRdy=&pTCB[MaxPrioTaskId];
      OS_CONTEX_SWITCH();
	  }
}


void ChangeStatus(uint8_t TaskId)//测试用函数 用完删除
{
   pTCB[TaskId].TaskStatus =READY; 
}

void CurrentTaskWait()
{
	pTCB[OSTCBCur->TaskId].TaskStatus = WAIT;
}

/*************************消息相关**********************************************/
//uint8_t TxMessage(uint8_t RxMesgTaskId,uint8_t message)
//{    
//     if(pMCB[RxMesgTaskId].MessageContext!=MES_NULL)
//         return 0;
//	 //pMcb[RxMesgTaskId].TxMessageTaskId = CurrentTaskId;
//	 pMCB[RxMesgTaskId].MessageContext = message;
//	 pTCB[RxMesgTaskId].TaskStatus = READY;
//	    return  1;
//}
//uint8_t RxMessage(uint8_t message)
//{
//	if(message == pMCB[OSTCBCur->TaskId].MessageContext)
//     {
//	    pMCB[OSTCBCur->TaskId].MessageContext=MES_NULL;
//        return 1;  
//     }
//	 else
//	 	 return 0;
//}

//void emTxSysMesg(uint8_t message)
//{
//	uint8_t i;
//	uint32_t cpu_sr;
//	cpu_sr = DisInt();
//	pMCB[15].MessageContext=message;
//	for(i=0;i<15;i++)//????????READY,??????????????,???RTOS?????15
//	{
//		if((pTCB[i].TaskStatus>1)&&(pTCB[i].TaskStatus<15))
//			pTCB[i].TaskStatus=READY;
//	}
//	EnInt(cpu_sr);
//}

//uint8_t emRxSysMesg(void)//??????????
//{
//	uint8_t i;
//	if(pMCB[15].MessageContext==MES_NULL)
//		return 0;
//	i=pMCB[15].MessageContext;
//	  return i;
//}
//void emDelSysMesg(void)
//{
//    if(pMCB[15].MessageContext != MES_NULL)
//      pMCB[15].MessageContext=MES_NULL;
//}
/*************************时间相关**********************************************/

//void SetTimerTick(unsigned int Tick)//Timer1?????
//{

//}
//uint8_t emSetHardTimer(uint8_t tid, unsigned int value)//?????
//{
//	pHt[tid].htstatus.IDtimer.Flg=HARD_TIMER_NULL;
//	pHt[tid].Lt_value=value;
//	return 1;
//}

//uint8_t emStartHardTimer(uint8_t tid)
//{
//	if(pHt[tid].htstatus.IDtimer.Flg!=HARD_TIMER_NULL)
//		return 0;
//	pHt[tid].htstatus.IDtimer.Flg=HARD_TIMER_WORK;
//	pHt[tid].temp=mSeconds;
//	return 1;
//}

//uint8_t emCheckHardTimer(uint8_t tid)
//{
//	unsigned long tv,ttv;

//    if(pHt[tid].htstatus.IDtimer.Flg!=HARD_TIMER_WORK)
//       return 0;
//	tv=pHt[tid].Lt_value;
//	if(mSeconds<pHt[tid].temp)//mSecond overflow
//	{
//		ttv=4294967295-pHt[tid].temp+mSeconds;	//4294967296
//		if(ttv<tv)//?????????,??0
//			return 0;
//		if(ttv>tv)
//		{
//			pHt[tid].temp=mSeconds;
//			return 5;//pHt[tid].htstatus.IDtimer.Flg=5;
//		}
//		else 
//		{		
//			pHt[tid].temp=mSeconds;
//			return 1;
//		}
//	}
//	else
//	{
//		ttv=mSeconds-pHt[tid].temp;
//		if(ttv>tv)
//		{
//			pHt[tid].temp=mSeconds;
//			return 5;
//		}
//		 if(ttv<tv)
//			return 0;
//		 else 
//		{
//			pHt[tid].temp=mSeconds;
//			return 1;
//		}
//	}

//}

//void emDelHardTimer(uint8_t tid)
//{
//	pHt[tid].htstatus.IDtimer.Flg=HARD_TIMER_NULL;
//}
