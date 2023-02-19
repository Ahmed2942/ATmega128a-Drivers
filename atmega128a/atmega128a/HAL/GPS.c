#define F_CPU 8000000UL
#include "GPS.h"

char Latitude_Buffer[15],Longitude_Buffer[15],Time_Buffer[15],Altitude_Buffer[8];
char degrees_buffer[degrees_buffer_size];   /* save latitude or longitude in degree */
char GGA_Buffer[Buffer_Size];               /* save GGA string */
u8 GGA_Pointers[20];                   /* to store instances of ',' */
char GGA_CODE[3];
volatile u8 GGA_Index, CommaCounter;
bool	IsItGGAString	= false,
flag1		= false,
flag2		= false;

/************************************************************************************************/

/*Function to get time from GGA Buffer*/
void get_gpstime(){
	cli();
	u8 time_index=0;

	/* parse Time in GGA string stored in buffer */
	for(u8 index = 0;GGA_Buffer[index]!=','; index++){
		
		Time_Buffer[time_index] = GGA_Buffer[index];
		time_index++;
	}
	convert_time_to_UTC();
	sei();
}

/*********************************************************************************************/

/* Function to get Latitude from GGA Buffer */
void get_latitude(u16 lat_pointer){
	cli();
	u8 lat_index;
	u8 index = lat_pointer+1;
	lat_index=0;
	
	/* parse Latitude in GGA string stored in buffer */
	for(;GGA_Buffer[index]!=',';index++){
		Latitude_Buffer[lat_index]= GGA_Buffer[index];
		lat_index++;
	}
	
	Latitude_Buffer[lat_index++] = GGA_Buffer[index++];
	Latitude_Buffer[lat_index]   = GGA_Buffer[index];  /* get direction */
	convert_to_degrees(Latitude_Buffer);
	sei();
}

/********************************************************************************************/

/* Function to get Longitude from GGA Buffer */
void get_longitude(u16 long_pointer){
	cli();
	u8 long_index;
	u8 index = long_pointer+1;
	long_index=0;
	
	/* parse Longitude in GGA string stored in buffer */
	for( ; GGA_Buffer[index]!=','; index++){
		Longitude_Buffer[long_index]= GGA_Buffer[index];
		long_index++;
	}
	
	Longitude_Buffer[long_index++] = GGA_Buffer[index++];
	Longitude_Buffer[long_index]   = GGA_Buffer[index]; /* get direction */
	convert_to_degrees(Longitude_Buffer);
	sei();
}

/********************************************************************************************/

/* Function to get Altitude from GGA Buffer */
void get_altitude(u16 alt_pointer){
	cli();
	u8 alt_index;
	u8 index = alt_pointer+1;
	alt_index=0;
	/* parse Altitude in GGA string stored in buffer */
	for( ; GGA_Buffer[index]!=','; index++){
		Altitude_Buffer[alt_index]= GGA_Buffer[index];
		alt_index++;
	}
	
	Altitude_Buffer[alt_index] = GGA_Buffer[index+1];
	sei();
}

/********************************************************************************************/

/* Function to convert time to UTC */
void convert_time_to_UTC()
{
	unsigned int hour, min, sec;
	u32 Time_value;
	
	Time_value = atol(Time_Buffer);       /* convert string to integer */
	hour = (Time_value / 10000);          /* extract hour from integer */
	min  = (Time_value % 10000) / 100;    /* extract minute from integer */
	sec  = (Time_value % 10000) % 100;    /* extract second from integer*/

	sprintf(Time_Buffer, "%d:%d:%d", hour,min,sec);
	
}

/********************************************************************************************/

/* Function to convert Latitude and Longitude */
void convert_to_degrees(char *raw){
	
	double value;
	float decimal_value,temp;
	
	S32 degrees;
	
	float position;
	value = atof(raw);    /* convert string into float for conversion */
	
	/* convert raw latitude/longitude into degree format */
	decimal_value = (value/100);
	degrees       = (int)(decimal_value);
	temp          = (decimal_value - (int)decimal_value)/0.6;
	position      = (float)degrees + temp;
	
	dtostrf(position, 6, 4, degrees_buffer);  /* convert float value into string */
}

/********************************************************************************************/

/* Function to check data comes from GPS */
void check_Gps(void)
{
	u8 oldsrg = SREG;    //can be neglected
	cli();
	char received_char = USART1_ReceiveNoBlock();
	
	if(received_char =='$'){                 /* check for '$' */
		GGA_Index = 0;
		CommaCounter = 0;
		IsItGGAString = false;
	}
	else if(IsItGGAString == true){          /* if true save GGA info. into buffer */
		if(received_char == ',' ) GGA_Pointers[CommaCounter++] = GGA_Index;     /* store instances of ',' in buffer */
		GGA_Buffer[GGA_Index++] = received_char;
	}
	else if(GGA_CODE[0] == 'G' && GGA_CODE[1] == 'G' && GGA_CODE[2] == 'A'){    /* check for GGA string */
		IsItGGAString = true;
		GGA_CODE[0] = 0; GGA_CODE[1] = 0; GGA_CODE[2] = 0;
	}
	else{
		GGA_CODE[0] = GGA_CODE[1];  GGA_CODE[1] = GGA_CODE[2]; GGA_CODE[2] = received_char;
	}
	SREG = oldsrg;
}