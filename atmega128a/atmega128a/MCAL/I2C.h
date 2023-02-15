#ifndef I2C_H_					/* Define library H file if not defined */
#define I2C_H_

#define F_CPU 16000000UL						 /* Define CPU clock Frequency e.g. here its 16MHz */
#include <util/delay.h>							 /* Include inbuilt defined Delay header file */
/* the CPU clock frequency in the slave must be at least 16 times higher than the SCL frequency */
#define SCL_CLK 100000L							 /* Define SCL clock frequency */
#define BITRATE	((F_CPU/SCL_CLK)-16)/(2)		 /* Define bit rate */

/* Master Functions */
void I2C_Master_Init();							/* I2C initialize function */
u8  I2C_Start(u8 write_address);				/* I2C start function */
void I2C_Start_Wait(u8 write_address);			/* I2C start wait function */
u8  I2C_Repeated_Start(u8 read_address);		/* I2C repeated start function */
void I2C_Stop();								/* I2C stop function */
u8  I2C_Write(u8 data);							/* I2C write function */
u8 I2C_Read_Ack();								/* I2C read ack function */
u8 I2C_Read_Nack();								/* I2C read nack function */

/* Slave Functions */
void I2C_Slave_Init(u8 slave_address);		/* I2C slave initialize function with Slave address */
u8 I2C_Slave_Listen();						/* I2C slave listen function */
u8 I2C_Slave_Transmit(u8 data);				/* I2C slave transmit function */
u8 I2C_Slave_Receive();						/* I2C slave receive function */

/////////////////////////////////////////////////////////////////////////////////////////////////////////////////

/* Copyright (c) 2002, Marek Michalkiewicz
   Copyright (c) 2005, 2007 Joerg Wunsch
   All rights reserved.

   Redistribution and use in source and binary forms, with or without
   modification, are permitted provided that the following conditions are met:

   * Redistributions of source code must retain the above copyright
     notice, this list of conditions and the following disclaimer.

   * Redistributions in binary form must reproduce the above copyright
     notice, this list of conditions and the following disclaimer in
     the documentation and/or other materials provided with the
     distribution.

   * Neither the name of the copyright holders nor the names of
     contributors may be used to endorse or promote products derived
     from this software without specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE. */

/* copied from: Id: avr/twi.h,v 1.4 2004/11/01 21:19:54 arcanum Exp */

/*
  Mnemonics:
  <br>TW_MT_xxx - master transmitter
  <br>TW_MR_xxx - master receiver
  <br>TW_ST_xxx - slave transmitter
  <br>TW_SR_xxx - slave receiver
*/

/* Master */
/* start condition transmitted */
#define TW_START		0x08

/* repeated start condition transmitted */
#define TW_REP_START		0x10

/* Master Transmitter */
/* SLA+W transmitted, ACK received */
#define TW_MT_SLA_ACK		0x18

/* SLA+W transmitted, NACK received */
#define TW_MT_SLA_NACK		0x20

/* data transmitted, ACK received */
#define TW_MT_DATA_ACK		0x28

/* data transmitted, NACK received */
#define TW_MT_DATA_NACK		0x30

/* arbitration lost in SLA+W or data */
#define TW_MT_ARB_LOST		0x38

/* Master Receiver */
/* arbitration lost in SLA+R or NACK */
#define TW_MR_ARB_LOST		0x38

/* SLA+R transmitted, ACK received */
#define TW_MR_SLA_ACK		0x40

/* SLA+R transmitted, NACK received */
#define TW_MR_SLA_NACK		0x48

/* data received, ACK returned */
#define TW_MR_DATA_ACK		0x50

/* data received, NACK returned */
#define TW_MR_DATA_NACK		0x58

/* Slave Transmitter */
/* SLA+R received, ACK returned */
#define TW_ST_SLA_ACK		0xA8

/* arbitration lost in SLA+RW, SLA+R received, ACK returned */
#define TW_ST_ARB_LOST_SLA_ACK	0xB0

/* data transmitted, ACK received */
#define TW_ST_DATA_ACK		0xB8

/* data transmitted, NACK received */
#define TW_ST_DATA_NACK		0xC0

/* last data byte transmitted, ACK received */
#define TW_ST_LAST_DATA		0xC8

/* Slave Receiver */
/* SLA+W received, ACK returned */
#define TW_SR_SLA_ACK		0x60

/* arbitration lost in SLA+RW, SLA+W received, ACK returned */
#define TW_SR_ARB_LOST_SLA_ACK	0x68

/* general call received, ACK returned */
#define TW_SR_GCALL_ACK		0x70

/* arbitration lost in SLA+RW, general call received, ACK returned */
#define TW_SR_ARB_LOST_GCALL_ACK 0x78

/* data received, ACK returned */
#define TW_SR_DATA_ACK		0x80

/* data received, NACK returned */
#define TW_SR_DATA_NACK		0x88

/* general call data received, ACK returned */
#define TW_SR_GCALL_DATA_ACK	0x90

/* general call data received, NACK returned */
#define TW_SR_GCALL_DATA_NACK	0x98

/* stop or repeated start condition received while selected */
#define TW_SR_STOP		0xA0

/* Misc */

/* no state information available */
#define TW_NO_INFO		0xF8

/* illegal start or stop condition */
#define TW_BUS_ERROR		0x00


#endif											/* I2C_H_ */