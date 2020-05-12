/* 
 * File:   UART Lib para Proyecto 1 Digital II
 * Author:  Carlos Alonzo
 * Comments:
 * Revision history: 
 */


// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __UART_H_
#define	__UART_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>


void USART_setup(uint16_t baudrate, uint8_t tx_enable, uint8_t rc_enable, uint8_t sincrono_asincrono);
void enviar_dato(uint8_t dato);




#endif	/* __UART_H_ */