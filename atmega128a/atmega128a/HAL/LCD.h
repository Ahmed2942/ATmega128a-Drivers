

#ifndef LCD_H_
#define LCD_H_

#define F_CPU 8000000UL
#include "Std_types.h"
#include "MemMap.h"
#include "util/delay.h"
#include "DIO_Interface.h"

#define _4_BIT  0 // We used it for (if condition)
#define _8_BIT  1

/*************SELECT LCD_MODE*********/

#define LCD_MODE  _4_BIT

#define  RS        PINA5    //To specify what will be written (DATA or COMMAND) (1 for DATA)(0 for COMMAND)
//#define  RW        PINC1    //To specify READ or WRITE operation (1 for read ,,0 for write)  // in KIT it is connected direct to GND
#define  EN        PINA7    //To tell the MP of LCD that there is a signal

/****************************pin_configuration FOR 8 BIT***************/

#define LCD_PORT   PA

/****************************pin_configuration FOR 4 BIT***************/

#define D4  PINA0
#define D5  PINA1
#define D6  PINA2
#define D7  PINA3

/********************from datasheet*************************/
void LCD_Init(void); 
/*THIS fun : is used to initialize the LCD by using data_sheet */
/* LCD_write_command(0x06); sets the move direction of cursor and display
 this command has 2 options --> I/D means increase or decrease DDRAM after each entry if (I/D = 1)
 this means to increase DDRAM by one, if (I/D = 1) means to decrease DDRAM by one
 ---> SH means to shift DDRAM after each entry (this means shift old data and write in the same position)*/

static void LCD_write_command (u8 command);
/*THIS fun : is used to write_command in  the LCD by using data_sheet */

static void LCD_write_data (u8 data);
/*THIS fun : is used to write_data in the LCD by using data_sheet */

void LCD_Clear();
/*THIS fun : is used to clear data from  the LCD by using data_sheet */

void LCD_GoTo(u8 line,u8 x);
/*THIS fun : is used to go to specified location to write data  in the LCD 
To go to first line you must add 0x80  (1000 0000)

To go to second line you must add 0x80 (1000 0000) + 0x40 (0100 0000) = 1100 0000
*/

void LCD_CreateShape(u8 location,u8*pattern);
/*THIS fun : is used to Create_Character in the LCD by using data_sheet 
to display shape use LCD_Writechar(location)*/

/****************************for any type of LCD***************************/
void LCD_Writechar(u8 ch);
/*THIS fun : is used to write single char in LCD*/

void LCD_Writestring(u8*str);
/*THIS fun : is used to write string in LCD*/

u8 getnum(u64 num,u8 i);
void LCD_WriteNumber(S32  num);
//void LCD_WriteNum_D(S32 num);
/*THIS fun : is used to write number in decimal in LCD*/

void LCD_WriteNum_Binary(u8 num);
/*THIS fun : is used to write number in binary according its size (10010) in LCD*/

void LCD_WriteNum_Binary_8bit(u8 num);
/*THIS fun : is used to write number in binary in 8 digits (00010010) in LCD*/

void lCD_DEC_BIN(S32 num);
/*THIS fun : is used to take a number in and print it in decimal & binary in LCD*/

void LCD_Writenum_4digit(S16 num);
 /*THIS fun : is used to write number in decimal in 4 Digits*/
 
void LCD_Writenum_2digit(u64 num);
/*THIS fun : is used to write number in decimal in 2 Digits*/

void LCD_Writenum_Hex(u8 num);
/*THIS fun : is used to write number in hex */

void LCD_Write_char_Ascii(u8 ch);
 
void Lcd_Move_Str(u8*ch);

void LCD_Dig_Hex_Bin(void);

void LCD_Write_Float(f32 v);


 #endif /* LCD_H_ */
