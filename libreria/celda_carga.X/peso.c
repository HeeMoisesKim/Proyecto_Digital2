/*
 * File:   peso.c
 * Author: moise
 *
 * Created on March 1, 2020, 9:15 PM
 */


#include <xc.h>
#include <stdint.h>
#include "peso.h"

#define _XTAL_FREQ 4000000
void celdaSetup(void){
    TRISAbits.TRISA0 = 0;
    TRISAbits.TRISA1 = 1;
    
    PORTAbits.RA1 = 0;
    PORTAbits.RA0 = 0;
    return;
}

uint32_t celdaRead(void){
    uint8_t i;
    uint32_t valor;
    uint32_t v;
    while(PORTAbits.RA1)
    {}
    for(i=0;i<24;i++){
        v = 0x0+PORTAbits.RA1;;
        valor = valor|v;
        valor <<= 1;
        PORTAbits.RA0 = 1;
        __delay_ms(1);
        PORTAbits.RA0 = 0;
        __delay_ms(1);
    }
    
    return valor;
}