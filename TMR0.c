/*
 * File:   TMR0.c
 * Author: ALBA RODAS
 *
 * Created on 4 de agosto de 2022, 22:01
 */

#include <stdio.h>
#include <stdlib.h>
#include <xc.h>
#include "TMR0.h"

void TMR0_init(uint8_t prescaler){
    OPTION_REGbits.T0CS = 0;
    if (prescaler == 0)
        OPTION_REGbits.PSA = 1; //Se asigno el prescaler para el TMR0
    else
        OPTION_REGbits.PSA = 0; //Se asigno el prescaler para el TMR0
    switch (prescaler){
        case 2: 
            //1:2
            OPTION_REGbits.PS0 = 0;
            OPTION_REGbits.PS1 = 0;
            OPTION_REGbits.PS2 = 0;
            break;
        case 4: 
            //1:4
            OPTION_REGbits.PS0 = 1;
            OPTION_REGbits.PS1 = 0;
            OPTION_REGbits.PS2 = 0;
            break;
        case 8: 
            //1:8
            OPTION_REGbits.PS0 = 0;
            OPTION_REGbits.PS1 = 1;
            OPTION_REGbits.PS2 = 0;
            break;
        case 16: 
            //1:16
            OPTION_REGbits.PS0 = 1;
            OPTION_REGbits.PS1 = 1;
            OPTION_REGbits.PS2 = 0;
            break;
        case 32: 
            //1:32
            OPTION_REGbits.PS0 = 0;
            OPTION_REGbits.PS1 = 0;
            OPTION_REGbits.PS2 = 1;
            break;
        case 64: 
            //1:64
            OPTION_REGbits.PS0 = 1;
            OPTION_REGbits.PS1 = 0;
            OPTION_REGbits.PS2 = 1;
            break;
        case 128: 
            //1:128
            OPTION_REGbits.PS0 = 0;
            OPTION_REGbits.PS1 = 1;
            OPTION_REGbits.PS2 = 1;
            break;
        case 255: 
            //1:256
            OPTION_REGbits.PS0 = 1;
            OPTION_REGbits.PS1 = 1;
            OPTION_REGbits.PS2 = 1;
            break;
    }
    TMR0 = _t0_literal;
    INTCONbits.T0IE = 1;        // Habilitar interrupción del TRM0
    INTCONbits.T0IF = 0;        // Limpiar bandera de interrupción del TRM0
}

void TMR0_reload(void){
    TMR0 = _t0_literal;     //TMR0 es igual a _t0_literal
    INTCONbits.T0IF = 0;    //Limpiamos bandera de TMR0
}