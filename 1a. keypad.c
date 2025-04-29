#include "lpc214x.h"

unsigned int COL[]={4,5,6,7};
unsigned int KeyCodes[]={'1','4','7','*','2','5','8','0','3','6','9','#','A','B','C','D'};

void delay(unsigned int time)
{
unsigned int i,j;
	for(i = 0; i < time ;i++ )
	{
		for(j = 0; j < 10000 ; j++);
	}
}

unsigned char GetKey(unsigned int* Key)
{
unsigned int col,rowdata,count=0;

for(col = 0 ; col < 4 ; col++)
{
	IOCLR0 = 1 << COL[col] ;			// set the column line low
	delay(2);							//debounce
	rowdata = IOPIN0;
	delay(1);							//debounce
	rowdata = IOPIN0;
	rowdata >>= 8;

	if((rowdata & 0xF)!=0xF)
	{
		for(count = 0; count < 4 ; count++)
		{
			if((rowdata & 0x01)== 0)
			{
				*Key = KeyCodes[(col*4)+ count];
				IOSET0 = 1 << COL[col] ;			// set the column line HIGH
				return 1;
			}
			rowdata >>= 1;
		}
	}
	IOSET0 = 1 << COL[col] ;			// set the column line HIGH
}

return 0;
}


int main(void)
{
unsigned int keycode;
unsigned char *ch = "Key Pressed ->";
LCD_init();
PINSEL0 = 0x00000000;
IODIR0 = 0x000ff0f0;
IOSET0 = 0x000000F0;
while(*ch)
	LCD_data(*ch++);


while(1)
{
	if(GetKey(&keycode))
	{
		LCD_cmd(0xc4);
		LCD_data(keycode);
		delay(100);
	}
}
return 0;
}
