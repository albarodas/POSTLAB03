/*
 * File:   
 * Author: ALBA RODAS
 *
 * Created on 4 de agosto de 2022, 22:01
 */

// This is a guard condition so that contents of this file are not included
// more than once.  
#ifndef ADC_H
#define	ADC_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>
//CONFIGURACIÓN EL ADC EN EL AD0, RA0
/*
00 = Fosc/2 (default)
01 = Fosc/8
10 = Fosc/32
11 = FRC
 */

void initADC(uint8_t ADCS_ADC, uint8_t vref_plus, uint8_t vref_min);
void startADC(uint8_t channel_1, uint8_t channel_2);
uint16_t ADCRead(void);

#endif	/* XC_HEADER_TEMPLATE_H */

