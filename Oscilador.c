/*
 * File:   Oscilador.c
 * Author: ALBA RODAS
 *
 * Created on 4 de agosto de 2022, 23:01
 */

#include <xc.h>
#include "Oscilador.h"

void initOsc(uint8_t freq){
    switch(freq){
        case 0: //4MHz
            OSCCONbits.IRCF =0b110;
            OSCCONbits.SCS = 1;
            break;
        case 1: //2MHz
            OSCCONbits.IRCF =0b101;
            OSCCONbits.SCS = 1;
            break;
        case 2: //1MHz
            OSCCONbits.IRCF =0b100;
            OSCCONbits.SCS = 1;
            break;
        case 3: //8MHz
            OSCCONbits.IRCF =0b100;
            OSCCONbits.SCS = 1;
            break;
    }
}