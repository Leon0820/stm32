;********************************************************************************************************
;  * @file    cmOS.s
;  * @author  ������
;  * @version V1.0.0
;  * @date    2014-12-22
;  * @brief   ��cmOS�йصĵײ�����������жϣ��������л�
;********************************************************************************************************

;********************************************************************************************************
;                                           PUBLIC FUNCTIONS
;********************************************************************************************************

    EXTERN  OSPrioCur					;��ǰ����Ķ�ջָ��
    EXTERN  OSPrioHighRdy				;�¸���Ҫ��������Ķ�ջָ��
    EXTERN  OSTCBCur					
    EXTERN  OSTCBHighRdy

    EXPORT  DisInt                               ;Functions declared in this file
    EXPORT  EnInt

	EXPORT  OS_CONTEX_SWITCH;�������л�
    EXPORT  OS_START;��ʼ���������

	EXPORT  PendSV_Handler;��Ҫ��������������ϵͳĬ�Ͻӿ�
;********************************************************************************************************
;                                                EQUATES
;********************************************************************************************************
NVIC_INT_CTRL   	EQU     0xE000ED04  ; �жϿ��ƼĴ���
NVIC_SYSPRI2    	EQU     0xE000ED20  ; ϵͳ���ȼ��Ĵ���2
NVIC_PENDSV_PRI 	EQU     0xFFFF0000   ; ����жϺ�ϵͳ�����ж�
NVIC_PENDSVSET  	EQU     0x10000000  ; ��������жϵ�ֵ
;********************************************************************************************************
;                                      CODE GENERATION DIRECTIVES
;********************************************************************************************************

    AREA |.text|, CODE, READONLY, ALIGN=2
    THUMB
    REQUIRE8
    PRESERVE8

;*********************************************************************************************************
;��������uint32_t DisInt(void);
;		 void 	   EnInt(uint32_t cpu_sr); 
;˵  ��: ��ֹ/�����ж�
;
;��  �ã�
;         void Task (void *p_arg)
;         {
;			uint32_t  cpu_sr;
;		    cpu_sr = DisInt();              
;                   :
;                   :
; 	    	EnInt(cpu_sr);              
;         }
;*********************************************************************************************************
;���򷵻�ֵ������R0��
DisInt
    MRS     R0, PRIMASK     ;����ȫ���жϱ�־��R0 ; Set prio int mask to mask all (except faults)
    CPSID   I	            ;���ж�
    BX      LR
;�����һ��������ΪR0
EnInt
    MSR     PRIMASK, R0	    ;�ָ�ȫ���жϱ�־
	CPSIE   I				;���ж�
    BX      LR
;********************************************************************************************************
;                              �����������л�
;********************************************************************************************************
OS_CONTEX_SWITCH
	PUSH     {R4, R5}
	LDR      R4, =NVIC_INT_CTRL	;�˹�����PendSV�쳣���ο�ucos!!!
	LDR      R5, =NVIC_PENDSVSET
	STR      R5, [R4]
	POP    	 {R4, R5}
	BX       LR
;********************************************************************************************************
;                            �ں�����
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
;                               PendSV�쳣����
;********************************************************************************************************
PendSV_Handler
	CPSID   I                                                   ; Prevent interruption during context switch
	MRS     R0, PSP                                             ; PSP is process stack pointer 
	CBZ     R0, Skip_Save		                                ; Skip register save the first time

;���浱ǰ�����������
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
		
		