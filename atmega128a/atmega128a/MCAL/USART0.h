 
#ifndef USART0_H_
#define USART0_H_

#include "Std_types.h"
#include "MemMap.h"
#include "Utils.h"


void USART0_Init(void);

//send or receive 8bit data
void USART0_Send(u8 data);
u8 USART0_Receive(void);

u8 USART0_ReceivePerodic(u8*pdata);
void USART0_RX_InterruptEnable(void);
void USART0_RX_InterruptDisable(void);

void USART0_TX_InterruptEnable(void);
void USART0_TX_InterruptDisable(void);

void USART0_RX_SetCallBack(void (*LocalFptr)(void));
void USART0_TX_SetCallBack(void (*LocalFptr)(void));

void USART0_SendNoBlock(u8 data);
u8 USART0_ReceiveNoBlock(void);




#endif /* USART0_H_ */