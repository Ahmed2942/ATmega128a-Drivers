
#ifndef ADC_H_
#define ADC_H_
#include "Std_types.h"
#include "MemMap.h"
#include "UTILS.h"

/***********************config**********************/
typedef enum{
	
	REF_VCC,
	REF_AREF,
	RE_256V
	
}ADC_Ref_type;
	
	
typedef enum{
	
	ADC_SCALER_2=1,
	ADC_SCALER_4,
	ADC_SCALER_8,
	ADC_SCALER_16,
	ADC_SCALER_32,
	ADC_SCALER_64,
	ADC_SCALER_128,
	
}ADC_Scalar_type;
		
typedef enum{	CH_0=0,	CH_1,	CH_2,	CH_3,	CH_4,	CH_5,	CH_6,	CH_7,}ADC_Channel_type;
/********************functs******************/
		
void ADC_Init(ADC_Ref_type vref,ADC_Scalar_type scaler);
/*this function is used to select v ref and prescaler of the ADC 
we may put vref=vcc  and scaler=64  */

u16 ADC_Read(ADC_Channel_type ch);//first scenario ---> wait till adc finish
/*this fun : is used to read ADC pin and return the reading,but it waste Mp time because it contain empty while
to solve this problem we use the next 2 functions */

void ADC_Start_conversion(ADC_Channel_type ch);
/*this fun enables the Mp to do anther thing while the ADC is reading the channel */

u16 ADC_Get_Read(void);//second scenario ---> make another thing till the adc finish, if you do the thing but adc still working ,wait it 
//if there is a remaining time the Mp will wait ,if not it returns the reading immediately 

u8 ADC_Read_No_block(u16*pread);//third scenario ---> ask if adc if it finished or not ,if no dont wait and make another thing   
/*this is another way to prevent the Mp form waiting any time and make it benefits from all time */


#endif /* ADC_H_ */