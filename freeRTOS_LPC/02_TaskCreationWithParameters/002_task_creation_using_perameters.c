#include <LPC214x.h>

void init_pll(void);
void initserial(unsigned int baudrate);
void sendserial(char c);
void print_string(const char *s);

int main(void)
{
	volatile unsigned int i;
    init_pll();
    initserial(9600);

    while (1)
    {
        print_string("Task 1 is running\r\n");
        for (i = 0; i < 500000; i++); 

        print_string("Task 2 is running\r\n");
        for ( i = 0; i < 500000; i++);  
    }
}

void init_pll(void)
{
    PLL0CON = 0x01;        
    PLL0CFG = 0x24;       
    PLL0FEED = 0xAA;
    PLL0FEED = 0x55;

    while (!(PLL0STAT & (1 << 10))); 

    PLL0CON = 0x03;     
    PLL0FEED = 0xAA;
    PLL0FEED = 0x55;

    VPBDIV = 0x01;         
}

void initserial(unsigned int baudrate)
{
    unsigned int divisor;
    unsigned long PCLK = 60000000;  

    PINSEL0 |= 0x05;        
    U0LCR = 0x83;          

    divisor = (PCLK / (16 * baudrate));
    U0DLL = divisor & 0xFF;
    U0DLM = (divisor >> 8) & 0xFF;

    U0LCR = 0x03;           
}

void sendserial(char c)
{
    while (!(U0LSR & (1 << 5)));  
    U0THR = c;
}

void print_string(const char *s)
{
    while (*s)
    {
        sendserial(*s++);
    }
}
