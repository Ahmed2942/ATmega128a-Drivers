#define F_CPU 16000000UL
#include <util/delay.h>
#include "MemMap.h"
#include "Std_types.h"
#include "UTILS.h"
#include "ADC.h"
#include "LCD.h"
#include "I2C.h"
#include "MAX30102.h"
#include "heartRate.h"


const u8 RATE_SIZE = 4; //Increase this for more averaging. 4 is good.
u8 rates[4]; //Array of heart rates
u8 rateSpot = 0;
u32 lastBeat = 0; //Time at which the last beat occurred

float beatsPerMinute;
int beatAvg;

int main(void)
{
	DIO_Init();
    LCD_Init();
    LCD_GoTo(0,0);
    LCD_Writestring("Init.");
	_delay_ms(1000);
    // Initialize sensor
    if (!Begin(I2C_SPEED_FAST, MAX30102_ADDRESS)) //Use 400kHz speed
    {
		LCD_GoTo(0,0);
	    LCD_Writestring("MAX30102 was not found. Please check wiring/power. ");
	    while (1);
    }
    LCD_Writestring("Place your finger on the sensor with steady pressure.");

    //setup(); //Configure sensor with default settings
    setup(0x1F, 4, 3, 400, 411, 4096);
    setPulseAmplitudeRed(0x0A); //Turn Red LED to low to indicate sensor is running
    while (1) 
    {
		u32 irValue = getIR();//  s / u

	    if (checkForBeat(irValue) == TRUE)
	    {
		    //We sensed a beat!
		    u32 delta = millis() - lastBeat;
		    lastBeat = millis();

		    beatsPerMinute = 60 / (delta / 1000.0);

		    if (beatsPerMinute < 255 && beatsPerMinute > 20)
		    {
			    rates[rateSpot++] = (u8)beatsPerMinute; //Store this reading in the array
			    rateSpot %= RATE_SIZE; //Wrap variable

			    //Take average of readings
			    beatAvg = 0;
			    for (u8 x = 0 ; x < RATE_SIZE ; x++)
			    beatAvg += rates[x];
			    beatAvg /= RATE_SIZE;
		    }
	    }
		LCD_GoTo(0,0);
	    LCD_Writestring("IR=");
		LCD_GoTo(1,0);
	    LCD_WriteNumber(irValue);//s32
		_delay_ms(10000);
		LCD_GoTo(0,0);
	    LCD_Writestring(", BPM=");
		LCD_GoTo(1,0);
	    LCD_Write_Float(beatsPerMinute);
		_delay_ms(10000);
		LCD_GoTo(0,0);
	    LCD_Writestring(", Avg BPM=");
		LCD_GoTo(1,0);
	    LCD_WriteNumber(beatAvg);// int
		_delay_ms(10000);
		
	    if (irValue < 50000)
	    LCD_Writestring(" No finger?");

    }
}

