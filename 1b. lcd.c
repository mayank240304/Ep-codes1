/*RS-	P1.20, EN-P1.21	*/

#include<lpc214x.h>
#define RS 1<<20					//define RS pin
#define EN 1<<21					//define EN pin


void LCD_data(unsigned char ch)			  
{
	IOCLR0 = 0x000FF000;				   //clear LCD pins
	IOSET0 = ch<<12;            //shift data and set the data 
	IOSET1 = RS;						   
	IOSET1 = EN;               //EN pulse
	delay(100);
	IOCLR1 = EN;							   
}

void LCD_cmd(unsigned char ch)		   
{
	IOCLR0 = 0x000FF000;
	IOSET0 = ch<<12;           //shift data and set the data 
	IOCLR1 = RS;						  
	IOSET1 = EN;               //EN pulse
	delay(100);
	IOCLR1 = EN;
}

void LCD_init()
{
	IODIR0 = 0x000FF000; 			  //set the pins as output
	IODIR1 = RS | EN;

	LCD_cmd(0x38);		   		     //8bit use both lines
	LCD_cmd(0x06);					       //Entry mode
	LCD_cmd(0x0C);				 //display ON cursor OFF
	LCD_cmd(0x01);						 //Clear display
	LCD_cmd(0x80);	         //cursor at 1st line 1st position
}







