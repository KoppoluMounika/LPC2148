#include <lpc21xx.h>

unsigned char data;

int main()
{
    PINSEL0 |= 0x00000005;   // Enable UART0 pins (P0.0 = TXD0, P0.1 = RXD0)

    U0LCR = 0x83;            // 8-bit data, 1 stop bit, no parity, DLAB=1
    U0DLL = 98;              // Baud rate = 9600 (assuming 15MHz PCLK)
    U0LCR = 0x03;            // Clear DLAB, keep 8-bit mode

    while(1)
    {
        while(!(U0LSR & 0x01));   // Wait until data is received
        data = U0RBR;             // Read received byte

        while(!(U0LSR & 0x20));   // Wait until transmitter is ready
        U0THR = data;             // Send same byte back (echo)
    }
}
