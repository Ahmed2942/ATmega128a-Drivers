 
#ifndef MEMMAP_H_
#define MEMMAP_H_

#define _BV(bit) (1 << (bit))
#define _VECTOR(N) __vector_ ## N


/************************************DIO_Registers **********************************/
#define DDRA    (*(volatile unsigned char*)0x3A)
#define DDRB    (*(volatile unsigned char*)0x37)
#define DDRC    (*(volatile unsigned char*)0x34)
#define DDRD    (*(volatile unsigned char*)0x31)
#define DDRE    (*(volatile unsigned char*)0x22)
#define DDRF    (*(volatile unsigned char*)0x61)
#define DDRG    (*(volatile unsigned char*)0x64)


#define PINA    (*(volatile unsigned char*)0x39)
#define PINB    (*(volatile unsigned char*)0x36)
#define PINC    (*(volatile unsigned char*)0x33)
#define PIND    (*(volatile unsigned char*)0x30)
#define PINE    (*(volatile unsigned char*)0x21)
#define PINF    (*(volatile unsigned char*)0x20)
#define PING    (*(volatile unsigned char*)0x63)


#define PORTA   (*(volatile unsigned char*)0x3B)
#define PORTB   (*(volatile unsigned char*)0x38)
#define PORTC   (*(volatile unsigned char*)0x35)
#define PORTD   (*(volatile unsigned char*)0x32)
#define PORTE   (*(volatile unsigned char*)0x23)
#define PORTF   (*(volatile unsigned char*)0x62)
#define PORTG   (*(volatile unsigned char*)0x65)


/**********************************ADC_Registers***********************************************/
#ifndef __ASSEMBLER__
#define ADC     (*(volatile unsigned short*)0x24)
#endif

#define ADCW    (*(volatile unsigned short*)0x24)
#define ADCL    (*(volatile unsigned char*)0x24)
#define ADCH    (*(volatile unsigned char*)0x25)

#define ADCSRA  (*(volatile unsigned char*)0x26)
#define ADPS0   0
#define ADPS1   1
#define ADPS2   2
#define ADIE    3
#define ADIF    4
#define ADFR    5
#define ADSC    6
#define ADEN    7

#define ADMUX   (*(volatile unsigned char*)0x27)
#define MUX0    0
#define MUX1    1
#define MUX2    2
#define MUX3    3
#define MUX4    4
#define ADLAR   5
#define REFS0   6
#define REFS1   7

/**********************************Analog Comparetor_CA_Registers***********************************************/
#define ACSR    (*(volatile unsigned char*)0x28)
#define ACIS0   0
#define ACIS1   1
#define ACIC    2
#define ACIE    3
#define ACI     4
#define ACO     5
#define ACBG    6
#define ACD     7

/******************************************** Interrupt*******************************************************/
#define MCUCR   (*(volatile unsigned char*)0x55)
#define IVCE    0
#define IVSEL   1
#define SM2     2
#define SM0     3
#define SM1     4
#define SE      5
#define SRW10   6
#define SRE     7

/*External Interrupt*/

#define MCUCSR  (*(volatile unsigned char*)0x54)
#define PORF    0
#define EXTRF   1
#define BORF    2
#define WDRF    3
#define JTRF    4
#define JTD     7

#define EICRA   (*(volatile unsigned char*)0x6A)
#define ISC00   0
#define ISC01   1
#define ISC10   2
#define ISC11   3
#define ISC20   4
#define ISC21   5
#define ISC30   6
#define ISC31   7

#define EICRB   (*(volatile unsigned char*)0x5A)
#define ISC40   0
#define ISC41   1
#define ISC50   2
#define ISC51   3
#define ISC60   4
#define ISC61   5
#define ISC70   6
#define ISC71   7

#define EIFR    (*(volatile unsigned char*)0x58)
#define INTF0   0
#define INTF1   1
#define INTF2   2
#define INTF3   3
#define INTF4   4
#define INTF5   5
#define INTF6   6
#define INTF7   7

#define EIMSK   (*(volatile unsigned char*)0x59)
#define INT0    0
#define INT1    1
#define INT2    2
#define INT3    3
#define INT4    4
#define INT5    5
#define INT6    6
#define INT7    7




/****************************************************timer0******************************************/

#define OCR0    (*(volatile unsigned char*)0x51)
#define TCNT0   (*(volatile unsigned char*)0x52)

#define TCCR0   (*(volatile unsigned char*)0x53)
#define CS00    0
#define CS01    1
#define CS02    2
#define WGM01   3
#define COM00   4
#define COM01   5
#define WGM00   6
#define FOC0    7

#define ASSR    (*(volatile unsigned char*)0x50)
#define TCR0UB  0
#define OCR0UB  1
#define TCN0UB  2
#define AS0     3

#define TIMSK   (*(volatile unsigned char*)0x57)
#define TOIE0   0
#define OCIE0   1
#define TOIE1   2
#define OCIE1B  3
#define OCIE1A  4
#define TICIE1  5
#define TOIE2   6
#define OCIE2   7

#define TIFR    (*(volatile unsigned char*)0x56)
#define TOV0    0
#define OCF0    1
#define TOV1    2
#define OCF1B   3
#define OCF1A   4
#define ICF1    5
#define TOV2    6
#define OCF2    7

#define SFIOR   (*(volatile unsigned char*)0x40)
#define PSR321  0
#define PSR0    1
#define ACME    3
#define PUD     2
#define TSM     7

/****************************************************timer1******************************************/
#define TCCR1A  (*(volatile unsigned char*)0x4F)
#define WGM10   0
#define WGM11   1
#define COM1C0  2
#define COM1C1  3
#define COM1B0  4
#define COM1B1  5
#define COM1A0  6
#define COM1A1  7

#define TCCR1B  (*(volatile unsigned char*)0x4E)
#define CS10    0
#define CS11    1
#define CS12    2
#define WGM12   3
#define WGM13   4
#define ICES1   6
#define ICNC1   7

#define TCCR1C  (*(volatile unsigned char*)0x7A)
#define FOC1C   5
#define FOC1B   6
#define FOC1A   7

/* Combine TCNT1L and TCNT1H */
#define TCNT1   (*(volatile unsigned short*)0x4C)
#define TCNT1L  (*(volatile unsigned char*)0x4C)
#define TCNT1H  (*(volatile unsigned char*)0x4D)

/* Combine OCR1AL and OCR1AH */
#define OCR1A   (*(volatile unsigned short*)0x4A)
#define OCR1AL  (*(volatile unsigned char*)0x4A)
#define OCR1AH  (*(volatile unsigned char*)0x4B)

/* Combine OCR1BL and OCR1BH */
#define OCR1B   (*(volatile unsigned short*)0x48)
#define OCR1BL  (*(volatile unsigned char*)0x48)
#define OCR1BH  (*(volatile unsigned char*)0x49)

/* Combine OCR1CL and OCR1CH */
#define OCR1C   (*(volatile unsigned short*)0x78)
#define OCR1CL  (*(volatile unsigned char*)0x78)
#define OCR1CH  (*(volatile unsigned char*)0x79)

/* Combine ICR1L and ICR1H */
#define ICR1    (*(volatile unsigned short*)0x46)
#define ICR1L   (*(volatile unsigned char*)0x46)
#define ICR1H   (*(volatile unsigned char*)0x47)


/****************************************************timer3******************************************/
#define TCCR3A  (*(volatile unsigned char*)0x8B)
#define WGM30   0
#define WGM31   1
#define COM3C0  2
#define COM3C1  3
#define COM3B0  4
#define COM3B1  5
#define COM3A0  6
#define COM3A1  7

#define TCCR3B  (*(volatile unsigned char*)0x8A)
#define CS30    0
#define CS31    1
#define CS32    2
#define WGM32   3
#define WGM33   4
#define ICES3   6
#define ICNC3   7

#define TCCR3C  (*(volatile unsigned char*)0x8C)
#define FOC3C   5
#define FOC3B   6
#define FOC3A   7

/* Combine TCNT3L and TCNT3H */
#define TCNT3   (*(volatile unsigned short*)0x88)
#define TCNT3L  (*(volatile unsigned char*)0x88)
#define TCNT3H  (*(volatile unsigned char*)0x89)

/* Combine OCR3AL and OCR3AH */
#define OCR3A   (*(volatile unsigned short*)0x86)
#define OCR3AL  (*(volatile unsigned char*)0x86)
#define OCR3AH  (*(volatile unsigned char*)0x87)

/* Combine OCR3BL and OCR3BH */
#define OCR3B   (*(volatile unsigned short*)0x84)
#define OCR3BL  (*(volatile unsigned char*)0x84)
#define OCR3BH  (*(volatile unsigned char*)0x85)

/* Combine OCR3CL and OCR3CH */
#define OCR3C   (*(volatile unsigned short*)0x82)
#define OCR3CL  (*(volatile unsigned char*)0x82)
#define OCR3CH  (*(volatile unsigned char*)0x83)

/* Combine ICR3L and ICR3H */
#define ICR3    (*(volatile unsigned short*)0x80)
#define ICR3L   (*(volatile unsigned char*)0x80)
#define ICR3H   (*(volatile unsigned char*)0x81)

#define ETIMSK  (*(volatile unsigned char*)0x7D)
#define OCIE1C  0
#define OCIE3C  1
#define TOIE3   2
#define OCIE3B  3
#define OCIE3A  4
#define TICIE3  5

#define ETIFR   (*(volatile unsigned char*)0x7C)
#define OCF1C   0
#define OCF3C   1
#define TOV3    2
#define OCF3B   3
#define OCF3A   4
#define ICF3    5


/****************************************************timer2******************************************/
#define TCNT2   (*(volatile unsigned char*)0x44)
#define OCR2    (*(volatile unsigned char*)0x43)

#define TCCR2   (*(volatile unsigned char*)0x45)
#define CS20    0
#define CS21    1
#define CS22    2
#define WGM21   3
#define COM20   4
#define COM21   5
#define WGM20   6
#define FOC2    7

/*************************WATCH DOG TIMER*****************************/
#define WDTCR   (*(volatile unsigned char*)0x41)
#define WDP0    0
#define WDP1    1
#define WDP2    2
#define WDE     3
#define WDCE    4

/**********************************SPI******************************/
#define SPDR    (*(volatile unsigned char*)0x2F)

#define SPCR    (*(volatile unsigned char*)0x2D)
#define SPR0    0
#define SPR1    1
#define CPHA    2
#define CPOL    3
#define MSTR    4
#define DORD    5
#define SPE     6
#define SPIE    7

#define SPSR    (*(volatile unsigned char*)0x2E)
#define SPI2X   0
#define WCOL    6
#define SPIF    7

/********************************USART***************************/

/*USART0*/
#define UDR0    (*(volatile unsigned char*)0x2C)

#define UCSR0A  (*(volatile unsigned char*)0x2B)
#define MPCM0   0
#define U2X0    1
#define UPE0    2
#define DOR0    3
#define FE0     4
#define UDRE0   5
#define TXC0    6
#define RXC0    7

#define UCSR0B  (*(volatile unsigned char*)0x2A)
#define TXB80   0
#define RXB80   1
#define UCSZ02  2
#define TXEN0   3
#define RXEN0   4
#define UDRIE0  5
#define TXCIE0  6
#define RXCIE0  7

#define UCSR0C  (*(volatile unsigned char*)0x95)
#define UCPOL0  0
#define UCSZ00  1
#define UCSZ01  2
#define USBS0   3
#define UPM00   4
#define UPM01   5
#define UMSEL0  6

#define UBRR0H  (*(volatile unsigned char*)0x90)
#define UBRR0L  (*(volatile unsigned char*)0x29)

/*USART1*/
#define UDR1    (*(volatile unsigned char*)0x9C)

#define UCSR1A  (*(volatile unsigned char*)0x9B)
#define MPCM1   0
#define U2X1    1
#define UPE1    2
#define DOR1    3
#define FE1     4
#define UDRE1   5
#define TXC1    6
#define RXC1    7

#define UCSR1B  (*(volatile unsigned char*)0x9A)
#define TXB81   0
#define RXB81   1
#define UCSZ12  2
#define TXEN1   3
#define RXEN1   4
#define UDRIE1  5
#define TXCIE1  6
#define RXCIE1  7

#define UCSR1C  (*(volatile unsigned char*)0x9D)
#define UCPOL1  0
#define UCSZ10  1
#define UCSZ11  2
#define USBS1   3
#define UPM10   4
#define UPM11   5
#define UMSEL1  6

#define UBRR1H  (*(volatile unsigned char*)0x98)
#define UBRR1L  (*(volatile unsigned char*)0x99)


/**************************************SPI*********************************/
#define TWAR    (*(volatile unsigned char*)0x72)
#define TWGCE   0
#define TWA0    1
#define TWA1    2
#define TWA2    3
#define TWA3    4
#define TWA4    5
#define TWA5    6
#define TWA6    7

#define TWBR    (*(volatile unsigned char*)0x70)

#define TWCR    (*(volatile unsigned char*)0x74)
#define TWIE    0
#define TWEN    2
#define TWWC    3
#define TWSTO   4
#define TWSTA   5
#define TWEA    6
#define TWINT   7

#define TWDR    (*(volatile unsigned char*)0x73)

#define TWSR    (*(volatile unsigned char*)0x71)
#define TWPS0   0
#define TWPS1   1
#define TWS3    3
#define TWS4    4
#define TWS5    5
#define TWS6    6
#define TWS7    7


/************************JTAG*****************************/
#define OCDR    (*(volatile unsigned char*)0x42)
#define OCDR0   0
#define OCDR1   1
#define OCDR2   2
#define OCDR3   3
#define OCDR4   4
#define OCDR5   5
#define OCDR6   6
#define OCDR7   7

/*********************BOOT LOADER**************/
#define SPMCSR  (*(volatile unsigned char*)0x68)
#define SPMEN   0
#define PGERS   1
#define PGWRT   2
#define BLBSET  3
#define RWWSRE  4
#define RWWSB   6
#define SPMIE   7

/******************************EEPROM********************/

/* Combine EEARL and EEARH */
#define EEAR    (*(volatile unsigned short*)0x3E)
#define EEARL   (*(volatile unsigned char*)0x3E)
#define EEARH   (*(volatile unsigned char*)0x3F)

#define EECR    (*(volatile unsigned char*)0x3C)
#define EERE    0
#define EEWE    1
#define EEMWE   2
#define EERIE   3

#define EEDR    (*(volatile unsigned char*)0x3D)

#define XMCRA   (*(volatile unsigned char*)0x6D)
#define SRW11   1
#define SRW00   2
#define SRW01   3
#define SRL0    4
#define SRL1    5
#define SRL2    6

#define XMCRB   (*(volatile unsigned char*)0x6C)
#define XMM0    0
#define XMM1    1
#define XMM2    2
#define XMBK    7

/*****************************SYSTEM CLOCK - OSCILLATOR***********************/

#define OSCCAL  (*(volatile unsigned char*)0x6F)
#define OSCCAL0 0
#define OSCCAL1 1
#define OSCCAL2 2
#define OSCCAL3 3
#define OSCCAL4 4
#define OSCCAL5 5
#define OSCCAL6 6
#define OSCCAL7 7


#define RAMPZ   (*(volatile unsigned char*)0x5B)
#define RAMPZ0  0
#define XDIV    (*(volatile unsigned char*)0x5C)

/* SP [0x5D..0x5E] */

/* SREG [0x5F] */

/***********************************************************************/
/* Values and associated defines */
#define SLEEP_MODE_IDLE (0x00<<2)
#define SLEEP_MODE_ADC (0x02<<2)
#define SLEEP_MODE_PWR_DOWN (0x04<<2)
#define SLEEP_MODE_PWR_SAVE (0x06<<2)
#define SLEEP_MODE_STANDBY (0x05<<2)
#define SLEEP_MODE_EXT_STANDBY (0x07<<2)

/* Interrupt vectors */
/* Vector 0 is the reset vector */
/* External Interrupt Request 0 */
#define INT0_vect                               _VECTOR(1)
#define INT0_vect_num                           1

/* External Interrupt Request 1 */
#define INT1_vect                               _VECTOR(2)
#define INT1_vect_num                           2

/* External Interrupt Request 2 */
#define INT2_vect                               _VECTOR(3)
#define INT2_vect_num                           3

/* External Interrupt Request 3 */
#define INT3_vect                               _VECTOR(4)
#define INT3_vect_num                           4

/* External Interrupt Request 4 */
#define INT4_vect                               _VECTOR(5)
#define INT4_vect_num                           5

/* External Interrupt Request 5 */
#define INT5_vect                               _VECTOR(6)
#define INT5_vect_num                           6

/* External Interrupt Request 6 */
#define INT6_vect                               _VECTOR(7)
#define INT6_vect_num                           7

/* External Interrupt Request 7 */
#define INT7_vect                               _VECTOR(8)
#define INT7_vect_num                           8

/* Timer/Counter2 Compare Match */
#define TIMER2_COMP_vect                        _VECTOR(9)
#define TIMER2_COMP_vect_num                    9

/* Timer/Counter2 Overflow */
#define TIMER2_OVF_vect                         _VECTOR(10)
#define TIMER2_OVF_vect_num                     10

/* Timer/Counter1 Capture Event */
#define TIMER1_CAPT_vect                        _VECTOR(11)
#define TIMER1_CAPT_vect_num                    11

/* Timer/Counter1 Compare Match A */
#define TIMER1_COMPA_vect                       _VECTOR(12)
#define TIMER1_COMPA_vect_num                   12

/* Timer/Counter Compare Match B */
#define TIMER1_COMPB_vect                       _VECTOR(13)
#define TIMER1_COMPB_vect_num                   13

/* Timer/Counter1 Overflow */
#define TIMER1_OVF_vect                         _VECTOR(14)
#define TIMER1_OVF_vect_num                     14

/* Timer/Counter0 Compare Match */
#define TIMER0_COMP_vect                        _VECTOR(15)
#define TIMER0_COMP_vect_num                    15

/* Timer/Counter0 Overflow */
#define TIMER0_OVF_vect                         _VECTOR(16)
#define TIMER0_OVF_vect_num                     16

/* SPI Serial Transfer Complete */
#define SPI_STC_vect                            _VECTOR(17)
#define SPI_STC_vect_num                        17

/* USART0, Rx Complete */
#define USART0_RX_vect                          _VECTOR(18)
#define USART0_RX_vect_num                      18

/* USART0 Data Register Empty */
#define USART0_UDRE_vect                        _VECTOR(19)
#define USART0_UDRE_vect_num                    19

/* USART0, Tx Complete */
#define USART0_TX_vect                          _VECTOR(20)
#define USART0_TX_vect_num                      20

/* ADC Conversion Complete */
#define ADC_vect                                _VECTOR(21)
#define ADC_vect_num                            21

/* EEPROM Ready */
#define EE_READY_vect                           _VECTOR(22)
#define EE_READY_vect_num                       22

/* Analog Comparator */ 
#define ANALOG_COMP_vect                        _VECTOR(23)
#define ANALOG_COMP_vect_num                    23

/* Timer/Counter1 Compare Match C */
#define TIMER1_COMPC_vect                       _VECTOR(24)
#define TIMER1_COMPC_vect_num                   24

/* Timer/Counter3 Capture Event */
#define TIMER3_CAPT_vect                        _VECTOR(25)
#define TIMER3_CAPT_vect_num                    25

/* Timer/Counter3 Compare Match A */
#define TIMER3_COMPA_vect                       _VECTOR(26)
#define TIMER3_COMPA_vect_num                   26

/* Timer/Counter3 Compare Match B */
#define TIMER3_COMPB_vect                       _VECTOR(27)
#define TIMER3_COMPB_vect_num                   27

/* Timer/Counter3 Compare Match C */
#define TIMER3_COMPC_vect                       _VECTOR(28)
#define TIMER3_COMPC_vect_num                   28

/* Timer/Counter3 Overflow */
#define TIMER3_OVF_vect                         _VECTOR(29)
#define TIMER3_OVF_vect_num                     29

/* USART1, Rx Complete */
#define USART1_RX_vect                         _VECTOR(30)
#define USART1_RX_vect_num                     30

/* USART1, Data Register Empty */
#define USART1_UDRE_vect                       _VECTOR(31)
#define USART1_UDRE_vect_num                   31

/* USART1, Tx Complete */
#define USART1_TX_vect                         _VECTOR(32)
#define USART1_TX_vect_num                     32

/* 2-wire Serial Interface */
#define TWI_vect                               _VECTOR(33)
#define TWI_vect_num                           33

/* Store Program Memory Read */
#define SPM_READY_vect                         _VECTOR(34)
#define SPM_READY_vect_num                     34



#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  define _VECTORS_SIZE 140
#else
#  define _VECTORS_SIZE 140U
#endif


/* Constants */

#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  define SPM_PAGESIZE 256
#  define FLASHSTART   0x0000
#  define FLASHEND     0x1FFFF
#else
#  define SPM_PAGESIZE 256U
#  define FLASHSTART   0x0000U
#  define FLASHEND     0x1FFFFU
#endif
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  define RAMSTART     0x0100
#  define RAMSIZE      4096
#  define RAMEND       0x10FF
#else
#  define RAMSTART     0x0100U
#  define RAMSIZE      4096U
#  define RAMEND       0x10FFU
#endif
#if (defined(__ASSEMBLER__) || defined(__IAR_SYSTEMS_ASM__))
#  define E2START     0
#  define E2SIZE      4096
#  define E2PAGESIZE  8
#  define E2END       0x0FFF
#else
#  define E2START     0U
#  define E2SIZE      4096U
#  define E2PAGESIZE  8U
#  define E2END       0x0FFFU
#endif
#define XRAMEND      RAMEND


/* Fuses */

#define FUSE_MEMORY_SIZE 3

/* Low Fuse Byte */
#define FUSE_SUT_CKSEL0  (unsigned char)~_BV(0)
#define FUSE_SUT_CKSEL1  (unsigned char)~_BV(1)
#define FUSE_SUT_CKSEL2  (unsigned char)~_BV(2)
#define FUSE_SUT_CKSEL3  (unsigned char)~_BV(3)
#define FUSE_SUT_CKSEL4  (unsigned char)~_BV(4)
#define FUSE_SUT_CKSEL5  (unsigned char)~_BV(5)
#define FUSE_BODEN       (unsigned char)~_BV(6)
#define FUSE_BODLEVEL    (unsigned char)~_BV(7)
#define LFUSE_DEFAULT    (FUSE_SUT_CKSEL1 & FUSE_SUT_CKSEL2 & FUSE_SUT_CKSEL3 & FUSE_SUT_CKSEL4)


/* High Fuse Byte */
#define FUSE_BOOTRST     (unsigned char)~_BV(0)
#define FUSE_BOOTSZ0     (unsigned char)~_BV(1)
#define FUSE_BOOTSZ1     (unsigned char)~_BV(2)
#define FUSE_EESAVE      (unsigned char)~_BV(3)
#define FUSE_CKOPT       (unsigned char)~_BV(4)
#define FUSE_SPIEN       (unsigned char)~_BV(5)
#define FUSE_JTAGEN      (unsigned char)~_BV(6)
#define FUSE_OCDEN       (unsigned char)~_BV(7)
#define HFUSE_DEFAULT    (FUSE_BOOTSZ0 & FUSE_BOOTSZ1 & FUSE_SPIEN & FUSE_JTAGEN)


/* Extended Fuse Byte */
#define FUSE_WDTON       (unsigned char)~_BV(0)
#define FUSE_M103C       (unsigned char)~_BV(1)
#define EFUSE_DEFAULT    (FUSE_M103C)



/* Lock Bits */
#define __LOCK_BITS_EXIST
#define __BOOT_LOCK_BITS_0_EXIST
#define __BOOT_LOCK_BITS_1_EXIST


/* Signature */
#define SIGNATURE_0 0x1E
#define SIGNATURE_1 0x97
#define SIGNATURE_2 0x02

/*interrupt functions*/

# define sei()  __asm__ __volatile__ ("sei" ::)
# define cli()  __asm__ __volatile__ ("cli" ::)
# define reti()  __asm__ __volatile__ ("reti" ::)
# define ret()  __asm__ __volatile__ ("ret" ::)

#  define ISR_NOBLOCK    __attribute__((interrupt))
#  define ISR_NAKED      __attribute__((naked))


#  define ISR(vector,...)            \
void vector (void) __attribute__ ((signal))__VA_ARGS__ ; \
void vector (void)


#endif /* MEMMAP_H_ */