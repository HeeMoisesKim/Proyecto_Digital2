

/* 
 * File:     libreriash
 * Author:   RobertoCaceres
 * Comments: prueba1
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  

unsigned char ADCValor     = 0;
unsigned char ANDMOST      = 0b11110000;
unsigned char ANDLESS      = 0b00001111;
unsigned char D1           = 0;
unsigned char D2           = 0;
unsigned char FlagT        = 0;
unsigned char M1           = 0;
unsigned char M2           = 0;
unsigned char Show         = 0;
unsigned char multiplexor  = 0;

//aca van las funciones de las librerias que estaran en el archivo C

void ADC(void);
void MULTIPLEXEO(void);
void RADC  (void);

#endif /* XC_HEADER_TEMPLATE_H */