/*
 * File:   TEMPERATURA.c
 * Author: moises
 *
 * Created on February 16, 2020, 12:47 PM
 */

// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF       // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF       // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

#include <xc.h>
#include <stdint.h>
#include "LCD.h"
#include "peso.h"
#include "I2C.h"

#define _XTAL_FREQ 4000000

void setup(void);
void weight(uint32_t valor, uint32_t tare, uint8_t *v4, uint8_t *v0, uint8_t *v1, uint8_t *v2, uint8_t *v3);
uint8_t select(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t peso, uint8_t *contador);

uint8_t mandar;
uint8_t contador=0;
uint8_t borrar;
uint8_t z;
uint8_t b1=0;
uint8_t m1=0;
uint8_t c1=0;
uint8_t d1=0;
uint8_t u1=0;
uint32_t peso1=0;
uint32_t peso=0;
uint32_t peso_pasado=0;
uint32_t tare=0;
uint8_t pagar=0;

float lambda=0.35;

void __interrupt() isr(void){
    if(PIR1bits.SSPIF==1){
        SSPCONbits.CKP = 0;
       
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){
            z = SSPBUF;                 // Read the previous value to clear the buffer
            SSPCONbits.SSPOV = 0;       // Clear the overflow flag
            SSPCONbits.WCOL = 0;        // Clear the collision bit
            SSPCONbits.CKP = 1;         // Enables SCL (Clock)
        }

        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {
            //__delay_us(7);
            z = SSPBUF;                 // Lectura del SSBUF para limpiar el buffer y la bandera BF
            //__delay_us(2);
            PIR1bits.SSPIF = 0;         // Limpia bandera de interrupci贸n recepci贸n/transmisi贸n SSP
            SSPCONbits.CKP = 1;         // Habilita entrada de pulsos de reloj SCL
            while(!SSPSTATbits.BF);     // Esperar a que la recepci贸n se complete
            borrar = SSPBUF;             // Guardar en el PORTD el valor del buffer de recepci贸n
            __delay_us(250);   
        }else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            z = SSPBUF;
            BF = 0;
            mandar=select(b1,m1,c1,d1,u1,peso,&contador);
            SSPBUF = mandar;
            SSPCONbits.CKP = 1;
            __delay_us(250);
            while(SSPSTATbits.BF);
        
        }
       
        PIR1bits.SSPIF = 0;
    }
    return;
}


void main(void) {
    setup();
    while(1){
        peso_pasado = peso;
        peso = (1-lambda)*celdaRead()+lambda*peso_pasado;
        weight(peso1, tare, &b1, &m1, &c1, &d1, &u1);
        if(contador==0){
            peso1 = peso;
        }
        __delay_ms(250);
        if(peso=peso_pasado){
            if(100<peso<1420){
                pagar = 1; //paga carro peque駉
            } else if(1420<=peso<8388607){
                pagar = 2; //paga carro grande
            } else {
                pagar = 0;
            }
        }
    }
    return;
}

void setup(void){
    //lcd_setup();
    tare = celdaSetup();
    peso=tare;
    INTCON = 0b11000000;
    I2C_Slave_Init(0x20); 
    return;
}

void weight(uint32_t valor, uint32_t tare, uint8_t *v4, uint8_t *v0, uint8_t *v1, uint8_t *v2, uint8_t *v3){
    uint8_t x;
    uint8_t a;
    uint8_t b;
    uint8_t m;
    uint8_t c;
    uint8_t d;
    uint8_t u;
    float conv;
    conv = (float)(valor-tare-512)*(float)(0.0550271739);
    //conv = valor;
    if(conv>=0){
        b = (uint8_t)(conv/10000);
        m = (uint8_t)(conv/1000-(b*10));
        c = (uint8_t)((conv/100)-(b*100+m*10));
        d = (uint8_t)((((conv)/10)-(b*1000+m*100+c*10)));
        u = (uint8_t)((conv)/1-(b*10000+m*1000+c*100+d*10));
    }
    *v4=b+48;
    *v0=m+48;
    *v1=c+48;
    *v2=d+48;
    *v3=u+48;
    return;
}

uint8_t select(uint8_t a, uint8_t b, uint8_t c, uint8_t d, uint8_t e, uint8_t peso, uint8_t *contador){
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
        *contador=*contador+1;
        return d;
    }
    if (*contador==4){
        *contador=5;
        return e;
    }
    if (*contador==5){
        *contador=0;
        return peso;
    }
    return *contador;
}
