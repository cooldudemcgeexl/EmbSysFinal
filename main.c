/*
 * File:   main.c
 * Author: nick
 *
 * Created on April 14, 2022, 6:28 PM
 */

// CONFIG1
#pragma config FOSC = HS // Oscillator Selection bits (RC oscillator: CLKOUT function on RA6/OSC2/CLKOUT pin, RC on RA7/OSC1/CLKIN)
#pragma config WDTE = OFF          // Watchdog Timer Enable bit (WDT disabled and can be enabled by SWDTEN bit of the WDTCON register)
#pragma config PWRTE = OFF         // Power-up Timer Enable bit (PWRT disabled)
#pragma config MCLRE = OFF         // RE3/MCLR pin function select bit (RE3/MCLR pin function is digital input, MCLR internally tied to VDD)
#pragma config CP = OFF            // Code Protection bit (Program memory code protection is disabled)
#pragma config CPD = OFF           // Data Code Protection bit (Data memory code protection is disabled)
#pragma config BOREN = ON          // Brown Out Reset Selection bits (BOR enabled)
#pragma config IESO = ON           // Internal External Switchover bit (Internal/External Switchover mode is enabled)
#pragma config FCMEN = ON          // Fail-Safe Clock Monitor Enabled bit (Fail-Safe Clock Monitor is enabled)
#pragma config LVP = OFF           // Low Voltage Programming Enable bit (RB3 pin has digital I/O, HV on MCLR must be used for programming)

// CONFIG2
#pragma config BOR4V = BOR40V // Brown-out Reset Selection bit (Brown-out Reset set to 4.0V)
#pragma config WRT = OFF      // Flash Program Memory Self Write Enable bits (Write protection off)

#define _XTAL_FREQ 8000000
#define DHT11_PIN PORTCbits.RC7
#define DHT11_TRISTATE_PIN TRISCbits.TRISC7
#define LOW 0
#define HIGH 1
#define OUTPUT 0
#define INPUT 1

#define ROW_PINS PORTBbits.RB7, PORTBbits.RB6, PORTBbits.RB5, PORTBbits.RB4
#define COL_PINS PORTBbits.RB3, PORTBbits.RB2, PORTBbits.RB1, PORTBbits.RB0

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <xc.h>
#include "dht11.h"
//#include "lcd.h"
//#include "keypad.h"


void main(void)
{
   OSCCxON = 0x70;
   ANSELH = 0;
   T1CON = 0x10;
   TMR1H = 0;
   TMR1L = 0;
   
   
    TRISB = 0;
    PORTB = 0x00;



    char * sensorReadings;

    while (1)
    {
        sensorReadings = dhtReading();
        if(sensorReadings[0] > 0)
        {
            PORTB = 0x02;
        }
    
        
    }
}
