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
    TRISAbits.TRISA0 = 0; //clk
    TRISAbits.TRISA1 = 0; //decidir si leer o no, 0 leer y 1 convertir
    TRISAbits.TRISA2 = 1; //la entrada de la termocupla
    ANSEL = 0;
    cs = 1;
    __delay_ms(1000);
    return;
}


uint16_t tRead(void){
    uint8_t i;
    uint8_t v;
    uint16_t valor=0;
    cs = 0;
    __delay_ms(1);
    //cs = 1;
    for (i=0;i<16;i++){
        clk = 1;
        __delay_ms(1);
        //v = 0x0000 + PORTAbits.RA2;
        valor = valor|PORTAbits.RA2;
        valor <<= 1;
        clk = 0;
        __delay_ms(1);
    }
    
    cs = 1;
    if (valor & 0x4) {
        // uh oh, no thermocouple attached!
        //return NAN; 
        return -100;
    }
    
    valor >>= 3;
    valor = valor/4;
    return valor;
}