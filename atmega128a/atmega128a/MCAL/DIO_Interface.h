 
#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_


#include "Std_types.h"
#include "MemMap.h"
#include "UTILS.h"

/******************************enums**************************/
typedef enum{
	PINA0=0,
	PINA1,
	PINA2,
	PINA3,
	PINA4,
	PINA5,
	PINA6,
	PINA7,
	
	PINB0,
	PINB1,
	PINB2,
	PINB3,
	PINB4,
	PINB5,
	PINB6,
	PINB7,
	
	PINC0,
	PINC1,
	PINC2,
	PINC3,
	PINC4,
	PINC5,
	PINC6,
	PINC7,
	
	PIND0,
	PIND1,
	PIND2,
	PIND3,
	PIND4,
	PIND5,
	PIND6,
	PIND7,
	
	PINE0,
	PINE1,
	PINE2,
	PINE3,
	PINE4,
	PINE5,
	PINE6,
	PINE7,
	
	PINF0,
	PINF1,
	PINF2,
	PINF3,
	PINF4,
	PINF5,
	PINF6,
	PINF7,
	
	PING0,
	PING1,
	PING2,
	PING3,
	PING4=52,
	
	TOTAL_PINS=53,
	
}DIO_Pin_type;

typedef enum{
	OUTPUT=0,
	INFREE,
	INPULL,
}DIO_Pinstastus_type;


typedef enum
{
	PA=0,
	PB,
	PC,
	PD,
	PE,
	PF,
	PG
	
}DIO_Port_type;

typedef enum{         //we use it if pin is initialized as OUTPUT pin
	LOW=0,
	HIGH
	
}DIO_Voltagetype;

/******************************functions**************************/

//extern means that fun can be seen outside the file (it is the opposite of static)

extern const DIO_Pinstastus_type PinStatus[TOTAL_PINS]; //declaration of the array which used in DIO_Lcfg

extern void DIO_Init(void);
// it is used to make initialization for DIO

extern void DIO_Initpin(DIO_Pin_type pin,DIO_Pinstastus_type status);
/*it initialize each pin with special status without using DIO_Lcfg
we need to calculate the port by pin/8 (8 is changed if the micro changed) and pin_num(0-->7) by pin%8
problem in this fun: we need to initialize each pin (one by one)--> to solve this problem :we use DIO_Init with DIO_Lcfg (configration file)*/

extern void DIO_Writepin(DIO_Pin_type pin,DIO_Voltagetype volt);
/*it is used to write value(0 or 1) in the pin
we need to calculate the port by pin/8 (8 is changed if the micro changed) and pin_num(0-->7) by pin%8  */

extern DIO_Voltagetype DIO_Readpin(DIO_Pin_type pin);
/*it is used to read value(0 or 1) from the pin
we need to calculate the port by pin/8 (8 is changed if the micro changed) and pin_num(0-->7) by pin%8  */

extern void DIO_Togglepin(DIO_Pin_type pin);
//it is used to toggle pins

extern void DIO_Writeport(DIO_Port_type PORT,u8 value);
//it use to write value in the hole port

extern u8 DIO_Readport(DIO_Port_type PORT);
// it is used to read value from the hole port




#endif /* DIO_INTERFACE_H_ */