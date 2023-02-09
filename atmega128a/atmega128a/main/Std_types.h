#ifndef STD_TYPES_H_
#define STD_TYPES_H_

/*************** STD_TYPES.h ******************/

typedef unsigned char u8;
typedef signed char s8;
typedef char c8;

typedef unsigned short u16;
typedef signed short s16;

typedef unsigned long u32;
typedef signed long s32;

typedef unsigned long long u64;
typedef signed long long s64;

typedef unsigned char* p8;
typedef unsigned short* p16;
typedef unsigned long* p32;
typedef unsigned long long* p64;

typedef float f32;
typedef double f64;

#define NULLPTR ((void*)0)

typedef enum {
	NULL,
	OK,
	NOK,
	OUT_OF_RANGE
} Error_type;

typedef enum {
	FALSE,
	TRUE
} bool_type;

#define MAX_U8 ((u8)255)
#define MIN_U8 ((u8)0)

#define MAX_S8 ((s8)127)
#define MIN_S8 ((s8)-128)

#define MAX_U16 ((u16)65535)
#define MIN_U16 ((u16)0)

#define MAX_S16 ((s16)32767)
#define MIN_S16 ((s16)-32768)

#define MAX_U32 ((u32)4294967295)
#define MIN_U32 ((u32)0)

#define MAX_S32 ((s32)2147483647)
#define MIN_S32 ((s32)-2147483648)

#define MAX_U64 ((u64)18446744073709551615)
#define MIN_U64 ((u64)0)

#define MAX_S64 ((s64)9223372036854775807)
#define MIN_S64 ((s64)-9223372036854775808)



#endif /* STD_TYPES_H_ */