#include "heartRate.h"

//from data-sheet pg.2 ,Absolute Maximum Ratings
s16 IR_AC_Max = 20;//mA
s16 IR_AC_Min = -20;//mA

s16 IR_AC_Signal_Current = 0;
s16 IR_AC_Signal_Previous;
s16 IR_AC_Signal_min = 0;
s16 IR_AC_Signal_max = 0;
s16 IR_Average_Estimated;

s16 positiveEdge = 0;
s16 negativeEdge = 0;
s32 ir_avg_reg = 0;

s16 cbuf[32];
u8 offset = 0;

static const u16 FIRCoeffs[12] = {172, 321, 579, 927, 1360, 1858, 2390, 2916, 3391, 3768, 4012, 4096};

//  Heart Rate Monitor functions takes a sample value and the sample number
//  Returns true if a beat is detected
//  A running average of four samples is recommended for display on the screen.
bool_t checkForBeat(s32 sample)
{
	bool_t beatDetected = FALSE;

	//  Save current state
	IR_AC_Signal_Previous = IR_AC_Signal_Current;
	
	//This is good to view for debugging
	//Serial.print("Signal_Current: ");
	//Serial.println(IR_AC_Signal_Current);

	//  Process next data sample
	IR_Average_Estimated = averageDCEstimator(&ir_avg_reg, sample);
	IR_AC_Signal_Current = lowPassFIRFilter(sample - IR_Average_Estimated);

	//  Detect positive zero crossing (rising edge)
	if ((IR_AC_Signal_Previous < 0) & (IR_AC_Signal_Current >= 0))
	{
		
		IR_AC_Max = IR_AC_Signal_max; //Adjust our AC max and min
		IR_AC_Min = IR_AC_Signal_min;

		positiveEdge = 1;
		negativeEdge = 0;
		IR_AC_Signal_max = 0;

		//if ((IR_AC_Max - IR_AC_Min) > 100 & (IR_AC_Max - IR_AC_Min) < 1000)
		if ((IR_AC_Max - IR_AC_Min) > 20 & (IR_AC_Max - IR_AC_Min) < 1000)//??
		{
			//Heart beat!!!
			beatDetected = TRUE;
		}
	}

	//  Detect negative zero crossing (falling edge)
	if ((IR_AC_Signal_Previous > 0) & (IR_AC_Signal_Current <= 0))
	{
		positiveEdge = 0;
		negativeEdge = 1;
		IR_AC_Signal_min = 0;
	}

	//  Find Maximum value in positive cycle
	if (positiveEdge & (IR_AC_Signal_Current > IR_AC_Signal_Previous))
	{
		IR_AC_Signal_max = IR_AC_Signal_Current;
	}

	//  Find Minimum value in negative cycle
	if (negativeEdge & (IR_AC_Signal_Current < IR_AC_Signal_Previous))
	{
		IR_AC_Signal_min = IR_AC_Signal_Current;
	}
	
	return(beatDetected);
}

//  Average DC Estimator
s16 averageDCEstimator(s32 *p, u16 x)
{
	*p += ((((long) x << 15) - *p) >> 4);//??
	return (*p >> 15);
}

//  Low Pass FIR Filter
s16 lowPassFIRFilter(s16 din)
{
	cbuf[offset] = din;

	s32 z = mul16(FIRCoeffs[11], cbuf[(offset - 11) & 0x1F]);
	
	for (u8 i = 0 ; i < 11 ; i++)
	{
		z += mul16(FIRCoeffs[i], cbuf[(offset - i) & 0x1F] + cbuf[(offset - 22 + i) & 0x1F]);
	}

	offset++;
	offset %= 32; //Wrap condition

	return(z >> 15);//?? , adc resolution !!
}

//  Integer multiplier
s32 mul16(s16 x, s16 y)
{
	return((long)x * (long)y);
}






