/* 
 * File: LCD.c  
 * Se utilizó y se adaptaron las librerías de Ligo George 
 * de la página www.electrosome.com
 * Enlace: https://electrosome.com/lcd-pic-mplab-xc8/
 * Revision history: 
 */

//LCD Functions Developed by electroSome


#include <xc.h>
#include "LCD.h"
#define _XTAL_FREQ 4000000

void lcd_command(uint8_t a){
    RS = RW = 0;
    PORTB = a;
    E=1;
    __delay_ms(4);
    E=0;
}

void lcd_cursor(uint8_t a,uint8_t b){
    switch(a){
        case 1:
            lcd_command(0x80+b-1);
            break;
        case 2:
            lcd_command(0xC0+b-1);
            break;
    }
    return;
}

void r_shift(uint8_t saltos){
    uint8_t i;
    for(i=0;i<=saltos;i++)
        lcd_command(0x14);
    return;
}

void l_shift(uint8_t saltos){
    uint8_t i;
    for(i=0;i<=saltos;i++)
        lcd_command(0x10);
    return;
}

void lcd_wchar(char dato){
    RS = 1;
    datos = dato;
    E = 1;
    __delay_ms(4);
    E = 0;
    return;
}

void lcd_wstring(char *string){
    int i;
    for(i = 0; string[i] != '\0'; i++) 
        lcd_wchar(string[i]);            //divide el string y los escribe
    return;
}

void lcd_setup(void){
    TRISB = 0x00;
    ANSELH = 0x00;
    TRISD = 0x00;
    __delay_ms(16);
    lcd_command(0x03);
    __delay_ms(4.2);
    lcd_command(0x03);
    __delay_ms(1);
    lcd_command(0x03);
    lcd_command(0x38); //define que es de 8 bits y 2 lineas
    lcd_command(0x0C); //enciende el display y apaga el cursor
    lcd_command(0x06); //mode set
}
