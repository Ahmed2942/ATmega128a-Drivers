 
#include "USART1.h"

u8 init_flag1=0;
static void(*UART1_RX_Fptr)(void)=NULLPTR;
static void(*UART1_TX_Fptr)(void)=NULLPTR;


void USART1_Init(void)
{
	//baud rate 9600 f=8mhz,normal speed        //you can change it by using the table in data sheet 
	UBRR1L=51;
	// normal speed
	CLEAR_BIT(UCSR1A,U2X1);
	
	//frame-> parity , data bits , stop bits
	
	/*from data sheet the initial values are: parity--> no parity,,,, data bits--> 8 bits,,, stop bits-->1
	  so we do not need to change them */
	
	
	//enable transmitter and receiver  
	SET_BIT(UCSR1B,TXEN1);
	SET_BIT(UCSR1B,RXEN1);
	init_flag1=1;
}


void USART1_Send(u8 data)
{
	if (init_flag1==1)
	{
		while(!READ_BIT(UCSR1A,UDRE1));// this means wait until the buffer to be empty then put data on it ,,NOTE: this bit is 1 if buffer is empty and 0 if buffer is not empty
		UDR1=data;
	}
	
}

u8 USART1_Receive(void)
{
	while(!READ_BIT(UCSR1A,RXC1)); // this means wait until the buffer has data then read data from it ,,NOTE: this bit is 0 if buffer is empty and 1 if buffer has unread data

	return UDR1;
}


u8 USART1_ReceivePerodic(u8*pdata) //periodic check
{
	if (READ_BIT(UCSR1A,RXC1))
	{
		*pdata=UDR1;
		return 1;
	}
return 0;
}

// use this function in interrupt 
void USART1_SendNoBlock(u8 data)
{
	UDR1=data;
}

// use this function in interrupt 
u8 USART1_ReceiveNoBlock(void)
{
	return UDR1;
}


void USART1_RX_InterruptEnable(void)
{
	SET_BIT(UCSR1B,RXCIE1);
}

void USART1_RX_InterruptDisable(void)
{
	CLEAR_BIT(UCSR1B,RXCIE1);
}

void USART1_TX_InterruptEnable(void)
{
	SET_BIT(UCSR1B,TXCIE1);
}

void USART1_TX_InterruptDisable(void)
{
	CLEAR_BIT(UCSR1B,TXCIE1);
}

void USART1_RX_SetCallBack(void (*LocalFptr)(void))
{
	UART1_RX_Fptr = LocalFptr;
}

void USART1_TX_SetCallBack(void (*LocalFptr)(void))
{
	UART1_TX_Fptr = LocalFptr;
}


ISR(USART1_RX_vect)
{
	if (UART1_RX_Fptr!=NULLPTR)
	{
		UART1_RX_Fptr();
	}
}

ISR(USART1_TX_vect)
{
	if (UART1_TX_Fptr!=NULLPTR)
	{
		UART1_TX_Fptr();
	}
}	
	

 
