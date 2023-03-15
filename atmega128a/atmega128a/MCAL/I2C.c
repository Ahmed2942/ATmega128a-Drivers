#include "Std_types.h"
#include "MemMap.h"
#include "I2C.h"								/* Include I2C header file */


u8 I2C_receivedBufferWriteIndex;
u8 I2C_receivedBufferReadIndex;
u8 I2C_receivedBufferLength;
u8 I2C_receivedBuffer[I2C_BUFFER_LENGTH];

void I2C_SetFrequency(u32 frequency)
{
  TWBR = ((F_CPU / frequency) - 16) / 2;
  
  /* twi bit rate formula from atmega128 manual pg 204
  SCL Frequency = CPU Clock Frequency / (16 + (2 * TWBR))
  note: TWBR should be 10 or higher for master mode
  It is 72 for a 16mhz Wiring board with 100kHz TWI */
}

/************************************************* I2C Master *************************************************/

void I2C_Master_Init()										/* I2C initialize function */
{
	TWSR = 0x00;									
	I2C_setFrequency(SCL_CLK);										/* Get bit rate register value by formula */
}	

u8 I2C_Start(u8 write_address)								/* I2C start function */
{
	u8 status = 0xff;;										/* Declare variable */
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);					/* Enable TWI, generate start condition and clear interrupt flag */
	while(!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (start condition) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if(status != TW_START)									/* Check weather start condition transmitted successfully or not? */
	return TW_START;										/* If not then return 0 to indicate start condition fail */
	TWDR = write_address;									/* If yes then write SLA+W in TWI data register */
	TWCR = (1<<TWEN)|(1<<TWINT);							/* Enable TWI and clear interrupt flag */
	while(!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (Write operation) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */	
	if(status == TW_MT_SLA_ACK)								/* Check weather SLA+W transmitted & ack received or not? */
	return TW_MT_SLA_ACK;									/* If yes then return 1 to indicate ack received i.e. ready to accept data byte */
	if(status == TW_MT_SLA_NACK)							/* Check weather SLA+W transmitted & nack received or not? */
	return TW_MT_SLA_NACK;									/* If yes then return 2 to indicate nack received i.e. device is busy */
	else
	return 0xff;											/* Else return 3 to indicate SLA+W failed */
}

void I2C_StartWait(u8 write_address)						/* I2C start wait function */
{
	u8 status;												/* Declare variable */
	while(1)
	{
		TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);				/* Enable TWI, generate start condition and clear interrupt flag */
		while(!(TWCR & (1<<TWINT)));						/* Wait until TWI finish its current job (start condition) */
		status = TWSR & 0xF8;								/* Read TWI status register with masking lower three bits */
		if(status != TW_START)								/* Check weather start condition transmitted successfully or not? */
		continue;											/* If no then continue with start loop again */
		TWDR = write_address;								/* If yes then write SLA+W in TWI data register */
		TWCR = (1<<TWEN)|(1<<TWINT);						/* Enable TWI and clear interrupt flag */
		while(!(TWCR & (1<<TWINT)));						/* Wait until TWI finish its current job (Write operation) */
		status = TWSR & 0xF8;								/* Read TWI status register with masking lower three bits */
		if(status != TW_MT_SLA_ACK )						/* Check weather SLA+W transmitted & ack received or not? */
		{
			I2C_Stop();										/* If not then generate stop condition */
			continue;										/* continue with start loop again */
		}
		break;												/* If yes then break loop */
	}
}

u8 I2C_RepeatedStart(u8 read_address)						/* I2C repeated start function */
{
	u8 status = 0xff;;												/* Declare variable */
	TWCR = (1<<TWSTA)|(1<<TWEN)|(1<<TWINT);					/* Enable TWI, generate start condition and clear interrupt flag */
	while(!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (start condition) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if(status != TW_REP_START)								/* Check weather repeated start condition transmitted successfully or not? */
	return 0;												/* If no then return 0 to indicate repeated start condition fail */
	TWDR = read_address;									/* If yes then write SLA+R in TWI data register */
	TWCR = (1<<TWEN)|(1<<TWINT);							/* Enable TWI and clear interrupt flag */
	while(!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (Write operation) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if(status == TW_MR_SLA_ACK)								/* Check weather SLA+R transmitted & ack received or not? */
	return TW_MR_SLA_ACK;									/* If yes then return 1 to indicate ack received */ 
	if(status == TW_MR_SLA_NACK)							/* Check weather SLA+R transmitted & nack received or not? */
	return TW_MR_SLA_ACK;									/* If yes then return 2 to indicate nack received i.e. device is busy */
	else
	return 0xff;											/* Else return 3 to indicate SLA+W failed */
}

void I2C_Stop()												/* I2C stop function */
{
	TWCR=(1<<TWSTO)|(1<<TWINT)|(1<<TWEN);					/* Enable TWI, generate stop condition and clear interrupt flag */
	while(TWCR & (1<<TWSTO));								/* Wait until stop condition execution */ 
}

u8 I2C_Write(u8 data)										/* I2C write function */
{
	u8 status;												/* Declare variable */
	TWDR = data;											/* Copy data in TWI data register */
	TWCR = (1<<TWEN)|(1<<TWINT);							/* Enable TWI and clear interrupt flag */
	while(!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (Write operation) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if(status == TW_MT_DATA_ACK)							/* Check weather data transmitted & ack received or not? */
	return TW_MT_DATA_ACK;									/* If yes then return 0 to indicate ack received */
	if(status == TW_MT_DATA_NACK)							/* Check weather data transmitted & nack received or not? */
	return TW_MT_DATA_NACK;									/* If yes then return 1 to indicate nack received */
	else
	return 0xff;			   								/* Else return 2 to indicate data transmission failed */
}



u8 I2C_ReadAck()											/* I2C read ack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT)|(1<<TWEA);					/* Enable TWI, generation of ack and clear interrupt flag */
	while(!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (read operation) */
	
	return TWDR;											/* Return received data */
}	

u8 I2C_ReadNack()											/* I2C read nack function */
{
	TWCR=(1<<TWEN)|(1<<TWINT);								/* Enable TWI and clear interrupt flag */
	while(!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (read operation) */
	return TWDR;											/* Return received data */
}

u8 I2C_ReadBuffer(void)
{
	u8 value = -1;

	// get each successive byte on each call
	if(I2C_receivedBufferReadIndex > I2C_receivedBufferWriteIndex){

		I2C_receivedBufferReadIndex=0;
	}
	value = I2C_receivedBuffer[I2C_receivedBufferReadIndex++];
	return value;
}

// Request number of bytes equal to 'quantity' from 'address' and return number of remaining bytes
u8 I2C_RequestFrom(u8 address, u8 quantity)
{
	// clamp to buffer length
	if(quantity > I2C_BUFFER_LENGTH){
		I2C_ReadFrom(address, I2C_BUFFER_LENGTH);
		return quantity - I2C_BUFFER_LENGTH;
	}
	return 0;
}

void I2C_ReadFrom(u8 address, u8 length)
{
	// initialize buffer iteration vars
	I2C_receivedBufferWriteIndex = 0;
	I2C_receivedBufferLength = length-1;  
	// This is not intuitive, read on...
	// On receive, the previously configured ACK/NACK setting is transmitted in
	// response to the received byte before the interrupt is signalled. 
	// Therefor we must actually set NACK when the _next_ to last byte is
	// received, causing that NACK to be sent in response to receiving the last
	// expected byte of data.

	// wait for read operation to complete
	while(I2C_receivedBufferWriteIndex < I2C_receivedBufferLength){
		I2C_receivedBuffer[I2C_receivedBufferWriteIndex++] = I2C_ReadAck();
	}
	I2C_receivedBuffer[I2C_receivedBufferWriteIndex++] = I2C_ReadNack();
}


void I2C_WriteTo(u8 address, u8* data, u8 length)
{
	u8 i;
	// ensure data will fit into buffer
	if(I2C_BUFFER_LENGTH < length){
		return;
	}

	// copy data to I2C buffer
	for(i = 0; i < length; ++i){
		I2C_Write(data[i]);
	}
}





/************************************************* I2C Slave *************************************************/

void I2C_Slave_Init(u8 slave_address)
{
	TWAR = slave_address;									/* Assign address in I2C address register */
	TWCR = (1<<TWEN) | (1<<TWEA) | (1<<TWINT);				/* Enable TWI, Enable ack generation, clear TWI interrupt */
}

u8 I2C_Slave_Listen()
{
	while(1)
	{
		u8 status = 0xff;;													/* Declare variable */
		while(!(TWCR & (1<<TWINT)));										/* Wait to be addressed */
		status = TWSR & 0xF8;												/* Read TWI status register with masking lower three bits */
		if(status == TW_SR_SLA_ACK || status == TW_SR_ARB_LOST_SLA_ACK)		/* Check weather own SLA+W received & ack returned (TWEA = 1) */
		return 0;															/* If yes then return 0 to indicate ack returned */
		if(status == TW_ST_SLA_ACK || status == TW_ST_ARB_LOST_SLA_ACK)		/* Check weather own SLA+R received & ack returned (TWEA = 1) */
		return 1;															/* If yes then return 1 to indicate ack returned */
		if(status == TW_SR_GCALL_ACK || status == TW_SR_ARB_LOST_GCALL_ACK)	/* Check weather general call received & ack returned (TWEA = 1) */
		return 2;															/* If yes then return 2 to indicate ack returned */
		else
		continue;															/* Else continue */
	}
}

u8 I2C_Slave_Transmit(u8 data)
{
	u8 status = 0xff;;
	TWDR = data;											/* Write data to TWDR to be transmitted */
	TWCR = (1<<TWEN)|(1<<TWINT)|(1<<TWEA);					/* Enable TWI and clear interrupt flag */
	while(!(TWCR & (1<<TWINT)));							/* Wait until TWI finish its current job (Write operation) */
	status = TWSR & 0xF8;									/* Read TWI status register with masking lower three bits */
	if(status == TW_SR_STOP)								/* Check weather STOP/REPEATED START received */
	{
		TWCR |= (1<<TWINT);									/* If yes then clear interrupt flag & return -1 */
		return -1;
	}
	if(status == TW_ST_DATA_ACK)							/* Check weather data transmitted & ack received */
	return 0;												/* If yes then return 0 */
	if(status == TW_ST_DATA_NACK)							/* Check weather data transmitted & nack received */
	{
		TWCR |= (1<<TWINT);									/* If yes then clear interrupt flag & return -2 */
		return -2;
	}
	if(status == TW_ST_LAST_DATA)							/* If last data byte transmitted with ack received TWEA = 0 */
	return -3;												/* If yes then return -3 */
	else													/* else return -4 */
	return -4;
}

u8 I2C_Slave_Receive()
{
	u8 status = 0xff;;													/* Declare variable */
	TWCR=(1<<TWEN)|(1<<TWEA)|(1<<TWINT);								/* Enable TWI, generation of ack and clear interrupt flag */
	while(!(TWCR & (1<<TWINT)));										/* Wait until TWI finish its current job (read operation) */
	status = TWSR & 0xF8;												/* Read TWI status register with masking lower three bits */
	if(status == TW_SR_DATA_ACK || status == TW_SR_GCALL_DATA_ACK)		/* Check weather data received & ack returned (TWEA = 1) */
	return TWDR;														/* If yes then return received data */
	if(status == TW_SR_DATA_NACK || status == TW_SR_GCALL_DATA_NACK)	/* Check weather data received, nack returned and switched to not addressed slave mode */
	return TWDR;														/* If yes then return received data */
	if(status == TW_SR_STOP)											/* Check weather STOP/REPEATED START received */
	{
		TWCR |= (1<<TWINT);												/* If yes then clear interrupt flag & return 0 */
		return -1;
	}
	else
	return -2;															/* Else return 1 */
}