
#ifndef _74HC595_H_
#define _74HC595_H_

#define DATA_HIGH PORTB|=(1<<0)      ///����������
#define DATA_LOW PORTB&=~(1<<0)      ///����������
#define LCLK_HIGH PORTB|=(1<<1)      ///����������
#define LCLK_LOW PORTB&=~(1<<1)      ///����������
#define SCLK_HIGH PORTB|=(1<<2)      ///ʱ��������
#define SCLK_LOW PORTB&=~(1<<2)      ///ʱ��������

extern void init_74HC595(void);
extern void send_data_to_74HC595(int data);
extern void display_74HC595(int sit, int seg);
extern void tube_0_to_9(void);
extern void tube_liushui(int t);
extern void tube_decimal_num(long dec_num);

#endif
