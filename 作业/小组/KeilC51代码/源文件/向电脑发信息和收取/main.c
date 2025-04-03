#include <REGX52.H>
#include  <INTRINS.H>
#include "delay.h"
#include "timer.h"
#include "Nixie.h"
extern volatile bit flag_send ;
extern unsigned int abt;
void main ()
{
	timer0_init();
	while(1)
	{
		Nixie(2, abt);
		if (flag_send) {
            sendstring("Hello,world!");
            flag_send = 0;
		}
	}
}