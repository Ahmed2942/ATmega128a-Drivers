
#include "sensors.h"

u16 POT_Volt_Read(void)
{
	u16 adc=ADC_Read(POT_CH);
	u16 volt=((u32)5000*adc)/1024;
	return volt;
}
u16 POT_Volt_Read_precentage(void)
{
	u16 adc=ADC_Read(POT_CH);
	u16 volt=((u32)100*adc)/1023;
	return volt;
}

u16 Temp_Read(void)
{
	u16 adc =ADC_Read (LM35_CH);
	u16 volt=((u32)5000*adc)/1024;
	u16 temp=volt;   //u16 temp=volt/10;---> in data sheet it said that each (1 degree = 10 mvolt),,IF we need to show 0.5 degree we not divide by 10
	return temp;
	
}
u16 Pressure_Read(void)
{
	u16 adc =ADC_Read (MPX4115_CH);
	u16 volt=((u32)5000*adc)/1024;
	u16 pressure=(((volt*2)+900)/9)-9;
	return pressure;
	
}