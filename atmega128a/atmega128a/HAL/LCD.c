
#include "LCD.h"

#ifndef LCD_MODE
#define LCD_MODE _8_BIT
#endif
#if(LCD_MODE == _8_BIT)

static void LCD_write_command (u8 command)
{
	    DIO_Writepin(RS,LOW);
		//DIO_Writepin(RW,LOW);
		DIO_Writeport(LCD_PORT,command);
		DIO_Writepin(EN,HIGH);
		_delay_ms(1);
		DIO_Writepin(EN,LOW);
		_delay_ms(1);
		//DIO_Writepin(PINA5,HIGH);

}
static void LCD_write_data (u8 data)
{
	DIO_Writepin(RS,HIGH);
	//DIO_Writepin(RW,LOW);
	DIO_Writeport(LCD_PORT,data);
	DIO_Writepin(EN,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN,LOW);
	_delay_ms(1);

}
void LCD_Init(void)
{
	    _delay_ms(50);
	LCD_write_command(0x38);  //8-bit mode,, 2-line ,, 5*7sets
		_delay_ms(1);
	LCD_write_command(0x0c);  //display on ,, cursor on ,, blink on (you may change it to 0x0f , 0x0c , 0x0e)  
	_delay_ms(1);
	LCD_write_command(0x01); // to clear LCD
		_delay_ms(2);
	LCD_write_command(0x06);  // sets the move direction of cursor and display 
		_delay_ms(1);




}
#elif(LCD_MODE==_4_BIT)

static void LCD_write_command (u8 command)
{
	DIO_Writepin(RS,LOW);
	//DIO_Writepin(RW,LOW);
	
	DIO_Writepin(D4,READ_BIT(command,4));
	DIO_Writepin(D5,READ_BIT(command,5));
	DIO_Writepin(D6,READ_BIT(command,6));
	DIO_Writepin(D7,READ_BIT(command,7));
	DIO_Writepin(EN,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN,LOW);
	_delay_ms(1);
	
	DIO_Writepin(D4,READ_BIT(command,0));
	DIO_Writepin(D5,READ_BIT(command,1));
	DIO_Writepin(D6,READ_BIT(command,2));
	DIO_Writepin(D7,READ_BIT(command,3));
	DIO_Writepin(EN,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN,LOW);
	_delay_ms(1);

}

static void LCD_write_data (u8 data)
{
	DIO_Writepin(RS,HIGH);
	//DIO_Writepin(RW,LOW);
	
	DIO_Writepin(D4,READ_BIT(data,4));
	DIO_Writepin(D5,READ_BIT(data,5));
	DIO_Writepin(D6,READ_BIT(data,6));
	DIO_Writepin(D7,READ_BIT(data,7));
	DIO_Writepin(EN,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN,LOW);
	_delay_ms(1);
	
	DIO_Writepin(D4,READ_BIT(data,0));
	DIO_Writepin(D5,READ_BIT(data,1));
	DIO_Writepin(D6,READ_BIT(data,2));
	DIO_Writepin(D7,READ_BIT(data,3));
	DIO_Writepin(EN,HIGH);
	_delay_ms(1);
	DIO_Writepin(EN,LOW);
	_delay_ms(1);
	


}

void LCD_Init(void)
{
	_delay_ms(50);
	LCD_write_command(0x02);    // to tell the MC that commands is sent in 2 parts(4_bit)
	_delay_ms(1);
	LCD_write_command(0x28);   //4-bit mode,, 2-line ,, 5*7sets
	_delay_ms(1);
	LCD_write_command(0x0c);   //display on ,, cursor on ,, blink on (you may change it to 0x0f , 0x0c , 0x0e)  
	_delay_ms(1);
	LCD_write_command(0x01);  // to clear LCD
	_delay_ms(2);
	LCD_write_command(0x06); // sets the move direction of cursor and display 
	_delay_ms(1);

}
#endif
void LCD_Clear()
{
	LCD_write_command(0x01);
}
void LCD_GoTo(u8 line,u8 x)
{
	u8 command =0x80;
	if(line==0)
	command+=x;                  //LCD_write_command(0x80+x);
	else if(line==1)
	command+=(0x40+x);
	LCD_write_command(command);  //LCD_write_command(0x80+0x40+x);
}
void LCD_Writechar(u8 ch)
{
	 LCD_write_data (ch);
	
}
void LCD_Writestring(u8*str)
{
	u8 i;
	for(i=0;str[i]!='\0';i++)
	{
		LCD_write_data (str[i]);
	}
	
}
 u8 getnum(u64 num,u8 i)
 {
	 u64 n=1;
	 u8 y;
	while(i>0)
	{
		
	n=n*10;
	i--;
	}
	return (((num%n)/(n/10))+48);
		  	 	 
 }
/*void LCD_WriteNum_D(S32 num)
{
	
	if(num==0)
	LCD_write_data('0') ;
	if(num<0)
	{
		LCD_write_data('-');
		num=(-1)*num;
	}
	u32 x=num;
	u8 y,flag=0,i=0;
	u8*str;
	while(x>0)
	{
		x=x/10;
		flag++;
		
	}
	
	while(flag)
	{
		y=getnum(num,flag);
		LCD_write_data(y) ;
		
		flag--;
	}
	
}*/
void LCD_WriteNumber(S32 num)//-2503
{
	u8 str[20];
	u8 rem,i=0;
	if (num==0)
	{
		LCD_Writechar('0');
		return;
	}
	if (num<0)
	{
		num=num*-1;
		LCD_Writechar('-');
	}
	while(num>0)
	{
		rem=num%10;
		str[i]=rem+'0';
		num=num/10;
		i++;
	}
	for (S8 j=i-1;j>=0;j--)
	{
		LCD_Writechar(str[j]);
	}
	
	
}

 void LCD_WriteNum_Binary_8bit(u8 num)
{
	S8 i;
		
	for(i=7;i>=0;i--)
	{
		LCD_write_data(((num>>i)&1)+'0');
	}
	
}
/*void LCD_Writenum_Binary(u8 num)
{
	u8 x,flag=0;
	
		
	for(x=num;x>0;x=x>>1)
	flag=flag+1;
	
	while(flag>0)
	{
		flag=flag-1;
		if(1&(num>>flag))
		LCD_write_data('1');
		else
		LCD_write_data('0');
		
	}
	if(num==0)
	LCD_Writechar('0');
		
}*/

void LCD_WriteNum_Binary(u8 num)
{
	S8 i;
	u8 flag=0;
	
	for (i=7;i>=0;i--)
	{
		if ((num>>i)&1)
		{
			flag=1;
		}
		if(flag==1)
		{
			LCD_write_data(((num>>i)&1)+'0');
		}
	}
	
}

void lCD_DEC_BIN(S32 num)
{
		LCD_Writestring("DEC:");

	LCD_WriteNum_D(num);
	LCD_Writestring("--BIN:");

	LCD_WriteNum_Binary(num);
	
}

void LCD_Writenum_4digit(S16 num)
{
	
	if(num<0)
	{
		
		LCD_write_data('-');
		num=(-1)*num;
	}
	LCD_write_data (((num%10000)/(1000))+'0');
	LCD_write_data (((num%1000)/(100))+'0');
	LCD_write_data (((num%100)/(10))+'0');
	LCD_write_data (((num%10)/(1))+'0');

}
void LCD_Writenum_2digit(u64 num)
{
	
	
	LCD_write_data (((num%100)/(10))+'0');
	LCD_write_data (((num%10)/(1))+'0');

}
void LCD_Writenum_Hex(u8 num)
{
	u8 x,y;
	x=(num/16)%16;
	if(x<=9)
	LCD_write_data(x+'0');
	else
	LCD_write_data((x-10)+'A');
	y=(num%16);
	if(y<=9)
	LCD_write_data(y+'0');
	else
	LCD_write_data((y-10)+'A');

}

/*void LCD_Writenum_Hex(u8 num)   //another solution
{
	u8 x,y;
	x=num &(0x0f);
	y=num>>4;
	
	if(y<=9)
	LCD_write_data(y+'0');
	else
	LCD_write_data((y-10)+'A');
	
	if(x<=9)
	LCD_write_data(x+'0');
	else
	LCD_write_data((x-10)+'A');
}*/

/*static u8 hexa[]={'0','1','2','3','4','5','6','7','8','9','A','B','C','D','E','F'};
void LCD_Writenum_Hex(u8 num)   //another solution
{
	u8 x,y;
	x= num % 16;
	y= num / 16;
	
	LCD_write_data(hexa[y]);
	LCD_write_data(hexa[x]);
}*/	






void LCD_Write_char_Ascii(u8 ch)
{LCD_GoTo(0,0);
	LCD_Writestring("CHAR:");
	LCD_GoTo(0,8);
LCD_Writechar(ch);
	LCD_GoTo(1,0);
LCD_Writestring("ASCI:");
	LCD_GoTo(1,8);
LCD_Writenum(ch);

}
void Lcd_Move_Str(u8*arr)
{
	u8 i=0,j=0,x,y,z;
for(x=0;arr[x]!='\0';x++);


for(y=x-1;y>=0;y--)
{ LCD_Clear();
	for(z=0;(x-y)>z;z++)
	{
		LCD_GoTo(0,z);
			

		LCD_Writechar(arr[y+z]);
		
	}
	_delay_ms(250);

	if(y==0)
	break;

}

for(i=1;i<16;i++)
{ LCD_Clear();
	LCD_GoTo(0,i);
	LCD_Writestring(arr);
	_delay_ms(110);
	
	
}
for(y=x-1;y>=0;y--)
{LCD_Clear();
	for(z=0;(x-y)>z;z++)
	{	
		LCD_GoTo(1,z);
		LCD_Writechar(arr[y+z]);
		
	}
	_delay_ms(250);


	if(y==0)
	break;

}


for(j=1;j<16;j++)
{ 	LCD_Clear();

	LCD_GoTo(1,j);
	LCD_Writestring(arr);
	_delay_ms(110);

	
}
}
void LCD_Dig_Hex_Bin(void)
{
	for(u8 n=1;n<16;n++)
	{
		LCD_GoTo(0,0);
		LCD_Writestring("BIN:");
		LCD_GoTo(1,0);
		LCD_Writenum_Binary(n);
		LCD_GoTo(0,4);
		LCD_Writechar('.');
		LCD_GoTo(1,4);
		LCD_Writechar('.');
		LCD_GoTo(0,5);
		LCD_Writestring("HEX:");
		LCD_GoTo(1,5);
		LCD_Writenum_hex(n);
		LCD_GoTo(0,9);
		LCD_Writechar('.');
		LCD_GoTo(1,9);
		LCD_Writechar('.');
		
		LCD_GoTo(0,10);
		LCD_Writestring("DIG:");
		LCD_GoTo(1,10);
		LCD_Writenum_4digit(n);
		_delay_ms(400);
		LCD_Clear();
	}
}
void LCD_CreateShape(u8 location,u8*pattern)
{
	u8 i;
	LCD_write_command(0x40+(location*8)); //to store shape in CGRAM
	for(i=0;i<8;i++)
	{
		LCD_write_data(pattern[i]); //array that create character
	}
	LCD_GoTo(0,0);  //after creating character we need to return to CGROM lcd_goto contain the command of this OR use this
	                //LCD_write_command(0x80);
}



void LCD_Write_Float(f32 v)
{
	u32 rem=0;
	f32 x=0;
	x=v*1;
	rem=x;
	rem=rem%10;
	LCD_GoTo(1,2);
	LCD_Writechar(rem+'0');
	LCD_GoTo(1,3);
	LCD_Writechar('.');
	x=v*10;
	rem=x;
	rem=rem%10;
	LCD_GoTo(1,4);
	LCD_Writechar(rem+'0');
	x=v*100;
	rem=x;
	rem=rem%10;
	LCD_GoTo(1,5);
	LCD_Writechar(rem+'0');
	x=v*1000;
	rem=x;
	rem=rem%10;
	LCD_GoTo(1,6);
	LCD_Writechar(rem+'0');
	x=v*10000;
	rem=x;
	rem=rem%10;
	LCD_GoTo(1,7);
	LCD_Writechar(rem+'0');
	
}


