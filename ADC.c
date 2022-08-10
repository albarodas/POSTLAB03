/*
 * File:   ADC.c 
 * Author: ALBA RODAS
 *
 * Created on 4 de agosto de 2022, 22:24
 */

#ifndef _XTAL_FREQ
#define _XTAL_FREQ 4000000
#endif

#include <xc.h>
#include <stdint.h>
#include "ADC.h"
 
void initADC(uint8_t ADCS_ADC, uint8_t vref_plus, uint8_t vref_min){
    switch(ADCS_ADC){
        case 0: 
            //FOSC/2
            ADCON0bits.ADCS = 0b00;
            break;
        case 1: 
            //FOSC/8
            ADCON0bits.ADCS = 0b01;
            break;
        case 2: 
            //FOSC/32
            ADCON0bits.ADCS = 0b10;
            break;
        default: 
            //FRC
            ADCON0bits.ADCS = 0b11;
            break;
    }
    ADCON1bits.ADFM = 0;
    ADCON1bits.VCFG0 = vref_plus;
    ADCON1bits.VCFG1 = vref_min;
    ADCON0bits.ADON =  1;
    __delay_ms(1);
    
    INTCONbits.PEIE = 1;        // Habilitar interrupción de perifericos
    PIE1bits.ADIE = 1;          // Habilitar interrupción del ADC
    PIR1bits.ADIF = 0;          // Limpiar bandera del ADC
}

void startADC(uint8_t channel_1, uint8_t channel_2){
        if (ADCON0bits.GO == 0) {                           // si esta en 0, revisa en qué canal está convirtiendo
            if (ADCON0bits.CHS == channel_1){                       //Verifica el AN0
                __delay_us(100);                            //Espera 100 us
                ADCON0bits.CHS = channel_2;                         //Se cambia al AN1
            }                                               //Termina verificacion del AN0
            else if (ADCON0bits.CHS == channel_2){                  //Verifica el AN1
                __delay_us(100);                            //Espera 100 us
                ADCON0bits.CHS = channel_1;                         //Se cambia al AN2
            }                                               //Termina verificacion del AN1                                             //Termina verificacion del AN3
            __delay_us(100);                                //Espera 100 us
            ADCON0bits.GO = 1;                              //Go en 1
        }
}


uint16_t ADCRead(void){
    PIR1bits.ADIF = 0;                  // Limpiar bandera de interrupción del ADC
    return ADRESH;
}
