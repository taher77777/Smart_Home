/********************		Author: TAHER MOHAMED	**************/
/********************		Layer: MCAL				**************/
/********************		SWC: EXTI				**************/
/********************		Version: 1.00			**************/
/********************		Date: 28-8-2020			**************/
/*****************************************************************/
/*****************************************************************/

#ifndef EXTI_REGISTER_H_
#define EXTI_REGISTER_H_

/* to enable interrubt */

#define GICR	 		*((volatile u8*)0x5B)
#define GICR_INT1		7
#define GICR_INT0		6
#define GICR_INT2		5

/* rising when interrubt is done */
#define GIFR		 	*((volatile u8*)0x5A)

/* set sense (rising edge , failing edge , LOW level ) in INT1 and INT0 */
#define MCUCR		 	*((volatile u8*)0x55)
#define MCUCR_ISC11		3
#define MCUCR_ISC10		2
#define MCUCR_ISC01		1
#define MCUCR_ISC00		0

/* set sense (rising edge , failing edge ) in INT2  */

#define MCUCSR	 		*((volatile u8*)0x54)
#define MCUCSR_INT2		6

#endif