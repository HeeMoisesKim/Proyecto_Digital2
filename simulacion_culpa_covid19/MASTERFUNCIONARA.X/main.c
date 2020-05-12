/*
 * File:   master.c
 * Author: moise
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

//master
#include <xc.h>
#include <stdint.h>
#include "SPI.h"
#include "LCD.h"


#define _XTAL_FREQ 4000000

void setup(void);

uint8_t estado=0x01;
uint8_t ADC1=5;
uint8_t ADC2=4;
uint8_t contador=0;
uint8_t a4,b4,c4,d4 = 0;
uint8_t a2,b2,c2,d2 = 0;
uint8_t a3,b3,c3,d3 = 0;
uint8_t a1,b1,c1 = 0;
uint8_t recorre = 0 ;
uint16_t espera1= 0;
uint16_t espera2= 1;
uint16_t espera3= 2;
uint16_t espera4= 3;

void __interrupt() isr(){
   /* if(PIR1bits.RCIF==1){
        PIR1bits.RCIF=0;
    }*/
}
void main(void) {
    setup();
    spiWrite(0);
    __delay_ms(1);
    while(1){
        /*
        spiWrite(0);              //IDENTIFICADOR POT1
        a1 = spiRead();       //LEER EL DATO DEL POT1 DESDE EL SLAVE
        __delay_ms(15);
        
         spiWrite(1);              //IDENTIFICADOR POT1
        b1 = spiRead();       //LEER EL DATO DEL POT1 DESDE EL SLAVE
        __delay_ms(15);
        
         spiWrite(2);              //IDENTIFICADOR POT1
        c1 = spiRead();       //LEER EL DATO DEL POT1 DESDE EL SLAVE
        __delay_ms(15);
        
         spiWrite(3);              //IDENTIFICADOR POT1
        a2 = spiRead();       //LEER EL DATO DEL POT1 DESDE EL SLAVE
        __delay_ms(15);
        
        spiWrite(4);              //IDENTIFICADOR POT1
        b2 = spiRead();       //LEER EL DATO DEL POT1 DESDE EL SLAVE
        __delay_ms(15);
        
        spiWrite(5);              //IDENTIFICADOR POT1
        c2 = spiRead();       //LEER EL DATO DEL POT1 DESDE EL SLAVE
        __delay_ms(15);
        
        spiWrite(6);              //IDENTIFICADOR POT1
        d2 = spiRead();       //LEER EL DATO DEL POT1 DESDE EL SLAVE
        __delay_ms(15);
        
        spiWrite(7);              //IDENTIFICADOR POT1
        a3 = spiRead();       //LEER EL DATO DEL POT1 DESDE EL SLAVE
        __delay_ms(15);
        
          spiWrite(8);              //IDENTIFICADOR POT1
        b3 = spiRead();       //LEER EL DATO DEL POT1 DESDE EL SLAVE
        __delay_ms(15);
        
          spiWrite(9);              //IDENTIFICADOR POT1
        c3 = spiRead();       //LEER EL DATO DEL POT1 DESDE EL SLAVE
        __delay_ms(15);
        
          spiWrite(10);              //IDENTIFICADOR POT1
        d3 = spiRead();       
        __delay_ms(15);
        
        
          spiWrite(11);              //IDENTIFICADOR POT1
        a4 = spiRead();       //LEER EL DATO DEL POT1 DESDE EL SLAVE
        __delay_ms(15);
        
          spiWrite(12);              //IDENTIFICADOR POT1
        b4 = spiRead();       //LEER EL DATO DEL POT1 DESDE EL SLAVE
        __delay_ms(15);
        
         spiWrite(13);              //IDENTIFICADOR POT1
        c4 = spiRead();       //LEER EL DATO DEL POT1 DESDE EL SLAVE
        __delay_ms(15);
        
          spiWrite(14);              //IDENTIFICADOR POT1
        d4 = spiRead();       //LEER EL DATO DEL POT1 DESDE EL SLAVE
        __delay_ms(15);*/
        
        if(PIR1bits.SSPIF==1){
              if(recorre == 0){
                a1 = spiRead();
                recorre = 1;
              }else if(recorre == 1){
                b1 = spiRead();
                recorre = 2;
              }else if(recorre == 2){
                c1 = spiRead(); 
                recorre = 3;
             }else if(recorre == 3){
                a2 = spiRead();
                recorre = 4;
             }else if(recorre == 4){
                b2 = spiRead();
                recorre = 5;
             }else if(recorre == 5){
                c2 = spiRead();
                recorre = 6;
             }else if(recorre == 6){
                d2 = spiRead();
                recorre = 7;
             }else if(recorre == 7){ 
                a3 = spiRead();
                recorre = 8;
             }else if(recorre == 8){
                b3 = spiRead();
                recorre = 9;
             }else if(recorre == 9){
                c3 = spiRead();
                recorre = 10;
             }else if(recorre == 10){
                d3 = spiRead();
                recorre = 11;
             }else if(recorre == 11){
                a4 = spiRead();
                recorre = 12;
             }else if(recorre == 12){
                b4 = spiRead();
                recorre = 13;
             }else if(recorre == 13){
                c4 = spiRead();
                recorre = 14;
             }else if(recorre == 14){
                d4 = spiRead();
                recorre = 0;
             }
        
            PIR1bits.SSPIF=0;
            spiWrite(1);
        }
        
        if(espera1!=0){
        espera1--;
    }else if(espera1==0){
        lcd_command(clean);
        __delay_ms(1);
        lcd_cursor(1,3);
        lcd_wstring("Temperatura:");
        lcd_cursor(2,3);
        lcd_wchar(a1);
        lcd_wchar(b1);
        lcd_wstring(".");
        lcd_wchar(c1);
        lcd_wstring("C");
        espera1=4;
    }
            if(espera2!=0){
            espera2--;
        }else if(espera2==0){
            lcd_command(clean);
            __delay_ms(1);
            lcd_cursor(1,3);
            lcd_wstring("Peso:");
            lcd_cursor(2,3);
            lcd_wchar(a2);
            lcd_wchar(b2);
            lcd_wchar(c2);
            lcd_wchar(d2);
            lcd_wstring("kg");
            espera2=4;
        }
        if(espera3!=0){
            espera3--;
        }else if(espera3==0){
            lcd_command(clean);
            __delay_ms(1);
            lcd_cursor(1,3);
            lcd_wstring("Caudal:");
            lcd_cursor(2,3);
            lcd_wchar(a3);
            lcd_wstring(".");
            lcd_wchar(b3);
            lcd_wchar(c3);
            lcd_wchar(d3);
            espera3=4;
        }
        if(espera4!=0){
            espera4--;
        }else if(espera4==0){
            lcd_command(clean);
            __delay_ms(1);
            lcd_cursor(1,3);
            lcd_wstring("Distancia:");
            lcd_cursor(2,3);
            lcd_wchar(a4);
            lcd_wchar(b4);
            lcd_wstring(".");
            lcd_wchar(c4);
            lcd_wchar(d4);
            lcd_wstring("m");
            espera4=4;
        }
        //uart_read(&PORTB);
        __delay_ms(5);
    }
    
    return;
}

void setup(void){
    TRISB = 0;
    ANSELH = 0;
    PORTB=0;
    lcd_setup();
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    return;
}
