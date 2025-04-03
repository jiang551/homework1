#include  <INTRINS.H>
void Delay1ms(unsigned int ms)	//@12.000MHz
{
	unsigned char data i, j;

	i = 12;
	j = 169;
	while(ms--)
		{
	do
	 {
		 while (--j);
	 } while (--i);
		}
}