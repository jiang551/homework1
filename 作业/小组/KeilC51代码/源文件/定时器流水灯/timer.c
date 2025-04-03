#include <REGX52.H>
#include "delay.h"
void timer0_init(void)
{
	PCON |= 0x80;		
	SCON = 0x50;		
	TMOD &= 0x0F;		
	TMOD |= 0x20;		
	TL1 = 0xF3;			
	TH1 = 0xF3;		
	ET1 = 0;			
	TR1 = 1;			
	EA=1;
	ES=0;
	TMOD &= 0xF0;		
	TMOD |= 0x01;		
	TF0=1;
	TR0=1;
	TH0=64535/256;
	TL0=64535%256;
	ET0=1;
	
	PT0=0;
}
void sendbyte(unsigned char Byte)
{
  SBUF=Byte;
	while(TI==0);
	TI=0;
}
void sendstring(unsigned char*Byte)
{
	while(*Byte!='\0'){
 sendbyte(*Byte);
	Delay1ms(2);
	Byte++;
	}
}
unsigned int count;
unsigned int a=-1;
void Tim0_Rountine(void) interrupt 1
{
	count++;
	if(count==10)
	{	
	if(a==8)
	{
	a=0;
	}
	else
	{
	a++;
	}
 	P2=~(0X01<<a);
	count=0;
	sendstring("Hello,world!");
	}
}
void Usart_Rountine(void) interrupt 4
{
if(RI==1)
{
  P2=0X0F;
	RI=0;
}

}