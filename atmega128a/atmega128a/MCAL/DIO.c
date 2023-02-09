
#include "DIO_Interface.h"
#include "MemMap.h"

 void DIO_Init(void)
 {
	 DIO_Pin_type i;
	 for(i=PINA0;i<TOTAL_PINS;i++)
	 DIO_Initpin(i,PinStatus[i]);
 }

 void DIO_Initpin(DIO_Pin_type pin,DIO_Pinstastus_type status)
 {
	 
	 DIO_Port_type PORT=pin/8;
	 u8 pin_num=pin%8;
	 switch(status)
	 {
		 case OUTPUT:
		 switch(PORT)
		 {
			 case PA:
			 SET_BIT(DDRA,pin_num);
			 break;
			 case PB:
			 SET_BIT(DDRB,pin_num);
			 break;
			 case PC:
			 SET_BIT(DDRC,pin_num);
			 break;
			 case PD:
			 SET_BIT(DDRD,pin_num);
			 break;
			 case PE:
			 SET_BIT(DDRE,pin_num);
			 break;
			 case PF:
			 SET_BIT(DDRF,pin_num);
			 break;
			 case PG:
			 SET_BIT(DDRG,pin_num);
			 break;
			 
		 }
		 break;
		 
		 case INFREE:
		 switch(PORT)
		 {
			 case PA:
			 CLEAR_BIT(DDRA,pin_num);
			 CLEAR_BIT(PORTA,pin_num);
			 break;
			 
			 case PB:
			 CLEAR_BIT(DDRB,pin_num);
			 CLEAR_BIT(PORTB,pin_num);
			 break;
			 
			 case PC:
			 CLEAR_BIT(DDRC,pin_num);
			 CLEAR_BIT(PORTC,pin_num);
			 break;
			 
			 case PD:
			 CLEAR_BIT(DDRD,pin_num);
			 CLEAR_BIT(PORTD,pin_num);
			 break;
			 
			 case PE:
			 CLEAR_BIT(DDRE,pin_num);
		     CLEAR_BIT(PORTE,pin_num);
		     break;
			 
			 case PF:
		     CLEAR_BIT(DDRF,pin_num);
		     CLEAR_BIT(PORTF,pin_num);
		     break;
			 
			 case PG:
			 CLEAR_BIT(DDRG,pin_num);
			 CLEAR_BIT(PORTG,pin_num);
			 break;
		 }
		 break;
		 
		 case INPULL:
		 switch(PORT)
		 {
			 case PA:
			 CLEAR_BIT(DDRA,pin_num);
			 SET_BIT(PORTA,pin_num);
			 break;
			 
			 case PB:
			 CLEAR_BIT(DDRB,pin_num);
			 SET_BIT(PORTB,pin_num);
			 break;
			 
			 case PC:
			 CLEAR_BIT(DDRC,pin_num);
			 SET_BIT(PORTC,pin_num);
			 break;
			 
			 case PD:
			 CLEAR_BIT(DDRD,pin_num);
			 SET_BIT(PORTD,pin_num);
			 break;
			 
			 case PE:
			 CLEAR_BIT(DDRE,pin_num);
			 SET_BIT(PORTE,pin_num);
			 break;
			 
			 case PF:
			 CLEAR_BIT(DDRF,pin_num);
			 SET_BIT(PORTF,pin_num);
			 break;
			 
			 case PG:
			 CLEAR_BIT(DDRG,pin_num);
			 SET_BIT(PORTG,pin_num);
			 break;
			 
		 }
		 break;		 
	 }	 
 }

 void DIO_Writepin(DIO_Pin_type pin,DIO_Voltagetype volt)
 {
	 DIO_Port_type PORT=pin/8;
	 u8 pin_num=pin%8;
	 if(volt==HIGH)
	 {
		 switch(PORT)
		 {
			 case PA:
			 SET_BIT(PORTA,pin_num);
			 break;
			 case PB:
			 SET_BIT(PORTB,pin_num);
			 break;
			 case PC:
			 SET_BIT(PORTC,pin_num);
			 break;
			 case PD:
			 SET_BIT(PORTD,pin_num);
			 break;
			 case PE:
			 SET_BIT(PORTE,pin_num);
			 break;
			 case PF:
			 SET_BIT(PORTF,pin_num);
			 break;
			 case PG:
			 SET_BIT(PORTG,pin_num);
			 break;
			 
		 }
	 }
	 else if (volt==LOW)
	 {
		 switch(PORT)
		 {
			 case PA:
			 CLEAR_BIT(PORTA,pin_num);
			 break;
			 case PB:
			 CLEAR_BIT(PORTB,pin_num);
			 break;
			 case PC:
			 CLEAR_BIT(PORTC,pin_num);
			 break;
			 case PD:
			 CLEAR_BIT(PORTD,pin_num);
			 break;
			 case PE:
			 CLEAR_BIT(PORTE,pin_num);
			 break;
			 case PF:
			 CLEAR_BIT(PORTF,pin_num);
			 break;
			 case PG:
			 CLEAR_BIT(PORTG,pin_num);
			 break;
		 }
		 
		 
	 }
 }

 DIO_Voltagetype DIO_Readpin(DIO_Pin_type pin)
 {
	 DIO_Port_type PORT=pin/8;
	 u8 pin_num=pin%8;
	 static DIO_Voltagetype volt;
	 switch(PORT)
	 {
		 case PA:
		 volt=READ_BIT(PINA,pin_num);
		 break;
		 case PB:
		 volt=READ_BIT(PINB,pin_num);
		 break;
		 case PC:
		 volt=READ_BIT(PINC,pin_num);
		 break;
		 case PD:
		 volt=READ_BIT(PIND,pin_num);
		 break;
		 case PE:
		 volt=READ_BIT(PINE,pin_num);
		 break;
		 case PF:
		 volt=READ_BIT(PINF,pin_num);
		 break;
		 case PG:
		 volt=READ_BIT(PING,pin_num);
		 break; 
	 }
	 return volt;
 }

 void DIO_Togglepin(DIO_Pin_type pin)
 {
	 DIO_Port_type PORT=pin/8;
	 u8 pin_num=pin%8;
	 switch(PORT)
	 {
		 case PA:
		 TOGGLE_BIT(PORTA,pin_num);
		 break;
		 case PB:
		 TOGGLE_BIT(PORTB,pin_num);
		 break;
		 case PC:
		 TOGGLE_BIT(PORTC,pin_num);
		 break;
		 case PD:
		 TOGGLE_BIT(PORTD,pin_num);
		 break;
		 case PE:
		 TOGGLE_BIT(PORTE,pin_num);
		 break;
		 case PF:
		 TOGGLE_BIT(PORTF,pin_num);
		 break;
		 case PG:
		 TOGGLE_BIT(PORTG,pin_num);
		 break;
	 }
	 
 }

 void DIO_Writeport(DIO_Port_type PORT,u8 value)
 {
	 switch(PORT)
	 {
		 case PA:
		 PORTA=value;
		 break;
		 case PB:
		 PORTB=value;
		 break;
		 case PC:
		 PORTC=value;
		 break;
		 case PD:
		 PORTD=value;
		 break;
		 case PE:
		 PORTE=value;
	     break;
		 case PF:
	     PORTF=value;
	     break;
	     case PG:
         PORTG=value;
	     break;
	 }
 }
 
 u8 DIO_Readport(DIO_Port_type PORT)
 {
	 static u8 value;
	 switch(PORT)
	 {
		 case PA:
		 value=PINA;
		 break;
		 case PB:
		 value=PINB;
		 break;
		 case PC:
		 value=PINC;
		 break;
		 case PD:
		 value=PIND;
		 break;
		 case PE:
		 value=PINE;
		 break;
		 case PF:
		 value=PINF;
		 break;
		 case PG:
		 value=PING;
		 break;
		 
	 }
	 return value;
 }
 
 
 
 


 
 

