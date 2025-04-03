#include <REGX52.H>
#include "delay.h"
#include "Nixie.h"
void timer0_init(void)
{
	PCON |= 0x80;		
	SCON = 0x50;		
	TMOD &= 0x0F;		
	TMOD |= 0x20;		
	TMOD &= 0xF0;		
	TMOD |= 0x01;		
	TL1 = 0xF3;			
	TH1 = 0xF3;		
	ET1 = 0;			
	TR1 = 1;			
	EA=1;
	ES=0;
	TF0=1;
	TR0=1;
	TH0 = 0xFC;
TL0 = 0x18;
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
	Delay1ms(1);
	Byte++;
	}
}
volatile bit flag_send = 0;
unsigned int abt;
unsigned int count;
void Tim0_Rountine(void) interrupt 1
{
	count++;
	if(count==10){
		 flag_send = 1;
	count=0;
	}
}
void UART_Routine(void) interrupt 4 {
    if (RI == 1) {
        abt= SBUF;  
        RI = 0;
    }
}