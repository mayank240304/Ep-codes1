#include <LPC214x.h>
#include "stdio.h"
void UartInit()	  
{
	PINSEL0 = 0x05;	   // set the functionality of TxD and Rxd 
 	U0LCR = 0x83;	   // Line control register :DLAB=1 ; 8  
                        //   bits; 1 stop bit ; no parity

	U0DLM = 0;					
	U0DLL = 97;					
	U0LCR = 0x03;	   // Line control register :DLAB=0 
}


int UART_PutChar(unsigned char Ch)
{if (Ch == '\n')  {
    while (!(U0LSR & 0x20));
    U0THR = 0x0D;        // output CR 
}

  while(!(U0LSR & 0x20));
   return( U0THR = Ch);                       
}

 int fputc(int ch, FILE *f)
 {	return (UART_PutChar(ch)); 
 }

struct __FILE { int handle;};
FILE __stdout;
