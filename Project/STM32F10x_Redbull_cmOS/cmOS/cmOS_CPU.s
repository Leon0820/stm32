;********************************************************************************************************
;  * @file    cmOS.s
;  * @author  南永涛
;  * @version V1.0.0
;  * @date    2014-12-22
;  * @brief   与cmOS有关的底层操作，开关中断，上下文切换
;********************************************************************************************************

;********************************************************************************************************
;                                           PUBLIC FUNCTIONS
;********************************************************************************************************

    EXTERN  OSPrioCur					;当前任务的堆栈指针
    EXTERN  OSPrioHighRdy				;下个将要运行任务的堆栈指针
    EXTERN  OSTCBCur					
    EXTERN  OSTCBHighRdy

    EXPORT  DisInt                               ;Functions declared in this file
    EXPORT  EnInt

	EXPORT  OS_CONTEX_SWITCH;上下文切换
    EXPORT  OS_START;开始多任务调度

	EXPORT  PendSV_Handler;需要声明，否则会进入系统默认接口
;********************************************************************************************************
;                                                EQUATES
;********************************************************************************************************
NVIC_INT_CTRL   	EQU     0xE000ED04  ; 中断控制寄存器
NVIC_SYSPRI2    	EQU     0xE000ED20  ; 系统优先级寄存器2
NVIC_PENDSV_PRI 	EQU     0xFFFF0000   ; 软件中断和系统节拍中断
NVIC_PENDSVSET  	EQU     0x10000000  ; 触发软件中断的值
;********************************************************************************************************
;                                      CODE GENERATION DIRECTIVES
;********************************************************************************************************

    AREA |.text|, CODE, READONLY, ALIGN=2
    THUMB
    REQUIRE8
    PRESERVE8

;*********************************************************************************************************
;函数名：uint32_t DisInt(void);
;		 void 	   EnInt(uint32_t cpu_sr); 
;说  明: 禁止/允许中断
;
;调  用：
;         void Task (void *p_arg)
;         {
;			uint32_t  cpu_sr;
;		    cpu_sr = DisInt();              
;                   :
;                   :
; 	    	EnInt(cpu_sr);              
;         }
;*********************************************************************************************************
;程序返回值保存在R0中
DisInt
    MRS     R0, PRIMASK     ;保存全局中断标志到R0 ; Set prio int mask to mask all (except faults)
    CPSID   I	            ;关中断
    BX      LR
;程序第一个参数即为R0
EnInt
    MSR     PRIMASK, R0	    ;恢复全局中断标志
	CPSIE   I				;开中断
    BX      LR
;********************************************************************************************************
;                              任务上下文切换
;********************************************************************************************************
OS_CONTEX_SWITCH
	PUSH     {R4, R5}
	LDR      R4, =NVIC_INT_CTRL	;人工触发PendSV异常，参考ucos!!!
	LDR      R5, =NVIC_PENDSVSET
	STR      R5, [R4]
	POP    	 {R4, R5}
	BX       LR
;********************************************************************************************************
;                            内核启动
;********************************************************************************************************
OS_START
	LDR     R4, =NVIC_SYSPRI2      ; set the PendSV exception priority
	LDR     R5, =NVIC_PENDSV_PRI
	STR     R5, [R4]

	MOV     R4, #0                 ; set the PSP to 0 for initial context switch call
	MSR     PSP, R4

	LDR     R4, =NVIC_INT_CTRL     ;rigger the PendSV exception (causes context switch)
	LDR     R5, =NVIC_PENDSVSET
	STR     R5, [R4]

	CPSIE   I        ;enable interrupts at processor level

	B    .            ;should never get here
;********************************************************************************************************
;                               PendSV异常处理
;********************************************************************************************************
PendSV_Handler
	CPSID   I                                                   ; Prevent interruption during context switch
	MRS     R0, PSP                                             ; PSP is process stack pointer 
	CBZ     R0, Skip_Save		                                ; Skip register save the first time

;保存当前任务的上下文
	SUBS    R0, R0, #0x20                                       ; Save remaining regs r4-11 on process stack
	STM     R0, {R4-R11}

	LDR     R1, =OSTCBCur                                       ; OS_CUR_SP = SP
	LDR     R1, [R1]
	STR     R0, [R1]                                            ; R0 is SP of process being switched out

Skip_Save
	LDR     R0, =OSPrioCur                                      ; OSPrioCur = OSPrioHighRdy;
    LDR     R1, =OSPrioHighRdy
    LDRB    R2, [R1]
    STRB    R2, [R0]

	LDR     R0, =OSTCBCur                                       ; SP  = OS_NEXT_SP;
	LDR     R1, =OSTCBHighRdy									; OSTCBCur = OSTCBHighRdy
	LDR     R2, [R1]
	STR     R2, [R0]
	
	LDR     R0, [R2]                                            ; R0 is new process SP; 
	LDM     R0, {R4-R11}                                        ; Restore r4-11 from new process stack
	ADDS    R0, R0, #0x20
	MSR     PSP, R0                                             ; Load PSP with new process SP
	ORR     LR, LR, #0x04                                       ; Ensure exception return uses process stack
	CPSIE   I
	BX      LR                                                  ; Exception return will restore remaining context

	END
		
		