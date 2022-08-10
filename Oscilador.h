/*
 * File:   
 * Author: ALBA RODAS
 *
 * Created on 4 de agosto de 2022, 22:01
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef OSCILADOR_H
#define	OSCILADOR_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h> 

void initOsc(uint8_t freq);
/*
111 = 8MHz (default)
110 = 4MHz
101 = 2MHz
100 = 1MHz
 */
#endif	/* XC_HEADER_TEMPLATE_H */