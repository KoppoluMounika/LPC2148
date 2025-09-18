#include <LPC214x.h>   
#include <stdint.h>
#include <stdio.h>

#define PCLK 60000000   // Peripheral clock = 60 MHz

char msg[40];

//UART initialization
void UartInit(void)
{
    PINSEL0 |= 0x00000005;   // P0.0 = TXD0, P0.1 = RXD0
    U0LCR = 0x83;            // 8-bit, 1 stop, no parity, DLAB=1
    U0DLL = 97;              // Baud rate 9600 for PCLK=60MHz
    U0LCR = 0x03;            // DLAB = 0
}

void UartTxChar(char ch)
{
    while (!(U0LSR & 0x20)); // Wait until THR is empty
    U0THR = ch;
}

void UartTxString(char *str)
{
    while (*str)
        UartTxChar(*str++);
}

// ADC initialization
void AdcInit(void)
{
    PINSEL1 |= (1 << 24);    // P0.28 as AD0.1
    AD0CR = (1 << 21)        // Enable ADC
          | (4 << 8);        // CLKDIV 
}

uint16_t AdcRead(void)
{
    AD0CR &= ~(0xFF);         // Clear channel selection
    AD0CR |= (1 << 1);        // Select channel 1 (AD0.1)
    AD0CR |= (1 << 24);       // Start conversion now

    
    while (!(AD0GDR & (1U << 31)));
    return (uint16_t)((AD0GDR >> 6) & 0x3FF);
}

void delay_ms(uint32_t ms)
{
    uint32_t i, j;
    for (i = 0; i < ms; i++)
        for (j = 0; j < 6000; j++);
}

int main(void)
{
    uint16_t adc_value;
    float temperature;

    UartInit();
    AdcInit();

    UartTxString("LM35 Temperature Sensor Test\r\n");

    while (1)
    {
        adc_value = AdcRead();

        // Convert ADC to Temperature
        temperature = ((float)adc_value * 3.3 / 1023.0) / 0.01;

        sprintf(msg, "Temp = %.2f C\r\n", temperature);
        UartTxString(msg);

        delay_ms(500);
    }
}
