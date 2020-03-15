/*
 * File:   peso.c
 * Author: moise
 *
 * Created on March 1, 2020, 9:15 PM
 */


#include <xc.h>
#include <stdint.h>
#include <pic16f887.h>
#include "peso.h"

#define _XTAL_FREQ 4000000

uint32_t celdaSetup(void){
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 1;
    ANSEL = 0;
    PORTAbits.RA0 = 0;
    __delay_ms(4000);
    uint32_t tare = 0;
    tare = tarar();
    return tare;
}

uint32_t celdaRead(void){
    uint8_t i;
    uint32_t valor=0;
    uint32_t v;
    while(PORTAbits.RA1);
    for(i=0;i<24;i++){
        PORTAbits.RA0 = 1;
        __delay_us(1);
        PORTAbits.RA0 = 0;
        __delay_us(1);
        valor <<= 1;
        v = 0x0+PORTAbits.RA1;;
        valor = valor|v;
    }
    PORTAbits.RA0 = 1;
    __delay_us(1);
    PORTAbits.RA0 = 0;
    /*__delay_us(1);
    PORTAbits.RA0 = 1;
    __delay_us(1);
    PORTAbits.RA0 = 0;
    __delay_us(1);
    PORTAbits.RA0 = 1;
    __delay_us(1);
    PORTAbits.RA0 = 0;
    __delay_us(1);*/
    valor = valor-0x80000000;
    return valor;
}

uint32_t tarar(void){
    uint8_t i;
    uint32_t sum;
    uint32_t total=celdaRead();
    uint32_t pasado;
    for (i = 0; i < 20; i++) {
        pasado = total;
		total =(1-0.65)*celdaRead()+0.65*pasado;
	}
	return total;
}