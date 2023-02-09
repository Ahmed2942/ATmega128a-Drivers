#include "DIO_Interface.h"
const DIO_Pinstastus_type PinStatus[TOTAL_PINS]=
{
	OUTPUT,      /* Port A Pin 0  * AD0*/ 
	OUTPUT,      /* Port A Pin 1  * AD1*/ 
	OUTPUT,      /* Port A Pin 2  * AD2*/ 
	OUTPUT,      /* Port A Pin 3  * AD3*/ 
	OUTPUT,      /* Port A Pin 4  * AD4*/ 
	OUTPUT,      /* Port A Pin 5  * AD5*/ 
	OUTPUT,      /* Port A Pin 6  * AD6*/ 
	OUTPUT,      /* Port A Pin 7  * AD7*/ 
	
	OUTPUT,      /* Port B Pin 0  * SS   */
	OUTPUT,      /* Port B Pin 1  * SCK  */
	OUTPUT,		 /* Port B Pin 2  * MOSI */
	OUTPUT,		 /* Port B Pin 3  * MISO */
	OUTPUT,		 /* Port B Pin 4  * OC0  */
	OUTPUT,		 /* Port B Pin 5  * OC1A */
	OUTPUT,		 /* Port B Pin 6  * OC1B */
	OUTPUT,		 /* Port B Pin 7  * OC1C/OC2 */
	
	OUTPUT,		 /* Port C Pin 0  * A8  */
	OUTPUT,		 /* Port C Pin 1  * A9  */
	OUTPUT,		 /* Port C Pin 2  * A10 */
	OUTPUT,		 /* Port C Pin 3  * A11 */
	OUTPUT,		 /* Port C Pin 4  * A12 */
	OUTPUT,		 /* Port C Pin 5  * A13 */
	OUTPUT,		 /* Port C Pin 6  * A14 */
	OUTPUT,		 /* Port C Pin 7  * A15 */
	
	OUTPUT,		 /* Port D Pin 0  * SCL  /INT0 */
	OUTPUT,		 /* Port D Pin 1  * SDA  /INT1 */
	INFREE,      /* Port D Pin 2  * RXD1 /INT2 */
	OUTPUT,      /* Port D Pin 3  * TXD1 /INT3 */
	OUTPUT,		 /* Port D Pin 4  * ICP1 */
	OUTPUT,		 /* Port D Pin 5  * XCK1 */
	INFREE,		 /* Port D Pin 6  * T1 */
	OUTPUT,		 /* Port D Pin 7  * T2 */
	
	OUTPUT,      /* Port E Pin 0  * RXD0 /PDI  */ 
	OUTPUT,      /* Port E Pin 1  * TXD0 /PDO  */ 
	OUTPUT,      /* Port E Pin 2  * XCK0 /AIN0 */ 
	OUTPUT,      /* Port E Pin 3  * OC3A /AIN1 */ 
	OUTPUT,      /* Port E Pin 4  * OC3B /INT4 */ 
	OUTPUT,      /* Port E Pin 5  * OC3C /INT5 */ 
	OUTPUT,      /* Port E Pin 6  * T3   /INT6 */ 
	OUTPUT,      /* Port E Pin 7  * ICP3 /INT7 */ 
	
	INFREE,      /* Port F Pin 0  * ADC0*/           //if you used it must be INFREE
	OUTPUT,      /* Port F Pin 1  * ADC1*/           //if you used it must be INFREE
	OUTPUT,      /* Port F Pin 2  * ADC2*/           //if you used it must be INFREE
	OUTPUT,      /* Port F Pin 3  * ADC3*/           //if you used it must be INFREE
	OUTPUT,      /* Port F Pin 4  * ADC4 /TCK */     //if you used it must be INFREE
	OUTPUT,      /* Port F Pin 5  * ADC5 /TMS */     //if you used it must be INFREE
	OUTPUT,      /* Port F Pin 6  * ADC6 /TDO */     //if you used it must be INFREE
	OUTPUT,      /* Port F Pin 7  * ADC7 /TDI */     //if you used it must be INFREE
	
	OUTPUT,      /* Port G Pin 0  * WR    */ 
	OUTPUT,      /* Port G Pin 1  * RD    */ 
	OUTPUT,      /* Port G Pin 2  * ALE   */ 
	OUTPUT,      /* Port G Pin 3  * TOSC2 */ 
	OUTPUT,      /* Port G Pin 4  * TOSC1 */ 
	
	
	
	
};

