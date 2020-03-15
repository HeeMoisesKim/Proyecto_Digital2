/* 
 * File:   
 * Author: Carlos Alonzo
 * Comments:
 *Se utilizó y se adaptaron las librerías de Ligo George 
 *de la página www.electrosome.com
 * Se utilizó una adaptación de la función convertir decimales a enteros, basado en idea de Ignacio Ramírez.
 * Se utilizó parte de la adaptación de Pablo Mazariegos. (mismo enlace)
 * Revision history: 
 */
#ifndef RS
#define RS RD5
#endif

#ifndef RW
#define RW RD6
#endif

#ifndef EN
#define EN RD7
#endif

#ifndef D0
#define D0 RA0
#endif

#ifndef D1
#define D1 RA1
#endif

#ifndef D2
#define D2 RA2
#endif

#ifndef D3
#define D3 RA3
#endif

#ifndef D4
#define D4 RA4
#endif

#ifndef D5
#define D5 RA5
#endif

#ifndef D6
#define D6 RA6
#endif

#ifndef D7
#define D7 RA7
#endif

#ifndef __LCD_FLOWMETER_H_
#define	__LCD_FLOWMETER_H_

#include <xc.h> // include processor files - each processor file is guarded.  
#include<stdint.h>

void LCD_sep(uint8_t val_cmd);
void LCD_Cmd(uint8_t cmd);
void LCD_clear(void);
void LCD_pos_cursor(uint8_t fila, uint8_t casilla);
void LCD_Write_Char(uint8_t caracter);
void LCD_Write_String(uint8_t *string);
void LCD_setup(void);
void Write_entero(uint8_t entero);
void Write_float(uint8_t entero, uint8_t decimal, uint8_t pos_inicial);





#endif	/* __LCD_FLOWMETER_H_ */
