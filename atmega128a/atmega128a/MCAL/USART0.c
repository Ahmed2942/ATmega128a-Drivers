 
#include "USART0.h"

u8 init_flag0=0;
static void(*UART0_RX_Fptr)(void)=NULLPTR;
static void(*UART0_TX_Fptr)(void)=NULLPTR;


void USART0_Init(void)
{
	//baud rate 9600 f=8mhz,normal speed        //you can change it by using the table in data sheet 
	UBRR0L=51;
	// normal speed
	CLEAR_BIT(UCSR0A,U2X0);
	
	//frame-> parity , data bits , stop bits
	
	/*from data sheet the initial values are: parity--> no parity,,,, data bits--> 8 bits,,, stop bits-->1
	  so we do not need to change them */
	
	
	//enable transmitter and receiver  
	SET_BIT(UCSR0B,TXEN0);
	SET_BIT(UCSR0B,RXEN0);
	init_flag0=1;
}


void USART0_Send(u8 data)
{
	if (init_flag0==1)
	{
		while(!READ_BIT(UCSR0A,UDRE0));// this means wait until the buffer to be empty then put data on it ,,NOTE: this bit is 1 if buffer is empty and 0 if buffer is not empty
		UDR0=data;
	}
	
}

u8 USART0_Receive(void)
{
	while(!READ_BIT(UCSR0A,RXC0)); // this means wait until the buffer has data then read data from it ,,NOTE: this bit is 0 if buffer is empty and 1 if buffer has unread data

	return UDR0;
}


u8 USART0_ReceivePerodic(u8*pdata) //periodic check
{
	if (READ_BIT(UCSR0A,RXC0))
	{
		*pdata=UDR0;
		return 1;
	}
return 0;
}

// use this function in interrupt 
void USART0_SendNoBlock(u8 data)
{
	UDR0=data;
}
// use this function in interrupt 
u8 USART0_ReceiveNoBlock(void)
{
	return UDR0;
}


void USART0_RX_InterruptEnable(void)
{
	SET_BIT(UCSR0B,RXCIE0);
}

void USART0_RX_InterruptDisable(void)
{
	CLEAR_BIT(UCSR0B,RXCIE0);
}

void USART0_TX_InterruptEnable(void)
{
	SET_BIT(UCSR0B,TXCIE0);
}

void USART0_TX_InterruptDisable(void)
{
	CLEAR_BIT(UCSR0B,TXCIE0);
}

void USART0_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART0_RX_Fptr = LocalFptr;
}

void USART0_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART0_TX_Fptr = LocalFptr;
}


ISR(USART0_RX_vect)
{
	if (UART0_RX_Fptr!=NULLPTR)
	{
		UART0_RX_Fptr();
	}
}

ISR(USART0_TX_vect)
{
	if (UART0_TX_Fptr!=NULLPTR)
	{
		UART0_TX_Fptr();
	}
}	
	



