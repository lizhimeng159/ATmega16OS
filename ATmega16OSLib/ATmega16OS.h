
#ifndef _ATMEGA16OS_H_
#define _ATMEGA16OS_H_

#define OS_ENTER_CRITICAL() cli()
#define OS_EXIT_CRITICAL()  sei()

//������ƿ�Ķ���
struct Os_Tcb
{
	UINT16  StkPtr;        //���������ջ
	void    (*Function)(); //ָ����ָ��
	UINT8   Priority;      //�������ȼ�
	UINT16  DelayTick;     //��ʱ������ 10msΪһ������
	UINT8   SemFlag;
};

//����������ƿ�
struct Os_Tcb TCB[8];

extern void ATmega16OS_Start(void);
extern void ATmega16OS_Init(void);
extern void ATmega16OS_TaskCreate(void (*Task)(void), UINT8 *P_Stk, UINT8 Prio);
extern void ATmega16OS_Time_Delay(UINT16 Ticks);
extern void ATmega16OS_Task_Sem_Suspend(void);
extern void ATmega16OS_Task_Sem_Post(void (*Task)(void));

extern UINT8 Idle_Task_Stk[64];

extern void ATmega16OS_Idle_Task(void);
#endif
