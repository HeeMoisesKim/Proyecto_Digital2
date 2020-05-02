/*
 * File:   P1_UART.c
 * Author: Carlos
 *
 * Created on 14 de marzo de 2020, 10:14 PM
 */


// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include "UART.h"

#define _XTAL_FREQ 4000000

uint8_t bandera_USART, mandar1, contador = 0;
uint8_t entero_d, entero_u, decimal_u, decimal_d = 0;
uint8_t sensor1, sensor2, sensor3, sensor4, sensor5 = 0;

void set_up(void);
uint8_t select(uint8_t a, uint8_t b, uint8_t c, uint8_t d,uint8_t *contador);       //Funcion para 4 datos



void __interrupt() ISR(void){
    
}



void main(void) {
    set_up();
    USART_setup(9600, 1, 0, 0);             //Configura el baudrate a 9600, no permite RC y  permite TX, asíncrono
    
    while(1){
        
        
        //Prepara dato para mandar del sensor 1
        //mandar1 = select(entero_d,entero_u,decimal_u,decimal_d,&contador);
        enviar_dato(entero_d);                        //Manda el valor del s1
       // mandar1 = select(entero_d,entero_u,decimal_u,decimal_d,&contador);
        enviar_dato(entero_u);                        //Manda el valor del s1
        //mandar1 = select(entero_d,entero_u,decimal_u,decimal_d,&contador);
        enviar_dato(decimal_u);                        //Manda el valor del s1
       // mandar1 = select(entero_d,entero_u,decimal_u,decimal_d,&contador);
        enviar_dato(decimal_d);                        //Manda el valor del s1
        
        
        
        //Esto solo cambia los valores para observar en proteus, en el codigo real son los sensores
        if(contador == 0){
            entero_d++;
        }
        
        entero_u = 255;
        decimal_u = 0;
        decimal_d = 255;
        __delay_ms(100);
        
       
    }
    return;
}

void set_up(){
    
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0;
    TRISC = 0;
    TRISD = 0;
    TRISE = 0;
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;

    return;
}

uint8_t select(uint8_t a, uint8_t b, uint8_t c, uint8_t d,uint8_t *contador){
    if (*contador==0){
        *contador=*contador+1;
        return a;
    }
    if (*contador==1){
        *contador=*contador+1;
        return b;
    }
    if (*contador==2){
        *contador=*contador+1;
        return c;
    }
    if (*contador==3){
        *contador=0;
        return d;
    }
    /*if (*contador==4){
        *contador=0;
        return e;
    }*/
    return *contador;
}