
#ifndef USART1_H_
#define USART1_H_

#include "Std_types.h"
#include "MemMap.h"
#include "Utils.h"


void USART1_Init(void);

//send or receive 8bit data
void USART1_Send(u8 data);
u8 USART1_Receive(void);

u8 USART1_ReceivePerodic(u8*pdata);
void USART1_RX_InterruptEnable(void);
void USART1_RX_InterruptDisable(void);

void USART1_TX_InterruptEnable(void);
void USART1_TX_InterruptDisable(void);

void USART1_RX_SetCallBack(void (*LocalFptr)(void));
void USART1_TX_SetCallBack(void (*LocalFptr)(void));

void USART1_SendNoBlock(u8 data);
u8 USART1_ReceiveNoBlock(void);







#endif /* USART1_H_ */