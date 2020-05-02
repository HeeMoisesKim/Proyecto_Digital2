/*
 * File:   UART.c
 * Author: Carlos Alonzo
 *
 * Created on 14 de marzo de 2020, 10:18 PM
 */



#include <xc.h>
#include "UART.h"

void USART_setup(uint16_t baudrate, uint8_t tx_enable, uint8_t rc_enable, uint8_t sincrono_asincrono){ //Función para inicializar
    
    TRISCbits.TRISC7 = 1;                        //Asegura que el RC7 sea input
    TRISCbits.TRISC6 = 1;                        //Asegura que el RC6 sea input
    RCSTAbits.SPEN = 1;                          //Habilita comunicación serial
    TXSTAbits.SYNC = sincrono_asincrono;         //Se escoge si quiere síncrono o asíncrono
    PIE1bits.RCIE = 0;                           //Asegura que las interrupciones de RC estén desactivadas
    
        
    if(rc_enable){                              //Se hace la configuración si se desea RC
        RCSTAbits.CREN = 1;                     //Habilita RC
        PIE1bits.RCIE = 1;                      //Habilita las interrupciones de RC
        PIR1bits.RCIF = 0;                      //Limpia la bandera de interrupción
    }
    if(tx_enable){                              //Se hace la configuración si se desea TX
        TXSTAbits.TXEN = 1;                     //Habilita TX
    }
    
    BAUDCTLbits.BRG16 = 1;
    TXSTAbits.BRGH = 1;                     //Seleccionado para ser High speed
    
      
    if(baudrate == 300){                        //Selección del baudrate deseado
        SPBRG = 0x40;
        SPBRGH = 0x03;
    } 
    else if (baudrate == 1200){                 //Para cada caso se modifica el valor que entra en SPBRG
        SPBRG = 207;
    } 
    else if (baudrate == 2400){
        SPBRG = 103;
    } 
    else if (baudrate == 9600){
        SPBRG = 25;
    } 
    else if (baudrate == 10417){
        SPBRG = 23;
    } 
    else if (baudrate == 19200){
        SPBRG = 12;
    }
}

void enviar_dato (uint8_t dato){                         //Enviar información por serial
    while (TXSTAbits.TRMT == 0){}                       //Revisa que haya acabado de enviar el último bit
    TXREG = dato;                                       //Cuando termina el último dato, envía el nuevo
}
