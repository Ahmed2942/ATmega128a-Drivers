/*
  twi.h - TWI/I2C library for Wiring & Arduino
  Copyright (c) 2006 Nicholas Zambetti.  All right reserved.

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
*/

#ifndef twi_h
#define twi_h

#include "DIO_Interface.h"

#define SCL PIND1
#define SDA PIND1

#ifndef TWI_FREQ
#define TWI_FREQ 100000UL
#endif

#ifndef TWI_BUFFER_LENGTH
#define TWI_BUFFER_LENGTH 32
#endif

#define TWI_READY 0
#define TWI_MRX   1
#define TWI_MTX   2
#define TWI_SRX   3
#define TWI_STX   4

void twi_init(void);
void twi_disable(void);
void twi_setAddress(u8);
void twi_setFrequency(u32);
u8 twi_readFrom(u8, u8*, u8, u8);
u8 twi_writeTo(u8, u8*, u8, u8, u8);
u8 twi_transmit(const u8*, u8);
void twi_attachSlaveRxEvent( void (*)(u8*, u32) );
void twi_attachSlaveTxEvent( void (*)(void) );
void twi_reply(u8);
void twi_stop(void);
void twi_releaseBus(void);

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

#ifndef _UTIL_TWI_H_
#define _UTIL_TWI_H_ 1

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

/*
 * The lower 3 bits of TWSR are reserved on the ATmega163.
 * The 2 LSB carry the prescaler bits on the newer ATmegas.
*/
#define TW_STATUS_MASK		((1<<TWS7)|(1<<TWS6)|(1<<TWS5)|(1<<TWS4)|\
				(1<<TWS3))

/* TWSR, masked by TW_STATUS_MASK */
#define TW_STATUS		(TWSR & TW_STATUS_MASK)

/* SLA+R address */
#define TW_READ		1

/* SLA+W address */
#define TW_WRITE	0

#endif /* _UTIL_TWI_H_ */

#endif /* TWI_H */

