#include <LPC21xx.h>
#include "uart.h"

void init_uart(unsigned int baud) {
    unsigned int pclk = 15000000; // Assuming PCLK = 15 MHz
    unsigned int divisor = pclk / (16 * baud);

    PINSEL0 |= 0x00000005;   // Enable UART0 pins (P0.0 = TXD0, P0.1 = RXD0)

    U0LCR = 0x83;            // 8-bit, no parity, 1 stop bit, DLAB=1
    U0DLL = divisor & 0xFF;
    U0DLM = (divisor >> 8) & 0xFF;
    U0LCR = 0x03;            // Clear DLAB
}

void uart_tx(char c) {
    while (!(U0LSR & 0x20)); // Wait until THR empty
    U0THR = c;
}

void uart_tx_string(char *str) {
    while (*str) {
        uart_tx(*str++);
    }
}
