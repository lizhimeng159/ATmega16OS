

#include "Global.h"
/************************************************************
Function Name: delay_us
Inputs: int m
Outputs: none
Description:    ΢�뼶��ʱ������Ϊm
Writer: WZY
*************************************************************/
void delay_us(int m)
{
    int i ;
    for( i=0 ; i<m ; i++ )
        {
            NOP();      ///��ָ�1MHz��Ϊ1us
        }
}

/************************************************************
Function Name: delay_ms
Inputs: int n
Outputs: none
Description:    ���뼶��ʱ������Ϊn
Writer: WZY
*************************************************************/

void delay_ms(int n)
{
    int i,j ;
    for( i=0 ; i<n ; i++ )
    {
        for( j=0 ; j<125 ; j++ )
        {
            ;
        }
    }
}

