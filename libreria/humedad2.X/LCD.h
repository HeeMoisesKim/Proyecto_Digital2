/* Microchip Technology Inc. and its subsidiaries.  You may use this software 
 * and any derivatives exclusively with Microchip products. 
 * 
 * THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS".  NO WARRANTIES, WHETHER 
 * EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY IMPLIED 
 * WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS FOR A 
 * PARTICULAR PURPOSE, OR ITS INTERACTION WITH MICROCHIP PRODUCTS, COMBINATION 
 * WITH ANY OTHER PRODUCTS, OR USE IN ANY APPLICATION. 
 *
 * IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
 * INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
 * WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP HAS 
 * BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE.  TO THE 
 * FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL CLAIMS 
 * IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT OF FEES, IF 
 * ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS SOFTWARE.
 *
 * MICROCHIP PROVIDES THIS SOFTWARE CONDITIONALLY UPON YOUR ACCEPTANCE OF THESE 
 * TERMS. 
 */

/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __LCD_H_
#define	__LCD_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

#define D7 PORTBbits.RB7
#define D6 PORTBbits.RB6
#define D5 PORTBbits.RB5
#define D4 PORTBbits.RB4
#define D3 PORTBbits.RB3
#define D2 PORTBbits.RB2
#define D1 PORTBbits.RB1
#define D0 PORTBbits.RB0
#define RS PORTDbits.RD7
#define RW PORTDbits.RD6
#define E PORTDbits.RD5
#define datos PORTB
#define clean 0x01
#define home 0x02

void lcd_setup(void);

void lcd_cursor(uint8_t a, uint8_t b);

void r_shift(uint8_t saltos);

void l_shift(uint8_t saltos);

void lcd_wchar(char dato);

void lcd_wstring(char *string);

void lcd_command(uint8_t a);

#endif	/* XC_HEADER_TEMPLATE_H */