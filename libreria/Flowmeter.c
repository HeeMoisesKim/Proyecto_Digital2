/*
 * File:   Flowmeter.c
 * Author: Carlos
 *
 * Created on 1 de marzo de 2020, 04:52 PM
 */

// PIC16F887 Configuration Bit Settings

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
#include <pic16f887.h>
#include "LCD_flowmeter.h"

#define _XTAL_FREQ 4000000

uint16_t contador_fm = 0;
uint8_t contar_seg = 0;
float conversor = 0.1399888905;         //Variable para hacer la conversion de pulsos a L/min
float L_min = 0;
float float1 = 0;
uint8_t entero1, decimal_1 = 0;


void set_up(void);
void TMR0_setup(void);

void __interrupt() isr(void){
    //INTCONbits.GIE = 0;                     //Apaga las interrupciones

    if(INTCONbits.INTF){                    //Revisa si es interrupción del sensor de flujo
        contador_fm++;                      //Variable que guarda los pulsos que se reciben
        INTCONbits.INTF = 0;                //Apaga la bandera de interrupcion externa
    }
    
    if(INTCONbits.T0IF){                         //Revisa si fue interrupción del TMR0
        if(contar_seg == 15){
            L_min = conversor*contador_fm;      //Hace la conversión de pulsos a L/min
            contar_seg = 0;                     //Reinicia el contador de tiempo a 0
            contador_fm = 0;                    //Vuelve a contar desde 0 los pulsos
        }
        else{
            contar_seg++;                   //Incrementa para ver cuántas veces se ha saturado el TMR0
        }
        TMR0 = 0;                           //vuelve a cargar valor para interrupción a 65.536 ms
        INTCONbits.T0IF = 0;                //Apaga la bander de TMR0
    }
    
    
    
    //INTCONbits.GIE = 1;                     //Enciende de nuevo las interrupciones
}


void main(void) {
    set_up();
    LCD_setup();                //Inicializa LCD
    LCD_clear();
    //__delay_ms(100);            //delay para que LCD se estabilice
    TMR0_setup();

    
    LCD_pos_cursor(1, 1);
    LCD_Write_String("L/min:");
    LCD_pos_cursor(1, 8);
    LCD_Write_String("Pul");          //Coloca los valores que no van a cambiar 
    
    LCD_pos_cursor(2,1);                //Se coloca el cursor en la segunda fila
    
    while(1){
        
        entero1 = (int) L_min;                          //Convierte en int el float de L/min
        float1 = (float) (L_min - entero1)*100;           //Separa el decimal y lo vuelve entero 
        decimal_1 = (int) float1;                      //Convierte en entero la parte decimal
        
        Write_float(entero1,decimal_1,1);               //Escribe el valor de L/min en LCD
    }
    
    return;
}

void set_up(void){
    ANSEL = 0;
    ANSELH = 0;
    TRISA = 0;
    TRISB = 0;
    TRISBbits.TRISB0 = 1;       //Coloco como entrada el RB0
    TRISD = 0;
    PORTB = 0;                  //Limpio PORTB
    PORTD = 0;
    PORTA = 0;
    OPTION_REGbits.nRBPU = 0;   //Habilita pull-ups para PORTB
    WPUB = 0b00000001;          //Habilito Weak Pull Up para RB0
    OPTION_REGbits.INTEDG = 0;  //Flanco de bajada para la interrupcion externa
    
    INTCONbits.GIE = 1;         //Habilita interrupciones globales
    INTCONbits.PEIE = 1;        //Habilita interrupciones perifericas
    INTCONbits.INTE = 1;        //Habilita interrupcion externa
    INTCONbits.INTF = 0;        //Limpio bandera de int externa
    return;
}

void TMR0_setup(){
    OPTION_REGbits.T0CS = 0;        //Set TMR0 como temporizador
    
    OPTION_REGbits.PSA = 0;
    OPTION_REGbits.PS2 = 1;
    OPTION_REGbits.PS1 = 1;
    OPTION_REGbits.PS0 = 1;         //Prescaler 1:256
       
    
    INTCONbits.T0IE = 1;        //Habilita interrupción TMR0
    INTCONbits.T0IF = 0;        //Limpia bandera del TMR0
    TMR0 = 0;                   //Coloca literal para saturarse a 65.536 ms
}