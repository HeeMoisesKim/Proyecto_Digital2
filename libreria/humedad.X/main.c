/*
 * File:   main.c
 * Author: Tinusaur
 * Edited: moises
 * Created on March 12, 2020, 2:24 PM
 */

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
#include "humedad.h"
#include "LCD.h"

// ----------------------------------------------------------------------------

#define _XTAL_FREQ 4000000

void setup(void);
void desplegar(uint32_t valor, uint8_t *v1, uint8_t *v2, uint8_t *v3);

uint8_t c1=0;
uint8_t d1=0;
uint8_t u1=0;
uint8_t resultado = 0;
uint8_t humedad;

// ----------------------------------------------------------------------------

void main(void) {
    setup();
    __delay_ms(1000);
    while(1){
        resultado = Read(&humedad);
        if(resultado==1){
            desplegar(humedad, &c1, &d1, &u1);
        }
        lcd_cursor(1,3);
        lcd_wstring("humedad");
        lcd_cursor(2,3);
        lcd_wchar(c1);
        lcd_wchar(d1);
        lcd_wchar(u1);
	}

	return; // Return the mandatory result value. It is "0" for success.
}

// ============================================================================

void setup(void){
    lcd_setup();
    return;
}
void desplegar(uint32_t valor, uint8_t *v1, uint8_t *v2, uint8_t *v3){
    uint8_t c;
    uint8_t d;
    uint8_t u;
    uint8_t conv;
    conv = (uint8_t)(valor);
    c = (uint8_t)((conv/100));
    d = (uint8_t)((((conv)/10)-(c*10)));
    u = (uint8_t)((conv)/1-(c*100+d*10));
    *v1=c+48;
    *v2=d+48;
    *v3=u+48;
    return;
}