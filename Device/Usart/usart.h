/********************************************************************************************************/
#ifndef _USART_H
#define _USART_H
/*-----------------------------------------  I N C L U D E S  -----------------------------------------*/
#include "../Headers/Global.h"
/*---------------------------------------  D E F I N I T I O N  ---------------------------------------*/

//UCSRA��غ궨��
//��־λ
#define USART_FLAG_RXC     0x80   //���ս���
#define USART_FLAG_TXC     0x40   //���ͽ���
#define USART_FLAG_UDRE    0x20   //���ݼĴ�����
//����λ
#define USART_U2X          0x02   //���ٷ���

//UCSRB��غ궨��
//����λ
#define USART_RXCIE        0x80   //���ս����ж�ʹ��
#define USART_TXCIE        0x40   //���ͽ����ж�ʹ��
#define USART_UDRIE        0x20   //���ݼĴ������ж�ʹ��
#define USART_RXEN         0x10   //����ʹ��
#define USART_TXEN         0x08   //����ʹ��
#define USART_UCSZ2        0x04   //�ַ�����  ������λ���ʹ��

//UCSRC��غ궨��
//����λ
#define UCSRC_URSEL        0x80   //�Ĵ���ѡ��
#define USART_UMSEL        0x40   //USARTģʽѡ��
#define USART_UPM          0x30   //��żУ��ģʽѡ��
#define USART_USBS         0x08   //ֹͣλѡ��
#define USART_UCSZ1        0x04   //�ַ�����
#define USART_UCSZ0        0x02   //�ַ�����

//UBRRH��غ궨��
#define UBRRH_URSEL        0x8000 //�Ĵ���ѡ��

/*--------------------------------------  D E C L A R A T I O N  --------------------------------------*/
/* Internal Variable */

/* External Variable */

/* Internal Function */

/* External Function */
extern void USART_Init(UINT16 baud);
extern  UINT8 USART_Rx(void);
extern void USART_Tx(UINT8 buf);

#endif /*_USART_H*/
//===========================================  End Of File  ===========================================//
