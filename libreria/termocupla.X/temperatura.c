/*
 * File:   temperatura.c
 * Author: moise
 *
 * Created on March 1, 2020, 5:38 PM
 */


#include <xc.h>
#include <stdint.h>
#include "temperatura.h"

#define _XTAL_FREQ 4000000

void tSetup(void){
    ANSEL = 0;
    TRISAbits.TRISA0 = 0; //clk
    TRISAbits.TRISA1 = 0; //decidir si leer o no, 0 leer y 1 convertir
    TRISAbits.TRISA2 = 1; //la entrada de la termocupla
    
    cs = 1;
    PORTAbits.RA2 = 0;
    PORTAbits.RA0 = 0;
    return;
}


void tRead(uint16_t *data){
    uint16_t v=0;
    uint16_t v2;
    uint8_t i;
    cs = 0;
    __delay_ms(1);
    
    for (i=0;i<16;i++){
        v = 0x0000 + PORTAbits.RA2;
        v2 = v2|v;
        v2 <<= 1;
        clk = 1;
        __delay_ms(1);
        clk = 0;
        __delay_ms(1);
    }
    
    __delay_ms(1);
    cs = 1;
    
    *data = v2 >> 3;
    return;
}