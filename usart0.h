/*
 * usart0.h
 *
 *  Created on: Oct 13, 2021
 *      Author: saranyan
 */

#ifndef USART0_H_
#define USART0_H_

//-----Function Declarations------//
void USART0_Init(unsigned int ubrr);
void USART0_Send_Data(register char * _data);

#endif /* USART0_H_ */
