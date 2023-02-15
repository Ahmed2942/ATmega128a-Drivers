#include "USART_Services.h"

void USART0_SendString (u8*str)
{
	u8 i;
	for (i=0;str[i];i++)
	{
		USART0_Send(str[i]);
	}

}

void USART1_SendString (u8*str)
{
	u8 i;
	for (i=0;str[i];i++)
	{
		USART1_Send(str[i]);
	}

}

void USART0_ReceiveString(u8*str)
{
	u8 i=0;
	str[i]=USART0_Receive();
	for (; str[i]!=';' ;)     // 13 is the ascii of ENTER   ------->try ascii of ";"
	{
		i++;
		str[i]=USART0_Receive();
		
	}
	str[i]=0;	
}
void USART1_ReceiveString(u8*str)
{
	u8 i=0;
	str[i]=USART1_Receive();
	for (; str[i]!=';' ;)     // 13 is the ascii of ENTER   ------->try ascii of ";"
	{
		i++;
		str[i]=USART1_Receive();
		
	}
	str[i]=0;
}

void USART0_SendNumber(u32 num)
{
	USART0_Send((u8)num);
	USART0_Send((u8)(num>>8));
	USART0_Send((u8)(num>>16));
	USART0_Send((u8)(num>>24));
}

void USART1_SendNumber(u32 num)
{
	USART1_Send((u8)num);
	USART1_Send((u8)(num>>8));
	USART1_Send((u8)(num>>16));
	USART1_Send((u8)(num>>24));
}


void USART0_SendNumber2(u32 num)
{
	u8*p=&num;
	USART0_Send(p[0]);
	USART0_Send(p[1]);
	USART0_Send(p[2]);
	USART0_Send(p[3]);
}
void USART1_SendNumber2(u32 num)
{
	u8*p=&num;
	USART1_Send(p[0]);
	USART1_Send(p[1]);
	USART1_Send(p[2]);
	USART1_Send(p[3]);
}

u32 USART0_ReceiveNumber(void)
{
	u32 num;
	u8 b0=USART0_Receive();
	u8 b1=USART0_Receive();
	u8 b2=USART0_Receive();
	u8 b3=USART0_Receive();
	
	num=(u32)b0 | (u32)b1<<8 | (u32)b2<<16 | (u32)b3<<24;
	
	return num;	
}

u32 USART1_ReceiveNumber(void)
{
	u32 num;
	u8 b0=USART1_Receive();
	u8 b1=USART1_Receive();
	u8 b2=USART1_Receive();
	u8 b3=USART1_Receive();
	
	num=(u32)b0 | (u32)b1<<8 | (u32)b2<<16 | (u32)b3<<24;
	
	return num;
}

u32 USART0_ReceiveNumber2(void)
{
	u32 num;
	u8*p=&num;
	p[0]=USART0_Receive();
	p[1]=USART0_Receive();
	p[2]=USART0_Receive();
	p[3]=USART0_Receive();
	
	return num;
	
}
u32 USART1_ReceiveNumber2(void)
{
	u32 num;
	u8*p=&num;
	p[0]=USART1_Receive();
	p[1]=USART1_Receive();
	p[2]=USART1_Receive();
	p[3]=USART1_Receive();
	
	return num;
	
}

//#this fun is used to check num of char in string and their sum to make validation in the massage

void USART0_SendStringCheckSum(u8*str)
{
	u8 i,len=0;
	u16 sum=0;
	for (len=0;str[len];len++);
	USART0_Send(len);
	for (i=0;i<len;i++)
	{
		USART0_Send(str[i]);
		sum=sum+str[i];
	}
	USART0_Send((u8)sum);
	USART0_Send((u8)(sum>>8));

}
void USART1_SendStringCheckSum(u8*str)
{
	u8 i,len=0;
	u16 sum=0;
	for (len=0;str[len];len++);
	USART1_Send(len);
	for (i=0;i<len;i++)
	{
		USART1_Send(str[i]);
		sum=sum+str[i];
	}
	USART1_Send((u8)sum);
	USART1_Send((u8)(sum>>8));

}

// #first byte---> length ,#second bytes-----> data ,#third 2 btyes ----> sum of chars in the string

u8 USART0_ReceiveStringCheckSum(u8*str)
{
	u8 i,len,b0,b1;
	u16 sum_calc=0,sum_rec=0;  //volatile
	len=USART0_Receive();
	for (i=0;i<len;i++)
	{
		str[i]=USART0_Receive();
		sum_calc+=str[i];
	}
	b0=USART0_Receive();
	b1=USART0_Receive();
	sum_rec=(u16)b0|(u16)b1<<8;
	str[i]=0;
	if (sum_rec==sum_calc)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

u8 USART1_ReceiveStringCheckSum(u8*str)
{
	u8 i,len,b0,b1;
	u16 sum_calc=0,sum_rec=0;  //volatile
	len=USART1_Receive();
	for (i=0;i<len;i++)
	{
		str[i]=USART1_Receive();
		sum_calc+=str[i];
	}
	b0=USART1_Receive();
	b1=USART1_Receive();
	sum_rec=(u16)b0|(u16)b1<<8;
	str[i]=0;
	if (sum_rec==sum_calc)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}


static u8*Tx0_str[20]; //this become array of pointers to enable us to send many strings one after the other 
static void FUNC_TX0(void);
static void FUNC_RX0(void);
static u8 j0=0;
static u8*Rx0_str;

//this function need more modification to operate
void USART0_SendStringAsynch(u8*str)
{
	//UART_Send(str[0]);
	Tx0_str[j0]=str;
	USART0_TX_SetCallBack(FUNC_TX0);
	USART0_TX_InterruptEnable();
	j0++;
}

static void FUNC_TX0(void)
{
	static u8 i=1,k=0;
	if (Tx0_str[k][i]!=0)
	{
		USART0_SendNoBlock(Tx0_str[k][i]);
		i++;
	}
	else
	{
		i=1;
		k++;
	}
}


void USART0_ReceiveStringAsynch(u8*str)
{
	
    USART0_RX_SetCallBack(FUNC_RX0);
	USART0_RX_InterruptEnable();
	Rx0_str=str;
	
}

static void FUNC_RX0(void)
{
	static u8 i=0;
	Rx0_str[i]=USART0_ReceiveNoBlock();
	i++;
	
}

static u8 flag=0;

void USART0_BCM_Runnabe(u8*str)
{
	static u8 i=0;
	
	if (flag==1)
	{
		if (str[i]!=0)
		{
			USART0_SendNoBlock(str[i]);
			i++;
			flag=0;
		}
		
	}
}

//static void FUNC0_TX(void)
//{
	//flag=1;
//}
/********************************************************************/

static u8*Tx1_str[20]; //this become array of pointers to enable us to send many strings one after the other
static void FUNC_TX1(void);
static void FUNC_RX1(void);
static u8 j1=0;
static u8*Rx1_str;


void USART1_SendStringAsynch(u8*str)
{
	
	//UART_Send(str[0]);
	Tx1_str[j1]=str;
	USART1_TX_SetCallBack(FUNC_TX1);
	USART1_TX_InterruptEnable();
	j1++;
}

static void FUNC_TX1(void)
{
	static u8 i=1,k=0;
	if (Tx1_str[k][i]!=0)
	{
		USART1_SendNoBlock(Tx1_str[k][i]);
		i++;
	}
	else
	{
		i=1;
		k++;
	}
}


void USART1_ReceiveStringAsynch(u8*str)
{
	
	USART1_RX_SetCallBack(FUNC_RX1);
	USART1_RX_InterruptEnable();
	Rx1_str=str;
	
}

static void FUNC_RX1(void)
{
	static u8 i=0;
	Rx1_str[i]=USART1_ReceiveNoBlock();
	i++;
	
}

static u8 flag1=0;

void USART1_BCM_Runnabe(u8*str)
{
	static u8 i=0;
	
	if (flag1==1)
	{
		if (str[i]!=0)
		{
			USART1_SendNoBlock(str[i]);
			i++;
			flag1=0;
		}
		
	}
}

//static void FUNC1_TX(void)
//{
	//flag1=1;
//}

/*********************************************************************************/

#define  LITTLE_ENDIAN 0
#define  BIG_ENDIAN 1

// this fun is used to check if the system is little or big endian
u8 Endian_test(void)
{
	u32 num=1;
	u8*p=&num;
	
	if (*p==1)
	{
		return LITTLE_ENDIAN;
	}
	else
	{
		return BIG_ENDIAN;
	}
}

u16 Endian_convert_16(u16 num)
{
	
	u16 n=(num<<8)|(num>>8);
	return n;	
}
u32 Endian_convert_32(u32 num)
{
	u8*p=&num;
	u8 temp;
	
	temp=p[0];
	p[0]=p[3];
	p[3]=temp;
	
	temp=p[1];
	p[1]=p[2];
	p[2]=temp;
	 
	return num;
}

//OR

u32 Endian_convert2_32(u32 num)
{
	u32 n;
	
	u32 b1=(num>>24);
	u32 b4=(num<<24);
	u32 b2=(num>>8)&(0x0000ff00);
	u32 b3=(num<<8)&(0x00ff0000);
	
	n=b1|b2|b3|b4;
	
	return n;
}