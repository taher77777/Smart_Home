/*Smart_Home*/
#include "STD_TYPE.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "PORT_interface.h"
#include "USART_interface.h"
#include "GIE_interface.h"
#include "EXTI_interface.h"
#include "LED_interface.h"
#include "KEYPAD_interface.h"
#include <util/delay.h>
/****************PINS*************************************************************/
/*pins
 * 			D0  RX input
 * 			D1  TX output
 * 			D2  int0 input / pullup switch
 * 			A1,A2,A3 LEDS OUTPUT
 * 			protB for KEYBAD 0-->3 out & high
 * 							 4-->7 input & pullup
 * 			D7 door out
 * 			D6 fan  out                           */
/**************************END****************************************************/
/*************************macros**************************************************/
#define DOOR_ON       1
#define DOOR_off      0

#define FAN_ON        1
#define FAN_off       0
/*****************************END**************************************************/
/*************************global variables*****************************************/
/* Leds` Counter */
u8 Globel_u8LEDS_COUNTER=0;
/* Fan`s Status */
u8 Globel_u8Fan_Status=FAN_off;
/* Door`s Status */
u8 Globel_u8Door_Status=DOOR_off;
/*first time for system*/
u8 Global_u8StateSystem=0;
/*password*/
u8 Global_u8Password[4]={1,2,2,2};
/*****************************END***************************************************/
/*****************function Prototype************************************************/
void EXTI_ISR(void);
void SHOW();
void OpenLed(u8 Led_Num);
void CloseLed(u8 Led_Num);
u8   KeybadInput();
void controlled();
void controlfan();
void controldoor();
void Openfan();
void Closefan();
void Opendoor();
void Closedoor();
/***********************END*********************************************************/
void main (void)
{
	PORT_voidInit();
	EXTI_u8Int0SetCallBack(EXTI_ISR);
	EXTI_voidInt0Init();
	USART_voidInit();
	GIF_voidEnable();
	SHOW();
	while(1)
	{

	}
}

void EXTI_ISR (void)
{
	u8 Local_KEY;
	UART_voidsendstring("\n\rTO control LEDS choose '1' \n\rTo control DOOR choose '2'\n\rTo control FAN choose  '3' \n\r" );
	Local_KEY=KeybadInput();
	switch (Local_KEY)
	{
	case 1 : controlled(); break;
	case 2 : controlfan(); break;
	case 3 : controldoor(); break;
	default : UART_voidsendstring("\n\rwrong input\n\r") ;EXTI_ISR(); break;
	}
	SHOW();
	EXTI_ISR();
}
void SHOW()
{
	UART_voidsendstring("\n\r*****************************************\n\r");
	UART_voidsendstring("number of on LED is  ");
	UART_voidSendNumber(Globel_u8LEDS_COUNTER);
	UART_voidsendstring("\n\r");
	UART_voidsendstring("FAN ");
	UART_voidsendstring(Globel_u8Fan_Status==FAN_off?"  OFF":"  ON");
	UART_voidsendstring("\n\r");
	UART_voidsendstring("DOOR ");
	UART_voidsendstring(Globel_u8Door_Status==DOOR_off?"  OFF":"  ON");
	UART_voidsendstring("\n\r");
	if(Global_u8StateSystem==0)
	{
	UART_voidsendstring("\n\rLogin to the system press the switch\n\r");
	Global_u8StateSystem++;
	}
}
void OpenLed(u8 Led_Num)
{
	if(Globel_u8LEDS_COUNTER<3)
	{
	Globel_u8LEDS_COUNTER++;
	switch(Led_Num)
	{
	case 1:LED_voidTurnOn(DIO_u8PORTA,DIO_u8PIN0);break;
	case 2:LED_voidTurnOn(DIO_u8PORTA,DIO_u8PIN1);break;
	case 3:LED_voidTurnOn(DIO_u8PORTA,DIO_u8PIN2);break;
	}
	UART_voidsendstring("\n\rthe led is opened\n\r");
	}
	else
	{
		UART_voidsendstring("\n\rALL LEDS ARE OPENED\n\r");
	}


}
void CloseLed(u8 Led_Num)
{
	if(Globel_u8LEDS_COUNTER>0)
	{
	Globel_u8LEDS_COUNTER--;
	switch(Led_Num)
	{
	case 1:LED_voidTurnOff(DIO_u8PORTA,DIO_u8PIN0);break;
	case 2:LED_voidTurnOff(DIO_u8PORTA,DIO_u8PIN1);break;
	case 3:LED_voidTurnOff(DIO_u8PORTA,DIO_u8PIN2);break;
	}
	UART_voidsendstring("\n\rthe led is closed\n\r");
	}
	else
	{
		UART_voidsendstring("\n\rALL LEDS ARE CLOSED\n\r");
	}

}
u8   KeybadInput()
{
	u8 x;
	do{
		x=KPD_u8PressedKey();
	}
	while(x==0xff);
	return x;
}
void controlled()
{
	u8 Local_KEY;
	UART_voidsendstring("\n\ropen led1 '1' \n\ropen led2 '2' \n\ropen led3 '3' \n\rclose led1 '4' \n\rclose led2 '5' \n\rclose led3 '6' \n\r" );
	Local_KEY=KeybadInput();
	switch (Local_KEY)
	{
	case 1 : OpenLed(1); break;
	case 2 : OpenLed(2); break;
	case 3 : OpenLed(3); break;
	case 4 : CloseLed(1); break;
	case 5 : CloseLed(2); break;
	case 6 : CloseLed(3); break;
	default: UART_voidsendstring("\n\rwrong input again \n\r");controlled();break;
	}

}
void controlfan()
{
	u8 Local_KEY;
	UART_voidsendstring("\n\ropen fan '1' \n\rclose fan '2' \n\r" );
	Local_KEY=KeybadInput();
	switch (Local_KEY)
	{
	case 1 :Openfan() ; break;
	case 2 : Closefan(); break;
	default: UART_voidsendstring("\n\rwrong input again\n\r");controlfan();break;
	}

}
void controldoor()
{
	u8 Local_KEY;
	UART_voidsendstring("\n\ropen door '1' \n\rclose door '2' \n\r" );
	Local_KEY=KeybadInput();
	switch (Local_KEY)
	{
	case 1 :Opendoor() ; break;
	case 2 :Closedoor(); break;
	default: UART_voidsendstring("\n\rwrong input again\n\r");controldoor();break;
	}
}
	void Openfan()
	{
		Globel_u8Fan_Status=FAN_ON;
		DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN6,DIO_u8PIN_HIGH);
		UART_voidsendstring("\n\rthe fan is opened\n\r");

	}
	void Closefan()
	{
		Globel_u8Fan_Status=FAN_off;
		DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN6,DIO_u8PIN_LOW);
		UART_voidsendstring("\n\rthe fan is closed\n\r");
	}
	void Opendoor()
	{
		UART_voidsendstring("\n\renter password to open the door 4 digit\n\r");
		u8 true=1;
		u8 count=0;
		u8 Local_password[4];
		for(count=0;count<4;count++)
		{
			Local_password[count]=KeybadInput();
		}
		for(count=0;count<4;count++)
		{
			if(Local_password[count]!=Global_u8Password[count])
			{
				true=0;
			}
		}
		if (true==1)
		{
		UART_voidsendstring("\n\rthe password is correct\n\r");
		Globel_u8Door_Status=DOOR_ON;
		DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_HIGH);
		UART_voidsendstring("\n\rthe door is opened\n\r");
		}
		else
		{
		UART_voidsendstring("\n\rthe password is not correct again\n\r");
		Opendoor();
		}
	}
	void Closedoor()
	{
		UART_voidsendstring("\n\renter password to close the door 4 digit\n\r");
		u8 true=1;
		u8 count=0;
		u8 Local_password[4];
		for(count=0;count<4;count++)
		{
			Local_password[count]=KeybadInput();
		}
		for(count=0;count<4;count++)
		{
			if(Local_password[count]!=Global_u8Password[count])
			{
				true=0;
			}
		}
		if (true==1)
		{
		UART_voidsendstring("\n\rthe password is correct\n\r");
		Globel_u8Door_Status=DOOR_off;
		DIO_u8SetPinValue(DIO_u8PORTD,DIO_u8PIN7,DIO_u8PIN_LOW);
		UART_voidsendstring("\n\rthe door is closed\n\r");
		}
		else
		{
		UART_voidsendstring("\n\rthe password is not correct again\n\r");
		Closedoor();
		}

	}
