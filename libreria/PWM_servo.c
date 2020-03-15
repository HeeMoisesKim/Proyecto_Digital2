/*
 * File:   PWM_servo.c
 * Author: Carlos
 *
 * Created on 2 de marzo de 2020, 11:28 AM
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

#define _XTAL_FREQ 500000           //Frecuencia 500 kHz

uint8_t push1, push2 = 0;

void PWM_setup(void);
void set_up(void);
void zero_deg(void);
void final_deg(void);

void __interrupt() isr(void){
    //INTCONbits.GIE = 0;                     //Apaga las dem�s interrupciones
    
    if(INTCONbits.RBIF){                    //Revisa si fue interrupci�n de los botones
        if(PORTBbits.RB0){
           push2 = 1;           
        }
        if(PORTBbits.RB1){
            push1 = 1;          
        }
        INTCONbits.RBIF = 0;                //Apago la bandera de Port B
    }
    
    //INTCONbits.GIE = 1;                     //Enciende de nuevo las interrupciones
}




void main(void) {
    set_up();
    PWM_setup();
    
    while(1){
        if(push1 && PORTBbits.RB1==1){            //Funcion de antirrebote 1 - incrementar
            final_deg();
        }
        else{
            push1 = 0;
        }
        if(push2 && PORTBbits.RB0==1){            //Funcion de antirrebote 2 - decrementar
            zero_deg();
        }
        else{
            push2 = 0;
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