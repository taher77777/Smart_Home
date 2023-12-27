/********************		Author: TAHER MOHAMED	**************/
/********************		Layer: MCAL				**************/
/********************		SWC: USART				**************/
/********************		Version: 1.00			**************/
/********************		Date: 28-8-2020			**************/
/*****************************************************************/
/*****************************************************************/

#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_
void USART_voidInit(void);               //func to initial
void USART_voidSend(u8 Copy_u8data);     //func to transmit data
u8 USART_u8Receive(void);                //func to receive data
void UART_voidsendstring(u8 *str);
void UART_voidSendNumber(u8 Copy_u8number);
#endif
