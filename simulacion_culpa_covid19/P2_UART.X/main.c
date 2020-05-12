
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (RCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
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

//*****************************************************************************
// Definición e importación de librerías
//*****************************************************************************
#include <xc.h>
#include <stdint.h>
#include "UART.h"
#include "SPI.h"
//*****************************************************************************
// Definición de variables
//*****************************************************************************
#define _XTAL_FREQ 4000000
//*****************************************************************************
// Definición de funciones para que se puedan colocar después del main de lo 
// contrario hay que colocarlos todas las funciones antes del main
//*****************************************************************************

uint8_t recorre,flag= 0;
uint8_t a1,b1,c1,d1 = 0;
uint8_t a2,b2,c2,d2 = 0;
uint8_t a3,b3,c3,d3 = 0;
uint8_t a4,b4,c4,d4 = 0;
uint8_t RecibeSPI = 0 ;
uint8_t Heechan = 0 ;
uint8_t estado=0x01;
uint8_t ADC1=5;
uint8_t ADC2=4;
uint8_t contador=0;

void setup(void);

void __interrupt() ISR(void){   
     //Funcion UART-------------------------------------------------------------------------------------------------------
        if(PIR1bits.RCIF == 1){         //If data received by USART
            PIR1bits.RCIF = 0 ;

            if(recorre == 0){
                a1 = RCREG; 

            }else if (recorre ==1){
                b1 = RCREG; 

            }else if (recorre ==2 ){
                 c1 = RCREG;

            }else if(recorre == 3){
                a2 = RCREG; 

            }else if (recorre == 4){
                 b2 = RCREG;

            } else if (recorre == 5){
                c2 = RCREG;

            }else if (recorre == 6){
                d2 = RCREG; 

            }else if (recorre ==7){
                a3 = RCREG; 

            }else if (recorre == 8){
                  b3 = RCREG;

            }else if  (recorre == 9){
                c3 = RCREG;

            }else if (recorre == 10){
                 d3 = RCREG;

            } else if(recorre == 11){
                a4 = RCREG; 

            } else if (recorre == 12){
                b4 = RCREG;

            } else if (recorre ==13){
                c4 = RCREG;

            } else if (recorre == 14){
                d4 = RCREG;

            }
        recorre++;
        recorre = recorre%15;
        flag = 0;
    }
       //Funcion SPI --------------------------------------------------------------------------------------------------------------------
    if(PIR1bits.SSPIF == 1){
        //Heechan = SSPBUF;
        if(RecibeSPI == 0){
            spiWrite(1);
            RecibeSPI = 1;
      
        } else if (RecibeSPI ==1){
            spiWrite(2);
            RecibeSPI = 2;
        
        } else if (RecibeSPI ==2){
            spiWrite(3);
            RecibeSPI = 3;
   
        }else if (RecibeSPI ==3){
            spiWrite(4);
            RecibeSPI = 4;
     
        }else if (RecibeSPI ==4){
            spiWrite(5);
            RecibeSPI = 5;
      
        }else if (RecibeSPI ==5){
            spiWrite(6);
            RecibeSPI = 6;
      
        }else if (RecibeSPI ==6){
            spiWrite(7);
            RecibeSPI = 7;
         
        } else if(RecibeSPI == 7){
            spiWrite(8);
            RecibeSPI = 8;
      
        } else if(RecibeSPI == 8){
            spiWrite(8);
            RecibeSPI = 9;
       
        } else if(RecibeSPI == 9){
            spiWrite(10);
            RecibeSPI = 10;
       
        } else if(RecibeSPI == 10){
            spiWrite(11);
            RecibeSPI = 11;
        
        } else if(RecibeSPI == 11){
            spiWrite(12);
            RecibeSPI = 12;
        
        } else if(RecibeSPI == 12){
            spiWrite(13);
            RecibeSPI = 13;
     
        } else if(RecibeSPI == 13){
            spiWrite(14);
            RecibeSPI = 14;
            
        } else if(RecibeSPI == 14){
            spiWrite(15);
            RecibeSPI = 0;
        }

        PIR1bits.SSPIF = 0;
    }    
    
 


}

//*****************************************************************************
// Código Principal
//*****************************************************************************
void main(void) {
    setup();
    USART_setup(9600, 1, 1, 0);
    __delay_ms(100);
    while(1){
        if(flag == 0){
            enviar_dato(recorre);
            flag = 1;
        }
        PORTB = a1;
        __delay_ms(10);
        
        
    }
    return;
}
//*****************************************************************************
// Función de Inicialización
//*****************************************************************************
void setup(void){
    PORTA = 0;
    PORTB = 0;
    PORTC = 0;
    PORTD = 0;
    PORTE = 0;
    TRISA = 0;
    TRISB = 0;
    TRISC = 0;
    TRISCbits.TRISC5 = 0;
    //TRISCbits.TRISC3 = 1;
    TRISCbits.TRISC4 = 1;
    TRISD = 0;
    TRISE = 0;
    
    INTCONbits.GIE = 1;         // Habilitamos interrupciones
    INTCONbits.PEIE = 1;        // Habilitamos interrupciones PEIE
    PIE1bits.RCIE = 1;
    PIR1bits.SSPIF = 0;         // Borramos bandera interrupción MSSP
    PIE1bits.SSPIE = 1;         // Habilitamos interrupción MSSP
    TRISAbits.TRISA5 = 1;       // Slave Select
    spiInit(SPI_SLAVE_SS_DIS, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE);
    


}