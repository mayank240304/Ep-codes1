#include<lpc214x.h>
#include "stdio.h"

int main()
{	unsigned int i=0;
	unsigned char ch, temp[100];
	UartInit();	  	
/* 	This function fetches a string from serial port starts with a character '$' 	And ends with a character '*' */
	
	if((ch = UART1_GetChar()) == '$')	//if '$' is received
		{
			do
			{
				temp[i] = UART1_GetChar();
			} while(temp[i++] != '*');			
//while '*' character is not received, keep fetching the string
			temp[i] = '\0';							//add a NULL character at the end of the string
				
	UART0_PutS(temp);//display lat and lon on Hyperterminal
			}  
			 
	return 0;
}
