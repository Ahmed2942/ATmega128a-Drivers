#define F_CPU 1000000UL
#include "util/delay.h"
#include "MemMap.h"
#include "Std_types.h"
#include "UTILS.h"
#include "DIO_Interface.h"

#include "ADC.h"
#include "Sensors.h"

int main(void)
{
   DIO_Init();
   ADC_Init(REF_VCC,ADC_SCALER_64);
	u16 temperature,pressure,password;
    while (1) 
    {
		
    }
}

