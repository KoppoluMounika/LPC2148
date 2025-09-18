#include <LPC214x.h>
#include "gpio.h"

// Write data starting from given pin (example: pin=12 ? P0.12 onwards)
void portwrite(int pin, unsigned int value)
{
    IO0DIR |= (0xFF << pin);     // Configure pins as output
    IO0CLR = (0xFF << pin);      // Clear bits first
    IO0SET = (value << pin);     // Write new value
}

// Simple delay
void delay(void)
{
    unsigned int i;
    for(i=0; i<60000; i++);
}
