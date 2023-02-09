
#include "ADC.h"

u8 static READ_Flag=0;

void ADC_Init(ADC_Ref_type vref,ADC_Scalar_type scaler)
{
    // select v ref
	switch(vref)
	{
		
	case REF_VCC:
	SET_BIT(ADMUX,REFS0);
	CLEAR_BIT(ADMUX,REFS1);
	break;
	case REF_AREF:
	CLEAR_BIT(ADMUX,REFS0);
	CLEAR_BIT(ADMUX,REFS1);
	break;
	case RE_256V :
	SET_BIT(ADMUX,REFS0);
	SET_BIT(ADMUX,REFS1);
	break;
	}
	
	//Scaler test
	ADCSRA=ADCSRA & 0XF8;
	ADCSRA=ADCSRA |scaler;
	
	// enable 
	SET_BIT(ADCSRA,ADEN);  // we write it at the end of the function ,because if we write it at the start of the fun ADC will operate with the previous features 


}
u16 ADC_Read(ADC_Channel_type ch)
{
	//select channel
	ADMUX=ADMUX&0XE0;  //0b11100000
	ADMUX=ADMUX|ch;
	
	//start conversion
	SET_BIT(ADCSRA,ADSC);
	while((READ_BIT(ADCSRA,ADSC))); //POLLING till the end of conversion //busy wait
	
	
	return ADC;
} 

void ADC_Start_conversion(ADC_Channel_type ch)
{
	if(READ_Flag==0)
	{
		ADMUX=ADMUX&0XE0;
		ADMUX=ADMUX|ch;
		SET_BIT(ADCSRA,ADSC);
		READ_Flag=1;
	}
}

u16 ADC_Get_Read(void)
{
	while((READ_BIT(ADCSRA,ADSC)));//POLLING till the end of conversion
	READ_Flag=0;
	
	return ADC;
}

u8 ADC_Read_No_block(u16*pread)//periodic checking  //no wait
{
	if((READ_BIT(ADCSRA,ADSC))==0)
	{
		READ_Flag=0;
		*pread=ADC;
		return 1;
	}
	else
	{
		return 0;
	}
	 
	
	
}