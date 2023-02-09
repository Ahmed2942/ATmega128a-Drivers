#define F_CPU 1000000UL
#include "util/delay.h"
#include "MemMap.h"
#include "Std_types.h"
#include "UTILS.h"
#include "DIO_Interface.h"

#include "ADC.h"
#include "Sensors.h"
#include "LCD.h"

int main(void)
{
   DIO_Init();
   LCD_Init();
   ADC_Init(REF_VCC,ADC_SCALER_64);
	u16 temperature,pressure,password;
    while (1) 
    {
		temperature=Temp_Read();
		LCD_GoTo(1,2);
		LCD_WriteNumber(temperature/10);
		LCD_Writechar('.');
		LCD_WriteNumber(temperature%10);
    }
}

