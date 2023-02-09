/*
 * IncFile1.h
 *
 * Created: 10/17/2020 12:31:58 PM
 *  Author: iT-User
 */ 


#ifndef INCFILE1_H_
#define INCFILE1_H_

#include "UTILS.h"
#include "Std_types.h"
#include "DIO_Interface.h"
#include "ADC.h" 

#define POT_CH   CH_6
#define LM35_CH  CH_0
#define MPX4115_CH  CH_7

u16 POT_Volt_Read(void);
/*THIS FUN: is used to to return volt in (mv) instead to return  adc reading
to call this fun in main use:
-----------------------------
volt=POT_Volt_Read();
LCD_WriteNum_D(volt/1000);
LCD_Writechar('.');
LCD_WriteNum_D(volt%1000);
-----------------------------
because the fun returns num in mv and we need to print it in volt*/

u16 POT_Volt_Read_precentage(void);

u16 Temp_Read(void);   //LM35 sensor
/*THIS FUN: is used to to return temp degree  instead to return  adc reading
to call this fun in main use:
-----------------------------
j=Temp_Read();
LCD_WriteNum_D(j/10);
LCD_Writechar('.');
LCD_WriteNum_D(j%10);

*/

u16 Pressure_Read(void);//mpx4115 sensor

#endif /* INCFILE1_H_ */