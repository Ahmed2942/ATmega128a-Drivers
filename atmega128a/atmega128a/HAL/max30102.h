/*************************************************** 
 This is a library written for the Maxim MAX30105 Optical Smoke Detector
 It should also work with the MAX30102. However, the MAX30102 does not have a Green LED.

 These sensors use I2C to communicate, as well as a single (optional)
 interrupt line that is not currently supported in this driver.
 *****************************************************/
#ifndef MAX30102_H
#define MAX30102_H

#define F_CPU 16000000UL						 /* Define CPU clock Frequency; here its 16MHz */
#include <util/delay.h>
#include "UTILS.h"
#include "Std_types.h"
#include "millis.h"

//#include "i2c.h"	// library for I2C-communication


 #define MAX30105_ADDRESS          0x57 //7-bit I2C Address
//Note that MAX30102 has the same I2C address and Part ID

#define I2C_SPEED_STANDARD        100000
#define I2C_SPEED_FAST            400000
 
//Define the size of the I2C buffer based on the platform the user has
//The catch-all default is 32
#define I2C_BUFFER_LENGTH 32
 
 
bool_t begin(TwoWire &wirePort = Wire, u32 i2cSpeed = I2C_SPEED_STANDARD, u8 i2caddr = MAX30105_ADDRESS);

u32 getRed(void); //Returns immediate red value
u32 getIR(void); //Returns immediate IR value
u32 getGreen(void); //Returns immediate green value
bool_t safeCheck(u8 maxTimeToCheck); //Given a max amount of time, check for new data

// Configuration
void softReset();
void shutDown(); 
void wakeUp(); 

void setLEDMode(u8 mode);

void setADCRange(u8 adcRange);
void setSampleRate(u8 sampleRate);
void setPulseWidth(u8 pulseWidth);

void setPulseAmplitudeRed(u8 value);
void setPulseAmplitudeIR(u8 value);

//Multi-led configuration mode (page 22)
void enableSlot(u8 slotNumber, u8 device); //Given slot number, assign a device to slot
void disableSlots(void);

// Data Collection

//Interrupts (page 13, 14)
u8 getINT1(void); //Returns the main interrupt group
u8 getINT2(void); //Returns the temp ready interrupt
void enableAFULL(void); //Enable/disable individual interrupts
void disableAFULL(void);
void enableDATARDY(void);
void disableDATARDY(void);
void enableALCOVF(void);
void disableALCOVF(void);

//FIFO Configuration (page 18)
void setFIFOAverage(u8 samples);
void enableFIFORollover();
void disableFIFORollover();
void setFIFOAlmostFull(u8 samples);

//FIFO Reading
u16 check(void); //Checks for new data and fills FIFO
u8 samples_available(void); //Tells caller how many new samples are available (head - tail)
void nextSample(void); //Advances the tail of the sense array
u32 getFIFORed(void); //Returns the FIFO sample pointed to by tail
u32 getFIFOIR(void); //Returns the FIFO sample pointed to by tail

u8 getWritePointer(void);
u8 getReadPointer(void);
void clearFIFO(void); //Sets the read/write pointers to zero

// Detecting ID/Revision
u8 getRevisionID();
u8 readPartID();  

// Setup the IC with user selectable settings
void setup(char powerLevel = 0x1F, char sampleAverage = 4, char ledMode = 3, int sampleRate = 400, int pulseWidth = 411, int adcRange = 4096);

// Low-level I2C communication
u8 readRegister8(u8 address, u8 reg);
void writeRegister8(u8 address, u8 reg, u8 value);


//activeLEDs is the number of channels turned on, and can be 1 to 3. 2 is common for Red+IR.
char activeLEDs; //Gets set during setup. Allows check() to calculate how many chars to read from FIFO

u8 revisionID; 

void readRevisionID();

void bitMask(u8 reg, u8 mask, u8 thing);

#define STORAGE_SIZE 4 //Each long is 4 chars so limit this to fit on your micro
typedef struct Record
{
  u32 red[STORAGE_SIZE];
  u32 IR[STORAGE_SIZE];
  char head;
  char tail;
} sense_struct; //This is our circular buffer of readings from the sensor

sense_struct sense;
  
  
  
  
#endif /*MAX30102_H*/