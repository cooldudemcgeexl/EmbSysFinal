/*
 * File:   dht11.c
 * Author: nick
 *
 * Created on April 19, 2022, 9:47 PM
 */

#include "dht11.h"
#include <string.h>

void StartSignal()
{
    DHT11_PIN_DIR = 0; // configure DHT11_PIN as output
    DHT11_PIN = 0;     // clear DHT11_PIN output (logic 0)

    __delay_ms(25); // wait 25ms
    DHT11_PIN = 1;  // set DHT11_PIN output (logic 1)

    __delay_us(30); // wait 30us
    DHT11_PIN_DIR = 1;
}

__bit CheckResponse()
{
    TMR1H = 0; // reset Timer1
    TMR1L = 0;
    TMR1ON = 1; // enable Timer1 module

    while (!DHT11_PIN && TMR1L < 100)
        ;           // wait until DHT11_PIN becomes high (checking of 80µs low time response)
    if (TMR1L > 99) // if response time > 99µS  ==> Response error
        return 0;   // return 0 (Device has a problem with response)

    else
    {
        TMR1H = 0; // reset Timer1
        TMR1L = 0;

        while (DHT11_PIN && TMR1L < 100)
            ; // wait until DHT11_PIN becomes low (checking of 80µs high time response)

        if (TMR1L > 99 * 5) // if response time > 99µS  ==> Response error
        {
            return 0; // return 0 (Device has a problem with response)
        }
        else
        {
            return 1; // return 1 (response OK)
        }
    }
}

__bit ReadData(unsigned char *dhtData)
{
    *dhtData = 0;

    for (char i = 0; i < 8; i++)
    {
        TMR1H = 0; // reset Timer1
        TMR1L = 0;

        while (!DHT11_PIN) // wait until DHT11_PIN becomes high
            if (TMR1L > 100)
            { // if low time > 100  ==>  Time out error (Normally it takes 50µs)
                return 1;
            }
        TMR1H = 0; // reset Timer1
        TMR1L = 0;

        while (DHT11_PIN) // wait until DHT11_PIN becomes low
            if (TMR1L > 100)
            {             // if high time > 100  ==>  Time out error (Normally it takes 26-28µs for 0 and 70µs for 1)
                return 1; // return 1 (timeout error)
            }
        if (TMR1L > 50)                  // if high time > 50  ==>  Sensor sent 1
            *dhtData |= (1 << (7 - i)); // set bit (7 - i)
    }

    return 0; // return 0 (data read OK)

}

char * dhtReading()
{
    char readings[5] = {0,0,0,0,255};

    StartSignal();

    if(CheckResponse())
    {
        readings[0] = ReadData(&Hum1);
        readings[1] = ReadData(&Hum2);
        readings[2] = ReadData(&Temp1);
        readings[3] = ReadData(&Temp2);
        readings[4] = ReadData(&CheckSum);

    }
    else
    {

    }
    TMR1ON = 0;
    __delay_ms(1000);
    return readings;
}