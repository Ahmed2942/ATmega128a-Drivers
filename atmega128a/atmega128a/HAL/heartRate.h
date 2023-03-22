/*
 Optical Heart Rate Detection (PBA Algorithm)
 By: Nathan Seidle
 SparkFun Electronics
 Date: October 2nd, 2016
 
 Given a series of IR samples from the MAX30105 we discern when a heart beat is occurring

 Let's have a brief chat about what this code does. We're going to try to detect
 heart-rate optically. This is tricky and prone to give false readings. We really don't
 want to get anyone hurt so use this code only as an example of how to process optical
 data. Build fun stuff with our MAX30105 breakout board but don't use it for actual
 medical diagnosis.

 Excellent background on optical heart rate detection:
 http://www.ti.com/lit/an/slaa655/slaa655.pdf */

 

#ifndef HEARTRATE_H_
#define HEARTRATE_H_


#include "Std_types.h"


bool_t checkForBeat(s32 sample);
s16 averageDCEstimator(s32 *p, u16 x);
s16 lowPassFIRFilter(s16 din);
s32 mul16(s16 x, s16 y);



#endif /* HEARTRATE_H_ */