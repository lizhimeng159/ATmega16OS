
#include "Global.h"

/************************************************************
Function Name: init_74HC595
Inputs: none
Outputs: none
Description:    ��λ�Ĵ����˿ڳ�ʼ����PB0(������)��PB1(������)��PB2(ʱ����)���˿�Ϊ������
Writer: WZY
*************************************************************/
void init_74HC595(void)
{
    DDRB |= 0x07;       ///PB0~2��ʼ��Ϊ���״̬
    LCLK_HIGH ;         ///����������
}

/************************************************************
Function Name: send_data_to_74HC595
Inputs: int data
Outputs: none
Description:    �������ݸ���λ�Ĵ���
Writer: XZ,WZY,WH
*************************************************************/
void send_data_to_74HC595(int data)
{
    int i , data_temp=0 ;
    data_temp = data ;
    for (i=0;i<8;i++)                       ///һ��ֻ�ܷ���һ���ֽڵ����ݣ�8λ��
    {
        if( data_temp & (1<<(7-i)) )        ///�Ӹ�λ��ʼ����
            DATA_HIGH;                      ///����������
        else
            DATA_LOW;                       ///����������
        SCLK_HIGH ;                         ///ʱ��������
        NOP() ; NOP() ;

        SCLK_LOW ;                          ///ʱ��������
    }
}

/************************************************************
Function Name: display_74HC595
Inputs: int sit, int seg
Outputs: none
Description:    ��74HC595������������,ǰ8λΪ��ѡ�����λΪλѡ��ѡһλ��
Writer: XZ,WH,WZY
*************************************************************/
void display_74HC595(int sit, int seg)    ///situationΪλ,segmentΪ��
{
    init_74HC595();
    LCLK_LOW ;
    send_data_to_74HC595( ~(1<<sit) );
    send_data_to_74HC595( tube[seg] );
    LCLK_HIGH ;
}

/************************************************************
Function Name: tube_0_to_9
Inputs: none
Outputs: none
Description:    8λ����ܴ�0~9ѭ����ʾ
Writer: WZY,DSY
*************************************************************/
void tube_0_to_9(void)
{
    int i=0,j=0,k=0;
    while (1)
    {
        for( i=0; i<10; i++ )
        {
            for (k=0;k<50;k++)
                {
                    for(j=0;j<8;j++)
                        {
                            display_74HC595(j,i) ;
                        }
                }
            delay_ms(1);
        }
    }
}

/************************************************************
Function Name: tube_liushui
Inputs: int t
Outputs: none
Description:    ��λ�Ĵ���ʵ��������ˮЧ��,t������λʱ��(ms)
Writer: WZY
*************************************************************/
void tube_liushui(int t)
{
//    int i=0,j=0;
    while (1)
    {
 //       for( i=0; i<8; i++ )
 //       {
 //           display_74HC595(i,i) ;
   //         delay_ms(t);
  //      }
    }
}

/************************************************************
Function Name:  tube_decimal_num
Inputs: long dec_num
Outputs: none
Description:    ���������ʾһ��ʮ�����������Ҷ���
Writer: WZY
*************************************************************/
void tube_decimal_num(long dec_num)
{
    int weishu=0,i=0;
    long num_temp=0;
    num_temp=dec_num;
    do
    {
        num_temp = num_temp/10;
        weishu++;
    }
    while( num_temp!=0 );
  //  while(1)
 //   {
        num_temp=dec_num;
        for( i=0; i<weishu; i++ )
        {
            display_74HC595( 7-i, (num_temp%10) );
            num_temp = num_temp/10;
          //  delay_ms(1);
        }
 //   }
}
