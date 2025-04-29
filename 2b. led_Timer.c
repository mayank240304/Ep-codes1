#include <lpc21xx.h>
        
void delay(unsigned int itime);
int main (void) 
{ 
IODIR0 = 0x000ff000; 
while (1)                           
{   
IOSET0=0x000ff000; 
delay(1000);
IOCLR0=0x000ff000; 
delay(1000);   
}
        
}
void delay(unsigned int itime)
{
T0PR=4999; 
	T0MR0=100; // Count in match register
	T0TC=0x00000000; // initial value always starts with Zero
	T0TCR=0X01; //START TIMER
	while(T0TC !=T0MR0); // Wait till T0TC value becomes equal to T0MR0
	T0TCR=0X02; //STOP TIMER
}

