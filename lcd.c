/*
 * File:   lcd.c
 * Author: nick
 *
 * Created on April 14, 2022, 6:43 PM
 */

#include <pic16f886.h>


#define _XTAL_FREQ 4000000
#define ENABLE_PIN PORTCbits.RC6
#define RS_PIN PORTCbits.RC4
#define RW_PIN PORTCbits.RC5
#define OUTPUT_BUS PORTB

#include "lcd.h"
#include <xc.h>
#include <string.h>



void SetMode(enum Mode mode)
{
    RS_PIN = mode;
    __delay_ms(20);
}

void EnableFlip()
{
    __delay_ms(20);
    ENABLE_PIN = 1; // Set EN
    __delay_ms(20);
    ENABLE_PIN = 0; // Set EN
}

void SendCommand(enum Command command)
{
    SetMode(COMMAND);
    PORTB = command;
    EnableFlip();
}

void SendRawCommand(char command)
{
    SetMode(COMMAND);
    PORTB = command;
    EnableFlip();
}

void SendCharacter(char character)
{
    SetMode(DATA);
    PORTB = character;
    EnableFlip();
    SendCommand(INCREMENT);
}

void SendString(char* string)
{
    for(int i = 0; i < strlen(string); i++)
    {
        SendCharacter(string[i]);
    }
}

void NextLine()
{
    SendCommand(NEW_LINE);
}

void LCDInit()
{
    RW_PIN = 0;
    SendCommand(TWO_LINES);
    SendCommand(DISP_REST);
    SendCommand(RETURN);
}