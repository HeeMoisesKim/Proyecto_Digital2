
/**
 * TinuDHT - Library for the DHT11 temperature/humidity sensors
 *
 * @author Neven Boyanov
 *
 * This is part of the Tinusaur/TinuDHT project.
 *
 * Copyright (c) 2018 Neven Boyanov, The Tinusaur Team. All Rights Reserved.
 * Distributed as open source software under MIT License, see LICENSE.txt file.
 * Retain in your source code the link http://tinusaur.org to the Tinusaur project.
 *
 * Source code available at: https://bitbucket.org/tinusaur/tinudht
 *
 */

#ifndef __HUMEDAD_H
#define __HUMEDAD_H

// ----------------------------------------------------------------------------

#include <xc.h> // include processor files - each processor file is guarded. 
#include <stdint.h>

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------

// ----------------------------------------------------------------------------

void Start_Signal(void);
uint8_t Read(uint8_t *humedad);
__bit Check_Response();
__bit Read_Data(unsigned char* dht_data);

// ----------------------------------------------------------------------------

#endif


