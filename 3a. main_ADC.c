#include <LPC214x.h>
	
#define ADC0 1 << 24 

#define VREF 3.3 

int main(void)
{

int i,j;
int unsigned long result;
unsigned char key;
PINSEL1 = (1<<24);// INITIALIZE ADC0 CH0 AD0.1 (p0.28) 
UartInit();
AD0CR = 0X01210302;
// Channel 0, Clock 4Mhz, Burst Mode,10 bit,PDN = 1, 

while(1)
  {	
	while(!(AD0DR1 & 0X80000000)); // wait for conversion 
	
	result = ((AD0DR1>>6) & 0x3ff);	
	printf("\nVoltage on AD0.1 = %dmV\n",(int)( result*VREF ));
	for(j=9;j>=0;j--)
	{
	key=(result>>j)&0x001; // fetching MSB to LSB bits at a time
	UART_PutChar(key+0x30);// conversion to ASCII
	}
	 for(i=0;i<10000;i++)
	 	for(j=0;j<5000;j++);
	}
	
	return 0;
}
