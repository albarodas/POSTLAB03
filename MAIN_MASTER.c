/* 
 * File:   MAIN_MASTER.c
 * Author: ALBA RODAS
 *
 * Created on 4 de agosto de 2022, 08:50 PM
 */

// PIC16F887 Configuration Bit Settings
// 'C' source line config statements
/*===============================================================================
 * INCLUIMOS LAS LIBRERIAS ".h" A UTILIZAR:
================================================================================*/
#include <xc.h>
#include "TMR0.h"
#include "SPI.h"
#include "LCD.h"
#include "oscilador.h"
#include "ADC.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

//-------------------------------------------------------------------------------
// DECLARAMOS FREQ. DE OSCILADOR:
#define _XTAL_FREQ 1000000      // VALOR DE OSC: 1MHz
//-------------------------------------------------------------------------------
// CONFIGURATION WORDS: 1
#pragma config FOSC = INTRC_NOCLKOUT// Oscillator Selection bits (INTOSCIO oscillator: I/O function on RA6/OSC2/CLKOUT pin, I/O function on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF       // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF      // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF      // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF         // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF        // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = OFF      // Brown Out Reset Selection bits (BOR disabled)
#pragma config IESO = OFF       // Internal External Switchover bit (Internal/External Switchover mode is disabled)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is disabled)
#pragma config LVP = OFF        // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIGURATION WORDS: 2
#pragma config BOR4V = BOR40V   // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF        // Flash Program Memory Self Write Enable bits (Write protection off)
// #pragma config statements should precede project file includes.
// Use project enums instead of #define for ON and OFF.
//-------------------------------------------------------------------------------
//===============================================================================
// VARIABLES:
//===============================================================================
#define _XTAL_FREQ 1000000 //Reloj a 1 MHz

/*
 * VARIABLES
 */
uint8_t counter_TMR0 = 0;
uint8_t send = 0;
uint8_t devolver = 0;
uint8_t counter_02 = 0;

/*
 * PROTOTIPOS DE FUNCIÓN
 */
void setup(void); //Configuración de módulos, registros y puertos del PIC

void __interrupt() SPI_master(void){
    if(INTCONbits.T0IF){
        counter_TMR0++; 
        if (counter_TMR0 == 5)
        { 
            counter_02++;       // Se incrementa contador del máster de 1 seg
            PORTB = counter_02;
            counter_TMR0 = 0;       // Clear contador de 500 ms
        }
        TMR0_CARGA();
    }
    return;
}

/*
 * LOOP PRINCIPAL
 */
void main(void) {
    setup();
    while(1){
        PORTCbits.RC7 = 0; 
        __delay_ms(1);  
        
        // CONTADOR --> BUFFER
        spiWrite(counter_02);   
        
        if (send == 0)
        { 
            // LEEMOS VALUE DEL SLAVE --> RECIBIDO POR EL SALVE
            devolver = spiRead(); 
            send = 1;               
            __delay_ms(1); 
            // DESACTIVAMOS EL SLAVE SELECT:
            PORTCbits.RC7 = 1; // WHEN 1 --> OFF, 0 =
            
        } else 
        {
            
            PORTB = spiRead(); 
            __delay_ms(1); 
            // DESACTIVAMOS EL SLAVE SELECT:
            PORTCbits.RC7 = 1; 
        }
        __delay_ms(100);
    }
    return;
}

/*
 * CONFIGURACIONES
 */
void setup(void) {
    //Configuración de puertos
    ANSEL = 0; 
    ANSELH = 0;   
    
    TRISB = 0; 
    PORTB = 0; 
    TRISCbits.TRISC7 = 0; //RC7 --> SS
    PORTCbits.RC7 = 1; 
    //SS OFF AL INICIO
    TRISD = 0; //PORTD como Output
    PORTD = 0; //Clean PORTD
    
    //SSPM de FOSC/4, SMP a la mitad del tiempo, CKP en low, CKE en flanco positivo
    spiInit(SPI_MASTER_OSC_DIV4, SPI_DATA_SAMPLE_MIDDLE, SPI_CLOCK_IDLE_LOW, SPI_IDLE_2_ACTIVE); 
    
    TMR0_init(255); //PS de TMR0 a 256
    TMR0_CARGA(); //Carga de período 50 ms al TMR0
    initOsc(0); //FOSC a 1 MHz
    
    // Configuración de interrupciones
    INTCONbits.GIE = 1;         // Habilitar interrupciones globales
    INTCONbits.PEIE = 1;        // Habilitar interrupciones de perifericos
    return;
}