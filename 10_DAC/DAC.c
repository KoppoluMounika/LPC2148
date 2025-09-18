#include <lpc21xx.h>
#define DACR   (*((volatile unsigned long *)0xE006C000))
	
void dac_init(void)
{
    PINSEL1 |= (1 << 21);   // Enable DAC function on P0.25 (AOUT)
}

void dac_write(unsigned int value)
{
    DACR = (value & 0x3FF) << 6;  // 10-bit value, left aligned
}

void delay_us(unsigned int us)
{
    unsigned int i, j;
    for(i = 0; i < us; i++)
    {
        for(j = 0; j < 10; j++);  // crude delay
    }
}

int main(void)
{
    unsigned int data;
    int i;   // declare here

    dac_init();

    while(1)
    {
        // square
        data = 0;
        while(data <= 1023)
        {
            dac_write(data);
            delay_us(200);
            data += 20;
        }

        // Triangle
        for(i = 0; i < 50; i++)
        {
            dac_write(i*20);
            delay_us(200);
        }
        for(i = 0; i < 50; i++)
        {
            dac_write(1000 - (i*20));
            delay_us(200);
        }
    }
}
