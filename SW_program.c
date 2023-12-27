/***********************************************************************/
/***********************************************************************/
/*****************    AUTHOR: TAHER MOHAMED   **************************/
/*****************    LAYER:  HAL             **************************/
/*****************    SWC:   SWITCH           **************************/
/*****************    VERSION:1.00            **************************/
/***********************************************************************/
/***********************************************************************/

#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"

#include "SW_interface.h"
#include "SW_config.h"
#include "SW_private.h"


#if SW_TYPE==PULL_UP 
u8 SW_u8GetState(u8 Copy_u8Port,u8 Copy_u8Pin)
{
	u8 SW_u8State=0;
	u8 PRESSED;
	DIO_u8GetPinValue(Copy_u8Port,Copy_u8Pin,&SW_u8State);
		
		if(SW_u8State)
		{
			PRESSED=SW_NOT_PRESSED;
		}
		else
		{
			PRESSED=SW_PRESSED;
		}
		
		return PRESSED;

}

#elif SW_TYPE==PULL_DOWN
u8 SW_u8GetState(u8 Copy_u8Port,u8 Copy_u8Pin,u8 SW_Pull_Type)
{
	u8 SW_u8State=0;
	u8 PRESSED;
	DIO_u8GetPinValue(Copy_u8Port,Copy_u8Pin,&SW_u8State);
		
		if(SW_u8State)
		{
			PRESSED=SW_PRESSED;
		}
		else
		{
			PRESSED=SW_NOT_PRESSED;
		}

	return PRESSED;
}
#endif
