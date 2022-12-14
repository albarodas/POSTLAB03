/*
 * File:   
 * Author: ALBA RODAS
 *
 * Created on 4 de agosto de 2022, 22:01
 */
// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef TMR0_H
#define	TMR0_H
#define _t0_literal 61  //N para mi tiempo de desbordamiento de 500ms del TMR0

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>

void TMR0_init(uint8_t prescaler);
void TMR0_reload(void);

#endif	/* XC_HEADER_TEMPLATE_H */