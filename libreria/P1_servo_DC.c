/*
 * File:   P1_servo_DC.c
 * Author: Carlos
 *
 * Created on 13 de marzo de 2020, 11:14 PM
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
#include "I2C_SDC.h"

#define _XTAL_FREQ 500000           //Frecuencia 500 kHz

//uint8_t push1, push2 = 0;
uint8_t limpia_buffer = 0;
uint8_t dato_recibido = 0;

void PWM_setup(void);
void set_up(void);
void zero_deg(void);
void final_deg(void);

void __interrupt() isr(void){
    //INTCONbits.GIE = 0;                     //Apaga las demás interrupciones
    
    if(INTCONbits.RBIF){                    //Revisa si fue interrupción de los botones
        if(PORTBbits.RB0){
           push2 = 1;           
        }
        if(PORTBbits.RB1){
            push1 = 1;          
        }
        INTCONbits.RBIF = 0;                //Apago la bandera de Port B
    }
 
    if(PIR1bits.SSPIF == 1){
        SSPCONbits.CKP = 0;                 //Deja el SCL en low
        
        if ((SSPCONbits.SSPOV) || (SSPCONbits.WCOL)){   //Revisa si hubo alguna colision
            limpia_buffer = SSPBUF;                 // Lee el valor previo para limpiar el buffer
            SSPCONbits.SSPOV = 0;                   // Limpia la bandera de overflow
            SSPCONbits.WCOL = 0;                    // Limpia bandera de colision
            SSPCONbits.CKP = 1;                     // Habilita de nuevo el SCL
        }
        if(!SSPSTATbits.D_nA && !SSPSTATbits.R_nW) {    //Significa que es una direccion / Write del slave habilitado
            //__delay_us(7);
            limpia_buffer = SSPBUF;                 // Lectura del SSBUF para limpiar el buffer y la bandera BF
            //__delay_us(2);
            PIR1bits.SSPIF = 0;                     // Limpia bandera de interrupción recepción/transmisión SSP
            SSPCONbits.CKP = 1;                 // Habilita entrada de pulsos de reloj SCL
            while(!SSPSTATbits.BF);              // Esperar a que la recepción se complete
            dato_recibido = SSPBUF;             // Guardar en variable del valor del buffer de recepción
            __delay_us(250);
        }
        /*else if(!SSPSTATbits.D_nA && SSPSTATbits.R_nW){         //Significa que el master quiere leer dato del slave
            limpia_buffer = SSPBUF;
            BF = 0;                                             //Data transmit complete
            SSPBUF = valor_para_Master;                         //Escribe en el registro el valor de L/min*100 para el master
            SSPCONbits.CKP = 1;                                 //Activa el reloj para enviar lso datos
            __delay_us(250);
            while(SSPSTATbits.BF);                              //Espera a que se envíe el dato completo
        }*/
        PIR1bits.SSPIF = 0;                 //Apaga la bandera de interrupcion del I2C
    }    
    
    //INTCONbits.GIE = 1;                     //Enciende de nuevo las interrupciones
}




void main(void) {
    set_up();
    I2C_Slave_Init(0x12);                   //Funcion para incializar I2C Slave mode con dirección 0x12
    PWM_setup();
    
    while(1){
        if(dato_recibido == 0){            //Funcion abrir puerta (servo)
 
        }

        if(dato_recibido == 1){            //Funcion cerrar puerta (servo)

        }
        
        if(dato_recibido == 2){            //Funcion encender DC

        }
        
        if(dato_recibido == 3){            //Funcion encender DC

        }

    }
    return;
}


void set_up(void){
    OSCCONbits.IRCF = 0b011;        //Configura oscilador a 500kHz
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0;
    TRISB = 0;
    TRISD = 0;
    PORTB = 0;                  //Limpio PORTB
    PORTD = 0;
    PORTA = 0;
    TRISB = 0b00000011;

    
    INTCONbits.GIE = 1;         //Habilita interrupciones globales
    INTCONbits.PEIE = 1;        //Habilita interrupciones perifericas
    IOCBbits.IOCB0 = 1;         //Habilita los botones RB0 y RB1 para ser IOC
    IOCBbits.IOCB1 = 1;
    INTCONbits.RBIE = 1;        //Habilita interrupciones del puerto B
    INTCONbits.RBIF = 0;        //Limpia la bandera del puerto B

    return;
}



void PWM_setup(void){           //CONFIGURACION_PWM1:   
TRISCbits.TRISC2 = 1;       //Coloca CCP1 como entrada
PR2 = 155;                  //Valor para periodo de 20 ms
CCP1CONbits.P1M = 0b00;        //Coloca un pin de salida unico
CCP1CONbits.CCP1M = 0b1100;      //Selecciona el pwm active-high
CCPR1L = 27;
CCP1CONbits.DC1B = 0b11;           //Los dos bits menos significativos- numero completo = 110 1111?
PIR1bits.TMR2IF = 0;                //Apaga bandera TMR2
T2CONbits.T2CKPS = 0b11;            //Prescaler de 1:16
T2CONbits.TMR2ON = 1;               //Enciende el TMR2
while(!TMR2IF){                      //Revisa un ciclo de interrupcion
}
PIR1bits.TMR2IF = 0;                //Apaga bandera del TMR2
TRISCbits.TRISC2 = 0;               //Coloca como salida el CCP1 

return;
}

void zero_deg(void){
    CCP1CONbits.DC1B = 0b00;        //2 LSB del valor completo 0001 1111
    CCPR1L = 3;                     //Restantes bits significativos para el valor a 1ms de pulse width
    return;
}

void final_deg(void){
    CCP1CONbits.DC1B = 0b11;        //2 LSB del valor completo 11 1110?
    CCPR1L = 13;                     //Restantes bits significativos para el valor a 2ms de pulse width
    return;    
}