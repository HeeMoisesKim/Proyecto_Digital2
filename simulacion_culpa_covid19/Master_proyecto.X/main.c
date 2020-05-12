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
#include "UART.h"


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
void desplegar(float valor, uint8_t *v1, uint8_t *v2, uint8_t *v3, uint8_t *v4, uint8_t *v5);

uint8_t c1=0;
uint8_t d1=0;
uint8_t u1=0;
uint8_t b2=0;
uint8_t m2=0;
uint8_t c2=0;
uint8_t d2=0;
uint8_t u2=0;
uint8_t m3=0;
uint8_t c3=0;
uint8_t d3=0;
uint8_t u3=0;
uint8_t a4=0;
uint8_t b4=0;
uint8_t c4=0;
uint8_t d4=0;
uint8_t e4=0;
uint8_t f4=0;
uint8_t g4=0;
uint8_t peso=0;
uint8_t PESOUART =0;
uint8_t   CAUDALUART =0;
uint8_t   DISUART = 0;


uint8_t ES=0;

uint32_t temperatura=0;

uint8_t sensor=0;
uint8_t puerta=0;
uint8_t rango =0;
uint8_t Cuenta=0; 
uint8_t cambio=0; 
uint8_t solicitud=0; 
uint16_t espera1 = 0;
uint16_t espera2 = 1;
uint16_t espera3 = 2;
uint16_t espera4 =3; 


void __interrupt() isr(void){
        //Funcion para UART
    if(PIR1bits.RCIF == 1){         //If data received by USART
        PIR1bits.RCIF = 0;
       
        solicitud = RCREG;      //Read
        
        if(solicitud == 0){
            enviar_dato(c1);
        }else if(solicitud == 1){
            enviar_dato(d1);
        }else if(solicitud == 2){
            enviar_dato(u1);
        }else if(solicitud ==3){
            enviar_dato(b2);
        }else if(solicitud == 4){
            enviar_dato(m2);
        }else if(solicitud == 5){
            enviar_dato(c2);
        }else if(solicitud == 6){
            enviar_dato(d2);         
        }else if(solicitud==7){
            enviar_dato(m3);
        }else if(solicitud == 8){
            enviar_dato(c3);
        }else if(solicitud == 9){
            enviar_dato(d3);
        }else if(solicitud == 10){
            enviar_dato(u3);
        }else if(solicitud==11){
            enviar_dato(a4);
        }else if(solicitud == 12){
            enviar_dato(b4);
        }else if(solicitud == 13){
            enviar_dato(c4);
        }else if(solicitud == 14){
            enviar_dato(d4);           
        }

    }
    
    
    
      
}


void main(void) {
  
    setup();
    lcd_command(clean);
    __delay_ms(4);
    lcd_cursor(1,1);
    lcd_wstring("Bienvenidos CW");
    
    while(1){
        PORTA = c1;
        //termocupla
        I2C_Master_Start();
        I2C_Master_Write(0x31); //le habla a la termocupla
        temperatura = I2C_Master_Read(0);
        I2C_Master_Stop();
        temperatura=temperatura<<8;
        //int_str(adc, &c1, &d1, &u1);
        __delay_ms(1);
        I2C_Master_Start();
        I2C_Master_Write(0x31); //le habla a la termocupla
        temperatura = temperatura+I2C_Master_Read(0);
        I2C_Master_Stop();
        temperatura=temperatura<<8;
        //int_str(adc, &c1, &d1, &u1);
        __delay_ms(1);
        I2C_Master_Start();
        I2C_Master_Write(0x31); //le habla a la termocupla
        temperatura = temperatura+I2C_Master_Read(0);
        I2C_Master_Stop();
        //int_str(adc, &c1, &d1, &u1);
        __delay_ms(1);
        temperatura=temperatura<<8;
        //int_str(adc, &c1, &d1, &u1);
        __delay_ms(1);
        I2C_Master_Start();
        I2C_Master_Write(0x31); //le habla a la termocupla
        temperatura = temperatura+I2C_Master_Read(0);
        I2C_Master_Stop();
        //int_str(adc, &c1, &d1, &u1);
        __delay_ms(1);
        //temperatura = temperatura/0.2217506684;
        int_str(temperatura, &c1, &d1, &u1);
        
        
        
        //pesa
        I2C_Master_Start();
        I2C_Master_Write(0x21); //le habla al pesa
        b2 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(1);        
        I2C_Master_Start();
        I2C_Master_Write(0x21); //le habla al pesa
        m2 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(1);
        I2C_Master_Start();
        I2C_Master_Write(0x21); //le habla al pesa
        c2 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(1);
        I2C_Master_Start();
        I2C_Master_Write(0x21); //le habla al pesa
        d2 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(1);
        I2C_Master_Start();
        I2C_Master_Write(0x21); //le habla al pesa
        peso = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(1);

        
        //caudalimetro
        I2C_Master_Start();
        I2C_Master_Write(0x11); //le habla al caudal
        m3 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(1);        
        I2C_Master_Start();
        I2C_Master_Write(0x11); //le habla al caudal
        c3 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(1);
        I2C_Master_Start();
        I2C_Master_Write(0x11); //le habla al caudal
        d3 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(1);
        I2C_Master_Start();
        I2C_Master_Write(0x11); //le habla al caudal
        u3 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(1);

        
        //distancia
        I2C_Master_Start();
        I2C_Master_Write(0x71); //le habla a distancia
        a4 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(1); 
        
        I2C_Master_Start();
        I2C_Master_Write(0x71); //le habla al distancia
        b4 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(1);
        
        I2C_Master_Start();
        I2C_Master_Write(0x71); //le habla al distancia
        c4 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(1);
        
        I2C_Master_Start();
        I2C_Master_Write(0x71); //le habla al distancia
        d4 = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(1);
        
        I2C_Master_Start();
        I2C_Master_Write(0x71); //le habla al distancia
        rango = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(1);
        
        I2C_Master_Start();
        I2C_Master_Write(0x71); //le habla al distancia
        puerta = I2C_Master_Read(0);
        I2C_Master_Stop();
        __delay_ms(1);     

        
        if(espera1!=0){
            espera1--;
        }else if(espera1==0){
            lcd_command(clean);
            __delay_ms(1);
            lcd_cursor(1,3);
            lcd_wstring("Temperatura:");
            lcd_cursor(2,3);
            lcd_wchar(c1);
            lcd_wchar(d1);
            lcd_wstring(".");
            lcd_wchar(u1);
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
            lcd_wchar(b2);
            lcd_wchar(m2);
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
            lcd_wchar(m3);
            lcd_wstring(".");
            lcd_wchar(c3);
            lcd_wchar(d3);
            lcd_wchar(u3);
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
            lcd_wstring("cm");
            espera4=4;
        }
        //enviar_dato(10);
        //__delay_ms(4);    
        
        
 
      
    }
    return;
}

void setup(void){
  
    I2C_Master_Init(100000);
    USART_setup(9600, 1, 1, 0);
    lcd_setup();
    
    PORTD = 0 ; 
    TRISA=0;
    ANSEL=0;
    PORTA=0;
    
    INTCONbits.GIE = 1;         // Habilitamos interrupciones
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIE1bits.RCIE = 1;
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