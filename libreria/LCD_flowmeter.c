/*
 * File:   LCD_init_lib.c
 * Author: Carlos
 *
 * Created on 01 de marzo de 2020, 5:30 AM
 */
  

#include <pic16f887.h>
#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include<stdint.h>
#include "LCD_flowmeter.h"

#define _XTAL_FREQ 4000000

void LCD_sep(uint8_t val_cmd){          //Función encargada de separar el dato en los pines D0-D7
    
	if(val_cmd & 1){
		D0 = 1;
    }
	else{
		D0 = 0;
    }
	if(val_cmd & 2){
		D1 = 1;
    }
	else{
		D1 = 0;
    }
	if(val_cmd & 4){
		D2 = 1;
    }
	else{
		D2 = 0;
    }
	if(val_cmd & 8){
		D3 = 1;
    }
	else{
		D3 = 0;
    }
    if(val_cmd & 16){
        D4 = 1;
    }
    else{
        D4 = 0;
    }
    if(val_cmd & 32){
        D5 = 1;
    }
    else{
        D5 = 0;
    }
    if(val_cmd & 64){
        D6 = 1;
    }
    else{   
        D6 = 0;
    }
    if(val_cmd & 128){
        D7 = 1;
    }
    else{
        D7 = 0;
    }
    return;

}

void LCD_Cmd(uint8_t cmd){
    RS = 0;          //Convierte RS a 0
    PORTA = cmd;    //PRUEBA
    //LCD_sep(cmd);   //Envía el dato a separar y enviar a cada pin
    EN = 1;         //EN se vuele 1
    __delay_ms(4);  //delay de 4 ms
    EN = 0;         //En el flanco de bajada se encarga de mandar el dato
    return;
}

void LCD_clear(void){
    //LCD_Cmd(0);             //Envía 0 a todos los bits D0- D7
    //LCD_Cmd(1);             //Comando para borrar el visualizador
    LCD_Cmd(0x01);
    return;
}

void LCD_pos_cursor(uint8_t fila, uint8_t casilla){
    uint8_t temporal;
    if(fila == 1){
        temporal = 0x80 + casilla -1;
        LCD_Cmd(temporal);
    }
    else if(fila == 2){
        temporal = 0xC0 + casilla -1;
        LCD_Cmd(temporal);
    }
    return;
}

void LCD_Write_Char(uint8_t caracter){

   RS = 1;                        // => RS = 1
   LCD_sep(caracter);             //Transfiere el valor al puerto
   EN = 1;
   __delay_us(40);
   EN = 0;                      //Escribe en el flanco de bajada
   return;
}

void LCD_Write_String(uint8_t *string){
	uint8_t i;
	for(i=0;string[i]!='\0';i++){       //Se encarga de enviar todos los caracteres que forman parte de un string
	   LCD_Write_Char(string[i]);
    }
    return;
}

void LCD_setup(void){
  //LCD_sep(0x00);
  __delay_ms(15);
  LCD_Cmd(0x030);
  __delay_ms(5);
  LCD_Cmd(0x30);
  __delay_ms(11);
  LCD_Cmd(0x30);            //Inicio para cualquier configuración
  
  LCD_Cmd(0x38);            //Pone la interfaz en 8 bits, 2 líneas y 5x10
  LCD_Cmd(0x10);            //Apaga el visualizador
  LCD_Cmd(0x01);            //Limpia el visualizador
  LCD_Cmd(0x06);            //Cursor move direction
  LCD_Cmd(0x0E);            //Prende display, prende cursor, apaga parpadeo
  return;
}

void Write_entero(uint8_t entero){          //Función para convertir enteros a stings
    char string_buffer [4];                 //Crea variable para caracter
    sprintf (string_buffer, "%d", entero);  //Función que convierte el entero
    LCD_Write_String(string_buffer);        //Escribe el string en la LCD
    return;
}

void Write_float(uint8_t entero, uint8_t decimal, uint8_t pos_inicial){ //Convierte entero y decimales para escribir en LCD

    LCD_pos_cursor(2, pos_inicial);         //Coloca el cursor en la posición donde se quiere escribir el número
    Write_entero(entero);                  // lcd_write_string
    LCD_pos_cursor(2, pos_inicial + 1);     //COloca el cursor junto al entero
    LCD_Write_Char('.');                    //Coloca el caracter '.' después del entero
    LCD_pos_cursor(2, pos_inicial + 2);     //Se coloca después del punto decimal
    
    if(decimal < 10){
        LCD_Write_Char('0');                //Si no hay un decimal, entonces la función coloca un 0
    }
    Write_entero(decimal);                  //si hay decimal, pone ese valor junto al '.'
    
    LCD_pos_cursor(2, pos_inicial + 4);         //Pone el cursor para escribir el V
    LCD_Write_Char('L');                    //Escribe el caracter V
    
    return;
}