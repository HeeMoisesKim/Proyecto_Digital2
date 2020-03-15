/*
 * File:   main.c
 * Author: moises
 *
 * Created on February 25, 2020, 8:38 AM
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


// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.

#include <xc.h>
#include <stdint.h>
#include <stdio.h>
#include <pic16f887.h>
#include "I2C.h"
#include "LCD.h"

#define _XTAL_FREQ 4000000
#define D7 PORTBbits.RB7
#define D6 PORTBbits.RB6
#define D5 PORTBbits.RB5
#define D4 PORTBbits.RB4
#define D3 PORTBbits.RB3
#define D2 PORTBbits.RB2
#define D1 PORTBbits.RB1
#define D0 PORTBbits.RB0
#define RS PORTDbits.RD7
#define RW PORTDbits.RD6
#define E PORTDbits.RD5
#define datos PORTB
#define clean 0x01
#define home 0x02
#define go ADCON0bits.GO_DONE
#define ADC_F PIR1bits.ADIF

void setup(void);
void int_str(uint32_t valor, uint8_t *v1, uint8_t *v2, uint8_t *v3);
void int_distance(uint8_t valor, uint8_t *v1, uint8_t *v2, uint8_t *v3);
void desplegar(float valor, uint8_t *v1, uint8_t *v2, uint8_t *v3, uint8_t *v4, uint8_t *v5);

uint8_t c1=0;
uint8_t d1=0;
uint8_t u1=0;
uint8_t b2=0;
uint8_t m2=0;
uint8_t c2=0;
uint8_t d2=0;
uint8_t u2=0;
uint8_t c3=0;
uint8_t d3=0;
uint8_t u3=0;

uint8_t contador=0;

uint8_t sensor=0;


void main(void) {
    setup();
    lcd_command(clean);
    __delay_ms(4);
    lcd_cursor(1,13);
    lcd_wstring("S3:");
    
    while(1){
         //termocupla
        I2C_Master_Start();
        I2C_Master_Write(0x31); //le habla a la termocupla
        c1 = I2C_Master_Read(0);
        I2C_Master_Stop();
        //int_str(adc, &c1, &d1, &u1);
        __delay_ms(1);
        I2C_Master_Start();
        I2C_Master_Write(0x31); //le habla a la termocupla
        d1 = I2C_Master_Read(0);
        I2C_Master_Stop();
        //int_str(adc, &c1, &d1, &u1);
        __delay_ms(1);
        I2C_Master_Start();
        I2C_Master_Write(0x31); //le habla a la termocupla
        u1 = I2C_Master_Read(0);
        I2C_Master_Stop();
        //int_str(adc, &c1, &d1, &u1);
        __delay_ms(1);
        
        //pesa
        I2C_Master_Start();
        I2C_Master_Write(0x21); //le habla al pesa
        b2 = I2C_Master_Read(0);
        I2C_Master_Stop();
        //desplegar(contador,&b2, &m2, &c2, &d2, &u2);
        __delay_ms(1);        
        I2C_Master_Start();
        I2C_Master_Write(0x21); //le habla al pesa
        m2 = I2C_Master_Read(0);
        I2C_Master_Stop();
        //desplegar(contador,&b2, &m2, &c2, &d2, &u2);
        __delay_ms(1);
        I2C_Master_Start();
        I2C_Master_Write(0x21); //le habla al pesa
        c2 = I2C_Master_Read(0);
        I2C_Master_Stop();
        //desplegar(contador,&b2, &m2, &c2, &d2, &u2);
        __delay_ms(1);
        I2C_Master_Start();
        I2C_Master_Write(0x21); //le habla al pesa
        d2 = I2C_Master_Read(0);
        I2C_Master_Stop();
        //desplegar(contador,&b2, &m2, &c2, &d2, &u2);
        __delay_ms(1);
        I2C_Master_Start();
        I2C_Master_Write(0x21); //le habla al pesa
        u2 = I2C_Master_Read(0);
        I2C_Master_Stop();
        //desplegar(contador,&b2, &m2, &c2, &d2, &u2);
        __delay_ms(1);
        /*I2C_Master_Start();
        I2C_Master_Write(0x61); //le habla al SENSOR
        sensor = I2C_Master_Read(0);
        I2C_Master_Stop();
        int_distance(sensor, &c3, &d3, &u3);
        __delay_ms(1);*/
        
        lcd_command(clean);
        __delay_ms(1);
        lcd_cursor(1,3);
        lcd_wstring("Temperatura:");
        lcd_cursor(2,2);
        lcd_wchar(c1);
        lcd_wchar(d1);
        lcd_wstring(".");
        lcd_wchar(u1);
        __delay_ms(500);
        lcd_command(clean);
        __delay_ms(1);
        lcd_cursor(1,8);
        lcd_wstring("Peso:");
        lcd_cursor(2,7);
        lcd_wchar(b2);
        lcd_wchar(m2);
        lcd_wchar(c2);
        lcd_wchar(d2);
        lcd_wchar(u2);
        __delay_ms(500);
        /*lcd_cursor(2,12);
        lcd_wchar(c3);
        lcd_wchar(d3);
        lcd_wstring(".");
        lcd_wchar(u3);*/
    }
    return;
}

void setup(void){
    I2C_Master_Init(100000);
    lcd_setup();
    TRISA=0;
    ANSEL=0;
    PORTA=0;
    return;
}

void int_str(uint32_t valor, uint8_t *v1, uint8_t *v2, uint8_t *v3){
    uint8_t c;
    uint8_t d;
    uint8_t u;
    float conv=valor;
    c = (uint8_t)(conv/100);
    d = (uint8_t)((((conv)/10)-(c*10)));
    u = (uint8_t)((conv)/1-(c*100+d*10));
    *v1=c+48;
    *v2=d+48;
    *v3=u+48;
    return;
}

void int_distance(uint8_t valor, uint8_t *v1, uint8_t *v2, uint8_t *v3){
    uint8_t c;
    uint8_t d;
    uint8_t u;
    float conv=valor;
    c = (uint8_t)(valor/100);
    d = (uint8_t)((((conv)/10)-(c*10)));
    u = (uint8_t)((conv)/1-(c*100+d*10));
    *v1=c+48;
    *v2=d+48;
    *v3=u+48;
    return;
}

//------------------------------------------------------------------------------
void desplegar(float valor, uint8_t *v1, uint8_t *v2, uint8_t *v3, uint8_t *v4, uint8_t *v5){
    uint8_t b;
    uint8_t m;
    uint8_t c;
    uint8_t d;
    uint8_t u;
    float conv=valor;
        b = (uint8_t)(conv/10000);
        m = (uint8_t)(conv/1000-(b*10));
        c = (uint8_t)((conv/100)-(b*100+m*10));
        d = (uint8_t)((((conv)/10)-(b*1000+m*100+c*10)));
        u = (uint8_t)((conv)/1-(b*10000+m*1000+c*100+d*10));
    *v1=b+48;
    *v2=m+48;
    *v3=c+48;
    *v4=d+48;
    *v5=u+48;
    return;
}