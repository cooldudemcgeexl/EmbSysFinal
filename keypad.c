/*
 * File:   keypad.c
 * Author: nick
 *
 * Created on April 19, 2022, 7:34 PM
 */

#include "keypad.h"

char getFirstKeyFound()
{
    for(int i = 0; i< 4; i++)
    {
        for(int j = 0; j < 4; j++)
        {
            if (bitMap[i][j])
            {
                return charMap[i][j];
            }
            
        }
    }
}

void readKey()
{
    TRISB = 1;
    COL_0_TRISTATE = 1;
    COL_1_TRISTATE = 1;
    COL_2_TRISTATE = 1;
    COL_3_TRISTATE = 1;

    ROW_0_TRISTATE = 0;
    ROW_0_PIN = 1;
    bitMap[0][0] = COL_0_PIN;
    bitMap[1][0] = COL_1_PIN;
    bitMap[2][0] = COL_2_PIN;
    bitMap[3][0] = COL_3_PIN;
    ROW_0_PIN = 0;
    ROW_0_TRISTATE = 1;

    ROW_1_TRISTATE = 0;
    ROW_1_PIN = 1;
    bitMap[0][1] = COL_0_PIN;
    bitMap[1][1] = COL_1_PIN; 
    bitMap[2][1] = COL_2_PIN;
    bitMap[3][1] = COL_3_PIN;
    ROW_1_PIN = 0;
    ROW_1_TRISTATE = 1;
    
    
    ROW_2_TRISTATE = 0;
    ROW_2_PIN = 1;
    bitMap[0][2] = COL_0_PIN;
    bitMap[1][2] = COL_1_PIN;
    bitMap[2][2] = COL_2_PIN;
    bitMap[3][2] = COL_3_PIN;
    ROW_2_PIN = 0;
    ROW_2_TRISTATE = 1;
    
    ROW_3_TRISTATE = 0;
    ROW_3_PIN = 1;
    bitMap[0][3] = COL_0_PIN;
    bitMap[1][3] = COL_1_PIN;
    bitMap[2][3] = COL_2_PIN;
    bitMap[3][3] = COL_3_PIN;
    ROW_3_PIN = 0;
    ROW_3_TRISTATE = 1;
    
}