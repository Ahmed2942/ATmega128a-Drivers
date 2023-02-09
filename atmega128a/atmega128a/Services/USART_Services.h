

#ifndef UART_SERVICES_H_
#define UART_SERVICES_H_


#include "USART0.h"
#include "USART1.h"

void USART0_SendString(u8*str);
void USART0_ReceiveString(u8*str);
void USART0_SendNumber(u32 num);
u32 USART0_ReceiveNumber(void);
u32 USART0_ReceiveNumber2(void);

void USART1_SendString(u8*str);
void USART1_ReceiveString(u8*str);
void USART1_SendNumber(u32 num);
u32 USART1_ReceiveNumber(void);
u32 USART1_ReceiveNumber2(void);

void UART0_SendStringCheckSum(u8*str);
u8 UART0_ReceiveStringCheckSum(u8*str);


void UART1_SendStringCheckSum(u8*str);
u8 UART1_ReceiveStringCheckSum(u8*str);

void UART0_SendStringAsynch(u8*str);
/* This FUN: is used to start sending (but not finished it), 
then send to interrupt to continue and finish the task  */
void UART0_ReceiveStringAsynch(u8*str);

void UART1_SendStringAsynch(u8*str);
/* This FUN: is used to start sending (but not finished it),
then send to interrupt to continue and finish the task  */
void UART1_ReceiveStringAsynch(u8*str);

/******************************************************************************************/
u8  Endian_test(void);
/*this fun: is use to check if processor receive or send data stat with MSB or LSB*/
u16 Endian_convert_16(u16 num);
u32 Endian_convert_32(u32 num);
u32 Endian_convert2_32(u32 num);


#endif /* UART_SERVICES_H_ */