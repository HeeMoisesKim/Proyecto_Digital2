/*
 * File:   LAB2.c
 * Author: Roberto
 *
 * Created on January 24, 2020, 11:28 AM
 */



// PIC16F887 Configuration Bit Settings

// 'C' source line config statements

// CONFIG1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT enabled)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is MCLR)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF         // Low Voltage Programming Enable bit (RB3/PGM pin has PGM function, low voltage programming enabled)

// CONFIG2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)

// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include "libreriasAD.h"
#include "I2C.h"
#include <pic16f887.h>
#define _XTAL_FREQ  4000000


uint8_t var1     = 0;
uint8_t var2     = 0;
uint8_t controli = 0;
uint8_t botonB7  = 0;
uint8_t botonB0  = 0;
uint8_t z;
uint8_t dato;
uint8_t NO_SIRVE = 0; 
uint8_t rango=0; 
uint8_t mandar = 0;
uint8_t contador=0;
uint8_t E1 = 0;
uint8_t C1 = 0;
uint8_t T1 = 0;
uint8_t U1 = 0;
uint8_t counter = 0; 
uint8_t SW      = 0;
uint8_t ENVIOLCD = 0; 
uint8_t ES = 0;
uint8_t PUERTA = 0 ;

uint8_t const Shorario[4] = {  0b1100,  //aca creamos dos vectores para poder darle vuelta al motor encendiendo una por una las bobinas
                               0b0110,
                               0b0011,
                               0b1001};

uint8_t const Santi[4] ={      0b1001,
                               0b0011,
                               0b0110,
                               0b1100};

float Conv1 = 0; 

unsigned char CADC     = 0;




void conf (void);
void conversion(void); 
void int_caudal(float conv,uint8_t *v0, uint8_t *v1, uint8_t *v2, uint8_t *v3);
uint8_t select(uint8_t q1, uint8_t q2, uint8_t q3, uint8_t q4, uint8_t r, uint8_t PUERT, uint8_t *contador);
//interrupciones 

void __interrupt() srt(void){
    
   if(PIR1bits.SSPIF == 1){ 

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
            PIR1bits.SSPIF = 0;         // Limpia bandera de interrupción recepción/transmisión SSP
            SSPCONbits.CKP = 1;         // Habilita entrada de pulsos de reloj SCL
            while(!SSPSTATbits.BF);     // Esperar a que la recepción se complete
            NO_SIRVE = SSPBUF;             // Guardar en el PORTD el valor del buffer de recepción
            __delay_us(250);
            
        }else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){
            z = SSPBUF;
            BF = 0;
            mandar = select(E1,C1,T1,U1,rango,PUERTA, &contador);
            SSPBUF = mandar; 
            SSPCONbits.CKP = 1;
            __delay_us(250);
            while(SSPSTATbits.BF);
        
        }
       
        PIR1bits.SSPIF = 0;    
    }
   
           if (ADCON0bits.GO_DONE == 0){
            CADC = 1;
            PIR1bits.ADIF =0;
        }
              
}

    
        



// loop principal 
void main(void) {
    conf ();
    ADC  ();
    
    while (1){
        ADCON0bits.GO_DONE =1;
        PORTB =ADCValor;
        Conv1 = (float)(ADCValor)*(float)(0.15686); //vamos a plotear los datos de 0 a 1300 kg que es lo que pesa una camioneta escolar. 
        int_caudal(Conv1, &E1, &C1, &T1, &U1);
        if (CADC ==1){
            ADCValor = ADRESH; 
            CADC =0;
        }
        
         if(PORTDbits.RD7 ==1 && ES == 0 ) {
             ES = 1 ;
             PUERTA = 0; 
        
             }
    
     if(PORTDbits.RD7 ==1 && ES == 1) {
         ES = 0;
         PUERTA = 1; 
        
             }
    
    if (PORTDbits.RD7 ==0 && PORTDbits.RD6 == 0){
        
        
    if (Conv1 >= 29 && Conv1 <= 37){
        PORTAbits.RA1 = 0;
        PORTAbits.RA2 = 0;
        PORTAbits.RA3 = 0;
        SW = 0 ;
        rango = 0;
        if (SW ==0){  
            PORTB = 0 ; 
             }
       }    
    
    if (Conv1 >= 18 && Conv1 <=28){
        PORTAbits.RA1 = 0;
        PORTAbits.RA2 = 0;
        PORTAbits.RA3 = 1;
        SW = 1;
        rango = 1;
        ENVIOLCD = 0;
        
        if (SW ==1){  
         counter=0;                          //cuando ya recorrio el vector saldra del while y entonces reiniciara el contador
         while((counter<4)&&(SW==1))       
        {
            PORTB =(Shorario[counter]);        //mostramos el valor del vector en el puerto
            __delay_ms(5);                //el tiempo que se tardara en incrementar o cambiar de bobinas
            counter++;                       
         }
             }
    }
    
    if (Conv1 >=10 && Conv1 <=17){
        PORTAbits.RA1 = 1;
        PORTAbits.RA2 = 0;
        PORTAbits.RA3 = 0;
        SW = 1;
        rango = 2; 
        ENVIOLCD = 1;
         if (SW ==1){  
         counter=0;                          //cuando ya recorrio el vector saldra del while y entonces reiniciara el contador
         while((counter<4)&&(SW==1))       
        {
            PORTB =(Shorario[counter]);        //mostramos el valor del vector en el puerto
            __delay_ms(5);                //el tiempo que se tardara en incrementar o cambiar de bobinas
            counter++;                       
         }
             }
    }
    
    if (Conv1 >=2 && Conv1 <=9){ 
        PORTAbits.RA1 = 0;
        PORTAbits.RA2 = 1;
        PORTAbits.RA3 = 0;
        SW = 0;
        ENVIOLCD =2;
        if (SW ==0){  
            PORTB = 0 ; 
             }
    
   
 
    } 
    }
        
        
        
        }
         return;  
}
    
    
        

    


void int_caudal(float conv,uint8_t *v0, uint8_t *v1, uint8_t *v2, uint8_t *v3){
    uint8_t m;
    uint8_t c;
    uint8_t d;
    uint8_t u;

    conv = conv*100;
    if(conv>=0){

        m = (uint8_t)(conv/1000);
        c = (uint8_t)((conv/100)-(m*10));
        d = (uint8_t)((((conv)/10)-(m*100+c*10)));
        u = (uint8_t)((conv)/1-(m*1000+c*100+d*10));
    }
    *v0=m+48;
    *v1=c+48;
    *v2=d+48;
    *v3=u+48;
    return;
}


void conf (void){

    //OSCCON     = 0b01110001;
    ANSEL      = 0b00000001;
    ANSELH     = 0;
    PORTD      = 0;
    PORTA      = 0;
    PORTB      = 0;
    PORTE      = 0;
    TRISA      = 0b00000001;
    TRISB      = 0;
    TRISD      = 0;
    TRISE      = 0;      
    INTCON     = 0b11000000;
    I2C_Slave_Init(0x70); 
}


uint8_t select(uint8_t q1, uint8_t q2, uint8_t q3, uint8_t q4, uint8_t r, uint8_t PUERT, uint8_t *contador){
    if (*contador==0){
        *contador=*contador+1;
        return q1;
    }
    if (*contador==1){
        *contador=*contador+1;
        return q2;
    }
    if (*contador==2){
        *contador=*contador+1;
        return q3;
    }
    if (*contador==3){
        *contador=*contador+1;
        return q4;
    }
    if (*contador==4){
        *contador=*contador+1;
        return r;
    }
    if (*contador==5){
        *contador = 0;
    return PUERT;
     }
    return *contador;
}