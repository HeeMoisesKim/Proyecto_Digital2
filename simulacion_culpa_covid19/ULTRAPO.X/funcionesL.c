/*
 * File:   funcionesL.c
 * Author: Roberto
 *
 * Created on February 5, 2020, 10:59 AM
 */


#include <xc.h>
#include "libreriasAD.h" // Libreria H
#define _XTAL_FREQ 4000000 


void ADC(void){
    ADCON1 = 0;                     
    PIE1 = 0b01000000;              
    ADCON0bits.ADCS0 = 0;          
    ADCON0bits.ADCS1 = 1;
    ADCON0bits.GO = 1;              
    ADCON0bits.ADON = 1;

}




void MULTIPLEXEO (void){
    unsigned char VDis[16] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F, 0x6F, 0x37, 0x7C, 0x39, 0x5E, 0x79, 0x71};
    if(FlagT==1){
        M1 = multiplexor%2 ;
        M2 = multiplexor%2 ; 
        if (M1 ==0){
            PORTEbits.RE0 = 0;
            PORTEbits.RE1 = 1;
            PORTC = VDis[D2];
            __delay_ms (1);
        }
        if (M2 == 1 ){
            PORTEbits.RE0 = 1;
            PORTEbits.RE1 = 0;
            PORTC = VDis[D1];
            __delay_ms (1);
            
        }
        
    
    }
}


