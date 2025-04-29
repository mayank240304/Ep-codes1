#include<lpc214x.h>
#define LED0  12  

void delay(unsigned int time)
{
unsigned int i,j;
	for(i = 0; i < time ;i++ )
	{
		for(j = 0; j < 5000 ; j++);
	}
}

int main(void)
{
int i,j;

  PINSEL0 = 0x00000000;  //set the pin function for pins as GPIO
  IODIR0 = 0x000FF000;  // set the direction of pins as  output 

while(1)
{
  for(i = 0; i < 4 ; i++)
 {
	IOSET0 = 0x000FF000;			// set the port pins to 1
	delay(150);
	IOCLR0 = 0x000FF000;			//clear the port pins to 0
	delay(150);
 }
 //LED Rolling
 for(i = 0 ; i < 4 ; i++)
 {
 	for(j = 0 ; j < 8; j++)
	{
		IOSET0 = 1 << (LED0 + j);	 // set the port pins to 1
		delay(50);
	}
	for(j = 7 ; j >= 0; j--)
	{
		IOCLR0 = 1 << (LED0 + j); //clear the port pins to 0
		delay(50);
	}
 }
 // LED SINGLE Rolling

 for(i = 0 ; i < 5 ; i++)
 {
 	for(j = 0 ; j < 8; j++)
	{
		IOCLR0 = 1 << (LED0 + j);  //clear the port pins to 0
		delay(50);
		IOSET0 = 0xFF <<(LED0 + j);// set the port pins to 1
		delay(50);
	}
	for(j = 7 ; j >= 0; j--)
	{
		IOCLR0 = 1 << (LED0 + j);  //clear the port pins to 0
		delay(50);
		IOSET0= 0xFF << (LED0 + j); // set the port pins to 1
		delay(50);
	}
 } 

}

return 0;

}
