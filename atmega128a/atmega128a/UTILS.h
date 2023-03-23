 
#include "Std_types.h"

#ifndef UTILS_H_
#define UTILS_H_


/*** Called Macro Like a Func ****/
#define SET_BIT(REG,BIT)           REG=REG|(1<<BIT)
#define CLEAR_BIT(REG,BIT)         REG=REG&(~(1<<BIT))
#define READ_BIT(REG,BIT)          (1&(REG>>BIT))
#define TOGGLE_BIT(REG,BIT)        REG=(REG^(1<<BIT))
#define WRITE_BIT(REG,BIT,VALUE)   REG=(REG&(~(1<<BIT))|(REG|(VALUE<<BIT)

#define ASSIGN_REG(REG,VALUE)     (REG=VALUE)
#define SET_REG(REG) (REG=0xff)
#define CLR_REG(REG) (REG=0)
#define TOG_REG(REG) (REG=REG^0xff)

/******** funct ******/
/*
u8 SET_BIT_func(u8 port ,u8 bit)
{
	port=port|(1<<bit);
	
	return port;
}

void SET_BIT_funct(u8* reg ,u8 bit)
{
	*reg|=(1<<bit);
}
*/



#endif /* UTILS_H_ */