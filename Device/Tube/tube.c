
#include "Global.h"

int tube[10] = { 0x3f , 0x06 , 0x5b , 0x4f , 0x66 , 0x6d , 0x7d , 0x07 , 0x7f , 0x6f };  ///���������0~9

/************************************************************
Function Name: init_tube
Inputs: none
Outputs: 0
Description:    ����ܳ�ʼ����P3��a~p��PD0~7���������ƶ�ѡ��P4��0~7��PB��0~7����������λѡ
Writer: WZY
*************************************************************/
int init_tube(void)
{
    DDRB = 0XFF ;    ///�Ĵ�������Ϊ���
    DDRD = 0XFF ;
    PORTB = 0xff ;   ///����ܹ����ӷ�������λѡ����ߵ�ƽ������ܲ���ͨ
    return 0 ;
}

/************************************************************
Function Name: tube_on
Inputs: int t
Outputs: none
Description:    8λ�������ʾͬһ������0~9֮��ĸ���intֵt
Writer: WZY
*************************************************************/
void tube_on(int t)
{
    init_tube();
    PORTB = 0x00 ;   ///������ƽ����
    PORTD = tube[t] ;    ///�����ߵ�ƽʱ��ͨ
    delay_ms(1000);
}

/************************************************************
Function Name: tube_circle
Inputs: int c
Outputs: none
Description:    8λ����ܴ�������ѭ����ʾ0~7,ѭ��c��
Writer: WZY
*************************************************************/
void tube_circle(int c)
{
    int i,j ;
    init_tube();
    for( j=0 ; j<c ; j++ )  ///����ѭ������
    {
        for( i=0 ; i<8 ; i++ )
        {
            PORTB = ~(1<<i) ;   ///��λ��ͨ������
            PORTD = tube[i] ;
            delay_ms(300);
        }
    }
    PORTB = 0xff ;
}
