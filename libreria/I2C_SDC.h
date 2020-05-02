/* 
 * File:   
 * Author: Carlos Alonzo
 * Comments: Basado en la libreria de Ligo George, Electrosome
 * Revision history: 
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef __I2C_SDC_H_
#define	__I2C_SDC_H_

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 500000
#endif

#include <xc.h> // include processor files - each processor file is guarded.  
#include <pic16f887.h>
#include <stdint.h>


void I2C_Master_Init(const unsigned long c);            //Inicializa el I2C Master

void I2C_Master_Wait(void);                             //Funcion para esperar condiciones adecuadas

void I2C_Master_Start(void);                            //Comineza la configuración de inicio para el Master

void I2C_Master_RepeatedStart(void);                    //Permite hacer otra instruccion seguida a los esclavos

void I2C_Master_Stop(void);                             //Funcion para detener la comunicacion I2C

void I2C_Master_Write(unsigned d);                      //Funcion para asegurar que el esclavo haya recibido el dato enviado

unsigned short I2C_Master_Read(unsigned short a);       //Funcion para leer datos enviados de los esclavos

void I2C_Slave_Init(uint8_t address);                   //Funcion para incializar I2C Slave mode


#endif	/* __I2C_SDC_H_ */
