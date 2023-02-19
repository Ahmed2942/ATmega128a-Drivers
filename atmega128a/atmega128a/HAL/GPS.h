
#ifndef GPS_H_
#define GPS_H_

#include "MemMap.h"
#include "Std_types.h"
#include "USART1.h"
#include "USART_Services.h"
#include <util/delay.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#define SREG    (*(volatile unsigned char*)0x5f)
#define Buffer_Size 150
#define degrees_buffer_size 20

void check_Gps(void);
void convert_time_to_UTC(void);
void convert_to_degrees(char *);
void get_gpstime(void);
void get_latitude(u16 lat_pointer);
void get_longitude(u16 long_pointer);
void get_altitude(u16 alt_pointer);



#endif /* GPS_H_ */