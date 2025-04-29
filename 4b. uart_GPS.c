#include "stdio.h"
#include "LPC214x.h"

void UartInit()     
{ 
	             	   
    PINSEL0 = 0x00050005;        //Enable RxD0 and TxD0                    
    U0LCR = 0x83;                // 8 bits, no Parity, 1 Stop bit
	U0DLM = 00;		      //0x00;
	U0DLL = 97;			 //0x97;        
    U0LCR = 0x03; 			 // DLAB = 0 
	U1LCR = 0x83;               // 8 bits, no Parity, 1 Stop bit
	U1DLM = 00;			 //0x00;
	U1DLL = 97;			 //0x97;        
    U1LCR = 0x03; 			 // DLAB = 0   
} 
																										 
unsigned char UART1_GetChar(void)
{	
	while(!(U1LSR & 0x01));
	return(U1RBR);
} 

unsigned char UART0_PutChar(unsigned char Ch)
{
  	while(!(U0LSR & 0x20));
		U0THR =Ch;
	 return Ch;
}  

void UART0_PutS(unsigned char *Ch)
{
	while(*Ch)
		UART0_PutChar(*Ch++);
}

