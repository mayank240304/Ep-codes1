   #include "lpc214x.h"
   #include "stdio.h"
void UartInit()	  
{
  
 PINSEL0 =  0x05;
 U0LCR = 0x83;	// LCR :DLAB=1 ; 8 bits ; 1 stop bit ; no parity
	U0DLM = 00;					
	U0DLL = 97;					
	U0LCR = 0x03;	// Line control register :DLAB=0 	
}

int UART_GetChar(void)
{
	while(!(U0LSR & 0x1)); 
     return(U0RBR);
}

int UART_PutChar(unsigned char Ch)
{
     while(!(U0LSR & 0x20));
     return( U0THR = Ch);
}

int main(void)
{
   UartInit(9600);			// initialise the UART0
   
while(1)
{
		UART_PutChar(UART_GetChar()+1);
}
return 0;
}




