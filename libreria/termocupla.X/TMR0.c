/*
 * File:   TMR0.c
 * Author: moise
 *
 * Created on February 1, 2020, 10:46 PM
 */


#include <xc.h>
#include <stdint.h>

void TMR0setup(uint8_t reloj,uint8_t start){
    INTCONbits.GIE = 0b1;
    INTCONbits.T0IE = 1;
    OPTION_REGbits.PS = reloj;
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.T0CS = 0;
    TMR0 = start;
    return;
}