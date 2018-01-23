
#include "Global.h"

//�������������
//���� ���ȼ�Ϊ x x x x x x x x
//              7 6 5 4 3 2 1 0
//���У�0�����ȼ���ߣ�7�����ȼ����
UINT8 OSRdyTbl;

//��ǰ����������е����λ
UINT8 OSPrioHighRdy;

//��ǰ�����ȼ�
UINT8 OSPrioCur;

//����һ�����к��������ı���
UINT32 Idle_Count = 0;

//������������ջ
UINT8 Idle_Task_Stk[64];

//��ǰ��������
void OSSched(void);
void ATmega16OS_Task_Switch(void);
void ATmega16OS_Time_Delay(UINT16 Ticks);
void ATmega16OS_SysTick_Init(void);

//������Ӧ������Ϊ ����״̬
void ATmega16OS_SetPrioRdy(UINT8 Prio)
{
	OSRdyTbl |= 0x01 << Prio;
}

//���ڽ�ĳ�����������������ɾ��
void ATmega16OS_DelPrioRdy(UINT8 Prio)
{
	OSRdyTbl &= ~(0x01 << Prio);
}

//�������������ѡ�����ȼ�����ߵ�����
void ATmega16OS_GetHighRdy(void)
{
	SINT8 Temp_OSNextTaskPrio  = 7;
	UINT8 Final_OSNextTaskPrio = 7;
	for (Temp_OSNextTaskPrio = 7; Temp_OSNextTaskPrio >= 0; Temp_OSNextTaskPrio--)
    {
		if (OSRdyTbl&(0x01 << Temp_OSNextTaskPrio))
		{
			Final_OSNextTaskPrio = Temp_OSNextTaskPrio;
		}
    }
	//��ֵ������ȼ�����
	OSPrioHighRdy = Final_OSNextTaskPrio;
}

//OS�����񴴽�����
//������������
//����ָ�� �����ջ  �������ȼ�
void ATmega16OS_TaskCreate(void (*Task)(void), UINT8 *P_Stk, UINT8 Prio)
{
		*(P_Stk--) = (UINT16)Task   ;       
		*(P_Stk--) = (UINT16)Task>>8;      

		*(P_Stk--) = 0x00   ;                //R 1
		*(P_Stk--) = 0x00;                   //R 0 

		*(P_Stk--) = 0x00;                   //SREG
		*(P_Stk--) = 0x02;                   //R 2
		*(P_Stk--) = 0x03;                   //R 3
		*(P_Stk--) = 0x04;                   //R 4
		*(P_Stk--) = 0x05;                   //R 5
		*(P_Stk--) = 0x06;                   //R 6
		*(P_Stk--) = 0x07;                   //R 7
		*(P_Stk--) = 0x08;                   //R 8
		*(P_Stk--) = 0x09;                   //R 9
		*(P_Stk--) = 0x0A;                   //R10
		*(P_Stk--) = 0x0B;                   //R11
		*(P_Stk--) = 0x0C;                   //R12
		*(P_Stk--) = 0x0D;                   //R13
		*(P_Stk--) = 0x0E;                   //R14
		*(P_Stk--) = 0x0F;                   //R15
		*(P_Stk--) = 0x10;                   //R16
		*(P_Stk--) = 0x11;                   //R17
		*(P_Stk--) = 0x12;                   //R18
		*(P_Stk--) = 0x13;                   //R19
		*(P_Stk--) = 0x14;                   //R20
		*(P_Stk--) = 0x15;                   //R21
		*(P_Stk--) = 0x16;                   //R22
		*(P_Stk--) = 0x17;                   //R23
		*(P_Stk--) = 0x18;                   //R24
		*(P_Stk--) = 0x19;                   //R25
		*(P_Stk--) = 0x1A;                   //R26
		*(P_Stk--) = 0x1B;                   //R27
		*(P_Stk--) = 0x1C;                   //R28
		*(P_Stk--) = 0x1D;                   //R29
		*(P_Stk--) = 0x1E;                   //R30
		*(P_Stk--) = 0x1F;                   //R31
        
		//д�����������
		ATmega16OS_SetPrioRdy(Prio);
		
        //����ָ��ָ��
		TCB[Prio].Function = Task;

		//������Ӧ��TCB��ջָ������
        TCB[Prio].StkPtr = (UINT16)P_Stk;  

		//��λ��������ȼ�
		TCB[Prio].Priority = Prio;

        //��ʼ�����������
		TCB[Prio].DelayTick = 0;
}

//����ϵͳ��������
void ATmega16OS_Start(void)
{
	//���ҵ����ȼ������ߵ�����
	ATmega16OS_GetHighRdy();
    //��ֵ��ǰ���ȼ�
	OSPrioCur = OSPrioHighRdy;
    //����SPָ��׼��������PC������������ȼ���ջ�ĺ������
    SP = TCB[OSPrioCur].StkPtr + 33;

}

//�����л�����
void ATmega16OS_Task_Switch(void)
{
	//�ҵ����ȼ������ߵ�����
	ATmega16OS_GetHighRdy();
    //����ִ�������л�����
	OSSched();
}

//����ϵͳ��ʼ������
void ATmega16OS_Init(void)
{
	//����ϵͳ����
	ATmega16OS_SysTick_Init();
	//������������
	ATmega16OS_TaskCreate(ATmega16OS_Idle_Task,&Idle_Task_Stk[63],7);
}

//���еĿ�������
void ATmega16OS_Idle_Task(void)
{
	while (ON)
	{
		Idle_Count++;
	}
}

//ϵͳ������ʼ�� �õ�TIM2 10msһ��
void ATmega16OS_SysTick_Init(void)
{    
     //�򿪶�ʱ���ж�ʹ��
     MCUCR |=(1<<TOIE2);	
     //��ʱ���ж�ʹ��
     TIMSK|=(1<<TOIE2);
	 //��ʱ������ֵ 
     TCNT2 =0;
	 //64��Ƶ
     TCCR2 |= ((1 << CS01)|(1 << CS00));
}

//ϵͳ���ඨʱ�������Ӻ��� 10ms����һ��
void ATmega16OS_Tick_Hook(void)
{
	UINT8 i = 0;
	for(i = 0;i < 8;i++)
	{
	   if(TCB[i].DelayTick != 0)
	   {
	      TCB[i].DelayTick--;
		  if(TCB[i].DelayTick == 0)
		  {
		     ATmega16OS_SetPrioRdy(i);
		  }
	   }
	}
	//�ҵ����ȼ������ߵ����񣬲������������
	ATmega16OS_Task_Switch();
}

//���������
void ATmega16OS_Task_Sem_Suspend(void)
{
    //ɾ��Ŀǰ���ȼ���ߵ�����
	ATmega16OS_DelPrioRdy(OSPrioCur);
	//�����������
	ATmega16OS_Task_Switch();
}

//�����ź�������
void ATmega16OS_Task_Sem_Post(void (*Task)(void))
{
    UINT8 Temp_Pro;
	//��ȡ���ȼ�
	for(Temp_Pro = 0;Temp_Pro < 8;Temp_Pro++)
	{
	    if(TCB[Temp_Pro].Function == Task)
		{
		    break;
		}
	}
    //��λ��Ӧ�����ȼ�
	ATmega16OS_SetPrioRdy(Temp_Pro);
	//�����������
	ATmega16OS_Task_Switch();
}

//��ʱ����ʱ����
void ATmega16OS_Time_Delay(UINT16 Ticks)
{
	//�������������
	ATmega16OS_DelPrioRdy(OSPrioCur);
	//����ʼ�ս�����
	TCB[OSPrioCur].DelayTick = Ticks;
	//�й������л�
	ATmega16OS_Task_Switch();
}

void OSSched(void)
{
	OS_ENTER_CRITICAL();

	if (OSPrioHighRdy != OSPrioCur)
	{
		__asm__ __volatile__("PUSH __zero_reg__          \n\t");
		__asm__ __volatile__("PUSH __tmp_reg__           \n\t");
		__asm__ __volatile__("IN   __tmp_reg__,__SREG__  \n\t");
		__asm__ __volatile__("PUSH __tmp_reg__           \n\t");
		__asm__ __volatile__("PUSH R2                    \n\t");
		__asm__ __volatile__("PUSH R3                    \n\t");
		__asm__ __volatile__("PUSH R4                    \n\t");
		__asm__ __volatile__("PUSH R5                    \n\t");
		__asm__ __volatile__("PUSH R6                    \n\t");
		__asm__ __volatile__("PUSH R7                    \n\t");
		__asm__ __volatile__("PUSH R8                    \n\t");
		__asm__ __volatile__("PUSH R9                    \n\t");
		__asm__ __volatile__("PUSH R10                   \n\t");
		__asm__ __volatile__("PUSH R11                   \n\t");
		__asm__ __volatile__("PUSH R12                   \n\t");
		__asm__ __volatile__("PUSH R13                   \n\t");
		__asm__ __volatile__("PUSH R14                   \n\t");
		__asm__ __volatile__("PUSH R15                   \n\t");
		__asm__ __volatile__("PUSH R16                   \n\t");
		__asm__ __volatile__("PUSH R17                   \n\t");
		__asm__ __volatile__("PUSH R18                   \n\t");
		__asm__ __volatile__("PUSH R19                   \n\t");
		__asm__ __volatile__("PUSH R20                   \n\t");
		__asm__ __volatile__("PUSH R21                   \n\t");
		__asm__ __volatile__("PUSH R22                   \n\t");
		__asm__ __volatile__("PUSH R23                   \n\t");
		__asm__ __volatile__("PUSH R24                   \n\t");
		__asm__ __volatile__("PUSH R25                   \n\t");
		__asm__ __volatile__("PUSH R26                   \n\t");
		__asm__ __volatile__("PUSH R27                   \n\t");
		__asm__ __volatile__("PUSH R28                   \n\t");
		__asm__ __volatile__("PUSH R29                   \n\t");
		__asm__ __volatile__("PUSH R30                   \n\t");
		__asm__ __volatile__("PUSH R31                   \n\t");  //��ջ���

        TCB[OSPrioCur].StkPtr = SP;
        OSPrioCur = OSPrioHighRdy;
        SP = TCB[OSPrioCur].StkPtr;

		__asm__ __volatile__("POP  R31                   \n\t");
		__asm__ __volatile__("POP  R30                   \n\t");
		__asm__ __volatile__("POP  R29                   \n\t");
		__asm__ __volatile__("POP  R28                   \n\t");
		__asm__ __volatile__("POP  R27                   \n\t");
		__asm__ __volatile__("POP  R26                   \n\t");
		__asm__ __volatile__("POP  R25                   \n\t");
		__asm__ __volatile__("POP  R24                   \n\t");
		__asm__ __volatile__("POP  R23                   \n\t");
		__asm__ __volatile__("POP  R22                   \n\t");
		__asm__ __volatile__("POP  R21                   \n\t");
		__asm__ __volatile__("POP  R20                   \n\t");
		__asm__ __volatile__("POP  R19                   \n\t");
		__asm__ __volatile__("POP  R18                   \n\t");
		__asm__ __volatile__("POP  R17                   \n\t");
		__asm__ __volatile__("POP  R16                   \n\t");
		__asm__ __volatile__("POP  R15                   \n\t");
		__asm__ __volatile__("POP  R14                   \n\t");
		__asm__ __volatile__("POP  R13                   \n\t");
		__asm__ __volatile__("POP  R12                   \n\t");
		__asm__ __volatile__("POP  R11                   \n\t");
		__asm__ __volatile__("POP  R10                   \n\t");
		__asm__ __volatile__("POP  R9                    \n\t");
		__asm__ __volatile__("POP  R8                    \n\t");
		__asm__ __volatile__("POP  R7                    \n\t");
		__asm__ __volatile__("POP  R6                    \n\t");
		__asm__ __volatile__("POP  R5                    \n\t");
		__asm__ __volatile__("POP  R4                    \n\t");
		__asm__ __volatile__("POP  R3                    \n\t");
		__asm__ __volatile__("POP  R2                    \n\t");
		__asm__ __volatile__("POP  __tmp_reg__           \n\t");
		__asm__ __volatile__("OUT  __SREG__,__tmp_reg__  \n\t");
		__asm__ __volatile__("POP  __tmp_reg__           \n\t"); 
		__asm__ __volatile__("POP  __zero_reg__          \n\t"); 
	}

	OS_EXIT_CRITICAL();
}


SIGNAL(SIG_OVERFLOW2)
{
    OS_ENTER_CRITICAL();

	TCNT2 = 100;
	ATmega16OS_Tick_Hook();

	OS_EXIT_CRITICAL();
}
