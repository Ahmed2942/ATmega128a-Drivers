#include "MAX30102.h"
#include <string.h>

// Status Registers
static const u8 MAX30102_INTSTAT1 =			0x00;
static const u8 MAX30102_INTSTAT2 =			0x01;
static const u8 MAX30102_INTENABLE1 =		0x02;
static const u8 MAX30102_INTENABLE2 =		0x03;

// FIFO Registers
static const u8 MAX30102_FIFOWRITEPTR = 	0x04;
static const u8 MAX30102_FIFOOVERFLOW = 	0x05;
static const u8 MAX30102_FIFOREADPTR =		0x06;
static const u8 MAX30102_FIFODATA =			0x07;

// Configuration Registers
static const u8 MAX30102_FIFOCONFIG = 		0x08;
static const u8 MAX30102_MODECONFIG = 		0x09;
static const u8 MAX30102_PARTICLECONFIG = 	0x0A;    // Note, sometimes listed as "SPO2" config in datasheet (pg. 11)
static const u8 MAX30102_LED1_PULSEAMP = 	0x0C;
static const u8 MAX30102_LED2_PULSEAMP = 	0x0D;
static const u8 MAX30102_LED3_PULSEAMP = 	0x0E;
static const u8 MAX30102_LED_PROX_AMP = 	0x10;
static const u8 MAX30102_MULTILEDCONFIG1 =  0x11;
static const u8 MAX30102_MULTILEDCONFIG2 =  0x12;

// Die Temperature Registers
static const u8 MAX30102_DIETEMPINT = 		0x1F;
static const u8 MAX30102_DIETEMPFRAC = 		0x20;
static const u8 MAX30102_DIETEMPCONFIG = 	0x21;

// Proximity Function Registers
static const u8 MAX30102_PROXINTTHRESH = 	0x30;

// Part ID Registers
static const u8 MAX30102_REVISIONID = 		0xFE;
static const u8 MAX30102_PARTID = 			0xFF;    // Should always be 0x15. Identical to MAX30102.

// MAX30102 Commands
// Interrupt configuration (pg 13, 14)
static const u8 MAX30102_INT_A_FULL_MASK =	(char)~0b10000000;
static const u8 MAX30102_INT_A_FULL_ENABLE = 0x80;
static const u8 MAX30102_INT_A_FULL_DISABLE = 0x00;

static const u8 MAX30102_INT_DATA_RDY_MASK = (char)~0b01000000;
static const u8 MAX30102_INT_DATA_RDY_ENABLE =	0x40;
static const u8 MAX30102_INT_DATA_RDY_DISABLE = 0x00;

static const u8 MAX30102_INT_ALC_OVF_MASK = (char)~0b00100000;
static const u8 MAX30102_INT_ALC_OVF_ENABLE = 	0x20;
static const u8 MAX30102_INT_ALC_OVF_DISABLE = 0x00;

static const u8 MAX30102_INT_PROX_INT_MASK = (char)~0b00010000;
static const u8 MAX30102_INT_PROX_INT_ENABLE = 0x10;
static const u8 MAX30102_INT_PROX_INT_DISABLE = 0x00;

static const u8 MAX30102_SAMPLEAVG_MASK =	(char)~0b11100000;
static const u8 MAX30102_SAMPLEAVG_1 = 	0x00;
static const u8 MAX30102_SAMPLEAVG_2 = 	0x20;
static const u8 MAX30102_SAMPLEAVG_4 = 	0x40;
static const u8 MAX30102_SAMPLEAVG_8 = 	0x60;
static const u8 MAX30102_SAMPLEAVG_16 = 	0x80;
static const u8 MAX30102_SAMPLEAVG_32 = 	0xA0;

static const u8 MAX30102_ROLLOVER_MASK = 	0xEF;
static const u8 MAX30102_ROLLOVER_ENABLE = 0x10;
static const u8 MAX30102_ROLLOVER_DISABLE = 0x00;

static const u8 MAX30102_A_FULL_MASK = 	0xF0;

// Mode configuration commands (page 19)
static const u8 MAX30102_SHUTDOWN_MASK = 	0x7F;
static const u8 MAX30102_SHUTDOWN = 		0x80;
static const u8 MAX30102_WAKEUP = 			0x00;

static const u8 MAX30102_RESET_MASK = 		0xBF;
static const u8 MAX30102_RESET = 			0x40;

static const u8 MAX30102_MODE_MASK = 		0xF8;
static const u8 MAX30102_MODE_REDONLY = 	0x02;
static const u8 MAX30102_MODE_REDIRONLY = 	0x03;
static const u8 MAX30102_MODE_MULTILED = 	0x07;

// Particle sensing configuration commands (pgs 19-20)
static const u8 MAX30102_ADCRANGE_MASK = 	0x9F;
static const u8 MAX30102_ADCRANGE_2048 = 	0x00;
static const u8 MAX30102_ADCRANGE_4096 = 	0x20;
static const u8 MAX30102_ADCRANGE_8192 = 	0x40;
static const u8 MAX30102_ADCRANGE_16384 = 	0x60;

static const u8 MAX30102_SAMPLERATE_MASK =  0xE3;
static const u8 MAX30102_SAMPLERATE_50 = 	0x00;
static const u8 MAX30102_SAMPLERATE_100 = 	0x04;
static const u8 MAX30102_SAMPLERATE_200 = 	0x08;
static const u8 MAX30102_SAMPLERATE_400 = 	0x0C;
static const u8 MAX30102_SAMPLERATE_800 = 	0x10;
static const u8 MAX30102_SAMPLERATE_1000 =  0x14;
static const u8 MAX30102_SAMPLERATE_1600 =  0x18;
static const u8 MAX30102_SAMPLERATE_3200 =  0x1C;

static const u8 MAX30102_PULSEWIDTH_MASK =  0xFC;
static const u8 MAX30102_PULSEWIDTH_69 = 	0x00;
static const u8 MAX30102_PULSEWIDTH_118 = 	0x01;
static const u8 MAX30102_PULSEWIDTH_215 = 	0x02;
static const u8 MAX30102_PULSEWIDTH_411 = 	0x03;

//Multi-LED Mode configuration (pg 22)
static const u8 MAX30102_SLOT1_MASK = 		0xF8;
static const u8 MAX30102_SLOT2_MASK = 		0x8F;
static const u8 MAX30102_SLOT3_MASK = 		0xF8;
static const u8 MAX30102_SLOT4_MASK = 		0x8F;

static const u8 SLOT_NONE = 				0x00;
static const u8 SLOT_RED_LED = 			    0x01;
static const u8 SLOT_IR_LED = 				0x02;


static const u8 MAX_30102_EXPECTEDPARTID =  0x15;

// I2C address
u8 _i2caddr;

bool_t Begin(u32 i2cSpeed, u8 i2caddr) {

  // _i2cPort->begin();
  I2C_Master_Init();
  
  _i2caddr = i2caddr;

  // Step 1: Initial Communication and Verification
  // Check that a MAX30102 is connected
  if (readPartID() != MAX_30102_EXPECTEDPARTID) {
    // Error -- Part ID read from MAX30102 does not match expected part ID.
    // This may mean there is a physical connectivity problem (broken wire, unpowered, etc).
    return FALSE;
  }
  // Populate revision ID
  readRevisionID();

  return TRUE;
}

//***************************Configuration**************************

//Begin Interrupt configuration

u8 getINT1(void) {
  return (readRegister8(_i2caddr, MAX30102_INTSTAT1));
}
u8 getINT2(void) {
  return (readRegister8(_i2caddr, MAX30102_INTSTAT2));
}

void enableAFULL(void) {
  bitMask(MAX30102_INTENABLE1, MAX30102_INT_A_FULL_MASK, MAX30102_INT_A_FULL_ENABLE);
}
void disableAFULL(void) {
  bitMask(MAX30102_INTENABLE1, MAX30102_INT_A_FULL_MASK, MAX30102_INT_A_FULL_DISABLE);
}

void enableDATARDY(void) {
  bitMask(MAX30102_INTENABLE1, MAX30102_INT_DATA_RDY_MASK, MAX30102_INT_DATA_RDY_ENABLE);
}
void disableDATARDY(void) {
  bitMask(MAX30102_INTENABLE1, MAX30102_INT_DATA_RDY_MASK, MAX30102_INT_DATA_RDY_DISABLE);
}

void enableALCOVF(void) {
  bitMask(MAX30102_INTENABLE1, MAX30102_INT_ALC_OVF_MASK, MAX30102_INT_ALC_OVF_ENABLE);
}
void disableALCOVF(void) {
  bitMask(MAX30102_INTENABLE1, MAX30102_INT_ALC_OVF_MASK, MAX30102_INT_ALC_OVF_DISABLE);
}

//End Interrupt configuration

void softReset(void) {
  bitMask(MAX30102_MODECONFIG, MAX30102_RESET_MASK, MAX30102_RESET);

  // Poll for bit to clear, reset is then complete
  // Timeout after 100ms
  unsigned long startTime = millis();
  while (millis() - startTime < 100)
  {
    u8 response = readRegister8(_i2caddr, MAX30102_MODECONFIG);
    if ((response & MAX30102_RESET) == 0) break; //We're done!
   _delay_ms(1); //Let's not over burden the I2C bus (ms)
  }
}

void shutDown(void) {
  // Put IC into low power mode (datasheet pg. 19)
  // During shutdown the IC will continue to respond to I2C commands but will
  // not update with or take new readings (such as temperature)
  bitMask(MAX30102_MODECONFIG, MAX30102_SHUTDOWN_MASK, MAX30102_SHUTDOWN);
}

void wakeUp(void) {
  // Pull IC out of low power mode (datasheet pg. 19)
  bitMask(MAX30102_MODECONFIG, MAX30102_SHUTDOWN_MASK, MAX30102_WAKEUP);
}

void setLEDMode(u8 mode) {
  // Set which LEDs are used for sampling -- Red only, RED+IR only, or custom.
  // See datasheet, page 19
  bitMask(MAX30102_MODECONFIG, MAX30102_MODE_MASK, mode);
}

void setADCRange(u8 adcRange) {
  // adcRange: one of MAX30102_ADCRANGE_2048, _4096, _8192, _16384
  bitMask(MAX30102_PARTICLECONFIG, MAX30102_ADCRANGE_MASK, adcRange);
}

void setSampleRate(u8 sampleRate) {
  // sampleRate: one of MAX30102_SAMPLERATE_50, _100, _200, _400, _800, _1000, _1600, _3200
  bitMask(MAX30102_PARTICLECONFIG, MAX30102_SAMPLERATE_MASK, sampleRate);
}

void setPulseWidth(u8 pulseWidth) {
  // pulseWidth: one of MAX30102_PULSEWIDTH_69, _188, _215, _411
  bitMask(MAX30102_PARTICLECONFIG, MAX30102_PULSEWIDTH_MASK, pulseWidth);
}

// NOTE: Amplitude values: 0x00 = 0mA, 0x7F = 25.4mA, 0xFF = 50mA (typical)
// See datasheet, page 21
void setPulseAmplitudeRed(u8 amplitude) {
  writeRegister8(_i2caddr, MAX30102_LED1_PULSEAMP, amplitude);
}

void setPulseAmplitudeIR(u8 amplitude) {
  writeRegister8(_i2caddr, MAX30102_LED2_PULSEAMP, amplitude);
}

//Given a slot number assign a thing to it
//Devices are SLOT_RED_LED
//Assigning a SLOT_RED_LED will pulse LED

void enableSlot(u8 slotNumber, u8 device) {

  switch (slotNumber) {
    case (1):
      bitMask(MAX30102_MULTILEDCONFIG1, MAX30102_SLOT1_MASK, device);
      break;
    case (2):
      bitMask(MAX30102_MULTILEDCONFIG1, MAX30102_SLOT2_MASK, device << 4);
      break;
    case (3):
      bitMask(MAX30102_MULTILEDCONFIG2, MAX30102_SLOT3_MASK, device);
      break;
    case (4):
      bitMask(MAX30102_MULTILEDCONFIG2, MAX30102_SLOT4_MASK, device << 4);
      break;
    default:
      //Shouldn't be here!
      break;
  }
}

//Clears all slot assignments

void disableSlots(void) {
  writeRegister8(_i2caddr, MAX30102_MULTILEDCONFIG1, 0);
  writeRegister8(_i2caddr, MAX30102_MULTILEDCONFIG2, 0);
}


//***************************FIFO Configuration***************************

//Set sample average (Table 3, Page 18)

void setFIFOAverage(u8 numberOfSamples) {
  bitMask(MAX30102_FIFOCONFIG, MAX30102_SAMPLEAVG_MASK, numberOfSamples);
}

//Resets all points to start in a known state
//Page 15 recommends clearing FIFO before beginning a read
void clearFIFO(void) {
  writeRegister8(_i2caddr, MAX30102_FIFOWRITEPTR, 0);
  writeRegister8(_i2caddr, MAX30102_FIFOOVERFLOW, 0);
  writeRegister8(_i2caddr, MAX30102_FIFOREADPTR, 0);
}

//Enable roll over if FIFO over flows
void enableFIFORollover(void) {
  bitMask(MAX30102_FIFOCONFIG, MAX30102_ROLLOVER_MASK, MAX30102_ROLLOVER_ENABLE);
}

//Disable roll over if FIFO over flows
void disableFIFORollover(void) {
  bitMask(MAX30102_FIFOCONFIG, MAX30102_ROLLOVER_MASK, MAX30102_ROLLOVER_DISABLE);
}

//Set number of samples to trigger the almost full interrupt (Page 18)
//Power on default is 32 samples
//Note it is reverse: 0x00 is 32 samples, 0x0F is 17 samples
void setFIFOAlmostFull(u8 numberOfSamples) {
  bitMask(MAX30102_FIFOCONFIG, MAX30102_A_FULL_MASK, numberOfSamples);
}

//Read the FIFO Write Pointer
u8 getWritePointer(void) {
  return (readRegister8(_i2caddr, MAX30102_FIFOWRITEPTR));
}

//Read the FIFO Read Pointer
u8 getReadPointer(void) {
  return (readRegister8(_i2caddr, MAX30102_FIFOREADPTR));
}


//*************************Device ID and Revision*************************

u8 readPartID() {
  return readRegister8(_i2caddr, MAX30102_PARTID);
}

void readRevisionID() {
  revisionID = readRegister8(_i2caddr, MAX30102_REVISIONID);
}

u8 getRevisionID() {
  return revisionID;
}

//**************************Setup the sensor******************************
//The MAX30102 has many settings. By default we select:
// Sample Average = 4
// Mode = MultiLED
// ADC Range = 16384 (62.5pA per LSB)
// Sample rate = 50
//Use the default setup if you are just getting started with the MAX30102 sensor
void setup(char powerLevel, char sampleAverage, char ledMode, int sampleRate, int pulseWidth, int adcRange) {
  softReset(); //Reset all configuration, threshold, and data registers to POR values

  //FIFO Configuration
  //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //The chip will average multiple samples of same type together if you wish
  if (sampleAverage == 1) setFIFOAverage(MAX30102_SAMPLEAVG_1); //No averaging per FIFO record
  else if (sampleAverage == 2) setFIFOAverage(MAX30102_SAMPLEAVG_2);
  else if (sampleAverage == 4) setFIFOAverage(MAX30102_SAMPLEAVG_4);
  else if (sampleAverage == 8) setFIFOAverage(MAX30102_SAMPLEAVG_8);
  else if (sampleAverage == 16) setFIFOAverage(MAX30102_SAMPLEAVG_16);
  else if (sampleAverage == 32) setFIFOAverage(MAX30102_SAMPLEAVG_32);
  else setFIFOAverage(MAX30102_SAMPLEAVG_4);

  //setFIFOAlmostFull(2); //Set to 30 samples to trigger an 'Almost Full' interrupt
  enableFIFORollover(); //Allow FIFO to wrap/roll over
  //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

  //Mode Configuration
  //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  if (ledMode == 3) setLEDMode(MAX30102_MODE_MULTILED); //Watch all three LED channels
  else if (ledMode == 2) setLEDMode(MAX30102_MODE_REDIRONLY); //Red and IR
  else setLEDMode(MAX30102_MODE_REDONLY); //Red only
  activeLEDs = ledMode; //Used to control how many chars to read from FIFO buffer
  //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

  //Particle Sensing Configuration
  //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  if(adcRange < 4096) setADCRange(MAX30102_ADCRANGE_2048); //7.81pA per LSB
  else if(adcRange < 8192) setADCRange(MAX30102_ADCRANGE_4096); //15.63pA per LSB
  else if(adcRange < 16384) setADCRange(MAX30102_ADCRANGE_8192); //31.25pA per LSB
  else if(adcRange == 16384) setADCRange(MAX30102_ADCRANGE_16384); //62.5pA per LSB
  else setADCRange(MAX30102_ADCRANGE_2048);

  if (sampleRate < 100) setSampleRate(MAX30102_SAMPLERATE_50); //Take 50 samples per second
  else if (sampleRate < 200) setSampleRate(MAX30102_SAMPLERATE_100);
  else if (sampleRate < 400) setSampleRate(MAX30102_SAMPLERATE_200);
  else if (sampleRate < 800) setSampleRate(MAX30102_SAMPLERATE_400);
  else if (sampleRate < 1000) setSampleRate(MAX30102_SAMPLERATE_800);
  else if (sampleRate < 1600) setSampleRate(MAX30102_SAMPLERATE_1000);
  else if (sampleRate < 3200) setSampleRate(MAX30102_SAMPLERATE_1600);
  else if (sampleRate == 3200) setSampleRate(MAX30102_SAMPLERATE_3200);
  else setSampleRate(MAX30102_SAMPLERATE_50);

  //The longer the pulse width the longer range of detection you'll have
  //At 69us and 0.4mA it's about 2 inches
  //At 411us and 0.4mA it's about 6 inches
  if (pulseWidth < 118) setPulseWidth(MAX30102_PULSEWIDTH_69); //Page 26, Gets us 15 bit resolution
  else if (pulseWidth < 215) setPulseWidth(MAX30102_PULSEWIDTH_118); //16 bit resolution
  else if (pulseWidth < 411) setPulseWidth(MAX30102_PULSEWIDTH_215); //17 bit resolution
  else if (pulseWidth == 411) setPulseWidth(MAX30102_PULSEWIDTH_411); //18 bit resolution
  else setPulseWidth(MAX30102_PULSEWIDTH_69);
  //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

  //LED Pulse Amplitude Configuration
  //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  //Default is 0x1F which gets us 6.4mA
  //powerLevel = 0x02, 0.4mA - Presence detection of ~4 inch
  //powerLevel = 0x1F, 6.4mA - Presence detection of ~8 inch
  //powerLevel = 0x7F, 25.4mA - Presence detection of ~8 inch
  //powerLevel = 0xFF, 50.0mA - Presence detection of ~12 inch

  setPulseAmplitudeRed(powerLevel);
  setPulseAmplitudeIR(powerLevel);
  //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

  //Multi-LED Mode Configuration, Enable the reading of the three LEDs
  //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-
  enableSlot(1, SLOT_RED_LED);
  if (ledMode > 1) enableSlot(2, SLOT_IR_LED);
  //if (ledMode > 2) enableSlot(3, SLOT_GREEN_LED);
  //-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-=-

  clearFIFO(); //Reset the FIFO before we begin checking the sensor
}


//****************************Data Collection*****************************

//Tell caller how many samples are available
u8 samples_available(void)
{
  u8 numberOfSamples = sense.head - sense.tail;
  if (numberOfSamples < 0) numberOfSamples += STORAGE_SIZE;

  return (numberOfSamples);
}

//Report the most recent red value
u32 getRed(void)
{
  //Check the sensor for new data for 250ms
  if(safeCheck(250))
    return (sense.red[sense.head]);
  else
    return(0); //Sensor failed to find new data
}

//Report the most recent IR value
u32 getIR(void)
{
  //Check the sensor for new data for 250ms
  if(safeCheck(250))
    return (sense.IR[sense.head]);
  else
    return(0); //Sensor failed to find new data
}

//Report the next Red value in the FIFO
u32 getFIFORed(void)
{
  return (sense.red[sense.tail]);
}

//Report the next IR value in the FIFO
u32 getFIFOIR(void)
{
  return (sense.IR[sense.tail]);
}

//Advance the tail
void nextSample(void)
{
  if(samples_available()) //Only advance the tail if new data is samples_available
  {
    sense.tail++;
    sense.tail %= STORAGE_SIZE; //Wrap condition
  }
}

//Polls the sensor for new data
//Call regularly
//If new data is samples_available, it updates the head and tail in the main struct
//Returns number of new samples obtained
u16 check(void)
{
  //Read register FIDO_DATA in (3-char * number of active LED) chunks
  //Until FIFO_RD_PTR = FIFO_WR_PTR

  char readPointer = getReadPointer();
  char writePointer = getWritePointer();

  int numberOfSamples = 0;

  //Do we have new data?
  if (readPointer != writePointer)
  {
    //Calculate the number of readings we need to get from sensor
    numberOfSamples = writePointer - readPointer;
    if (numberOfSamples < 0) numberOfSamples += 32; //Wrap condition

    //We now have the number of readings, now calc chars to read
    //For this example we are just doing Red and IR (3 chars each)
    int charsLeftToRead = numberOfSamples * activeLEDs * 3;

    //Get ready to read a burst of data from the FIFO register 
    I2C_Start(MAX30102_ADDRESS, I2C_WRITE);
    I2C_Write(MAX30102_FIFODATA);
    I2C_Stop();

    //We may need to read as many as 288 chars so we read in blocks no larger than I2C_BUFFER_LENGTH
    //I2C_BUFFER_LENGTH changes based on the platform. 64 chars for SAMD21, 32 chars for Uno.
    //Wire.requestFrom() is limited to BUFFER_LENGTH which is 32 on the Uno
    while (charsLeftToRead > 0)
    {
      int toGet = charsLeftToRead;
      if (toGet > I2C_BUFFER_LENGTH)
      {
        //If toGet is 32 this is bad because we read 6 chars (Red+IR * 3 = 6) at a time
        //32 % 6 = 2 left over. We don't want to request 32 chars, we want to request 30.
        //32 % 9 (Red+IR+GREEN) = 5 left over. We want to request 27.

        toGet = I2C_BUFFER_LENGTH - (I2C_BUFFER_LENGTH % (activeLEDs * 3)); //Trim toGet to be a multiple of the samples we need to read
      }

      charsLeftToRead -= toGet;

      //Request toGet number of chars from sensor
      I2C_RequestFrom(MAX30102_ADDRESS, toGet);
	  
      
      while (toGet > 0)
      {
        sense.head++; //Advance the head of the storage struct
        sense.head %= STORAGE_SIZE; //Wrap condition

        char temp[sizeof(u32)]; //Array of 4 chars that we will convert into long
        u32 tempLong;

        //Burst read three chars - RED
        temp[3] = 0;
        temp[2] = I2C_ReadBuffer();
        temp[1] = I2C_ReadBuffer();
        temp[0] = I2C_ReadBuffer();

        //Convert array to long
        memcpy(&tempLong, temp, sizeof(tempLong));
		
		tempLong &= 0x3FFFF; //Zero out all but 18 bits

        sense.red[sense.head] = tempLong; //Store this reading into the sense array

        if (activeLEDs > 1)
        {
          //Burst read three more chars - IR
          temp[3] = 0;
          temp[2] = I2C_ReadBuffer();
          temp[1] = I2C_ReadBuffer();
          temp[0] = I2C_ReadBuffer();

          //Convert array to long
          memcpy(&tempLong, temp, sizeof(tempLong));

		  tempLong &= 0x3FFFF; //Zero out all but 18 bits
          
		  sense.IR[sense.head] = tempLong;
        }

        /*if (activeLEDs > 2)
        {
          //Burst read three more chars - Green
          temp[3] = 0;
          temp[2] = I2C_ReadBuffer();
          temp[1] = I2C_ReadBuffer();
          temp[0] = I2C_ReadBuffer();
          //Convert array to long
          memcpy(&tempLong, temp, sizeof(tempLong));
		  tempLong &= 0x3FFFF; //Zero out all but 18 bits
          sense.green[sense.head] = tempLong;
        }*/

        toGet -= activeLEDs * 3;
      }

    } //End while (charsLeftToRead > 0)

  } //End readPtr != writePtr

  return (numberOfSamples); //Let the world know how much new data we found
}

//Check for new data but give up after a certain amount of time
//Returns true if new data was found
//Returns false if new data was not found
bool_t safeCheck(u8 maxTimeToCheck)
{
  u32 markTime = millis();
  
  while(1)
  {
	if(millis() - markTime > maxTimeToCheck) return(FALSE);

	if(check() == TRUE) //We found new data!
	  return(TRUE);

	_delay_ms(1);
  }
}

//Given a register, read it, mask it, and then set the thing
void bitMask(u8 reg, u8 mask, u8 thing)
{
  // Grab current register context
  u8 originalContents = readRegister8(_i2caddr, reg);

  // Zero-out the portions of the register we're interested in
  originalContents = originalContents & mask;

  // Change contents
  writeRegister8(_i2caddr, reg, originalContents | thing);
}


//**********************Low-level I2C Communication***********************

// u8 readRegister8(u8 address, u8 reg) {
//   I2C_Start(address);
//   I2C_Write(reg);
//   I2C_Stop();;
// 
//   I2C_RequestFrom((u8)address, (u8)1); // Request 1 char
//   if (samples_available())
//   {
//     return(I2C_ReadBuffer());
//   }
// 
//   return (0); //Fail
// 
// }

u8 readRegister8(u8 address, u8 reg) {
  u8 received;
  u8 test;
  test = I2C_Start(address, I2C_WRITE);
  LCD_Writenum_Hex(test);
  I2C_Write(reg);
  
  I2C_RepeatedStart(address, I2C_READ);
  if(samples_available()){
    received = I2C_ReadAck();
    return received;
  }
  I2C_Stop();
}

void writeRegister8(u8 address, u8 reg, u8 value) {
  I2C_Start(address, I2C_WRITE);
  I2C_Write(reg);
  I2C_Write(value);
  I2C_Stop();
}