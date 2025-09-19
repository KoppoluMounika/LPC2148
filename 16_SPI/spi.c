#include <LPC214x.h>

#define SSEL_PIN (1<<6)   // P0.6 as SSEL

// UART initialization for 9600 baud
void uart_init(void) {
    PINSEL0 |= 0x05;       // P0.0 = TXD0, P0.1 = RXD0
    U0LCR = 0x83;          // 8-bit, 1 stop, no parity, DLAB=1
    U0DLL = 13;            // 9600 baud @ 15MHz PCLK
    U0DLM = 0;
    U0LCR = 0x03;          // DLAB = 0
}

// UART send string
void uart_tx_string(const char *str) {
    while(*str) {
        while(!(U0LSR & 0x20)); // Wait for THR empty
        U0THR = *str++;
    }
}

// Simple delay (approximate)
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for(i=0; i<ms; i++)
        for(j=0; j<1000; j++);
}

// SPI initialization
void spi_init(void) {
    PINSEL0 |= (1<<14) | (1<<16);   // P0.7 = SCK, P0.9 = MOSI
    PINSEL0 &= ~(1<<15 | 1<<17);

    IODIR0 |= SSEL_PIN;
    IOSET0 = SSEL_PIN;               // SSEL idle high

    S0SPCR = (1<<5) | (1<<2);       // SPI enable, master, CPOL=0, CPHA=0
    S0SPSR = 0;
}

// SPI send one byte
void spi_send(unsigned char data) {
    IOCLR0 = SSEL_PIN;               // SSEL low ? select slave
    S0SPDR = data;
    while(!(S0SPSR & (1<<7)));       // Wait for transfer complete
    IOSET0 = SSEL_PIN;               // SSEL high ? deselect slave
}

int main(void) {
    unsigned char i;
    char temp_str[2];   // Temporary string for UART

    spi_init();
    uart_init();

    uart_tx_string("SPI Master Ready\n");

    while(1) {
        for(i=0; i<5; i++) {
            spi_send('A'+i);          // Send A, B, C, D, E

            // Send debug message over UART
            temp_str[0] = 'A'+i;
            temp_str[1] = '\0';
            uart_tx_string("Sent: ");
            uart_tx_string(temp_str);
            uart_tx_string("\n");

            delay_ms(500);
        }
        uart_tx_string("Cycle complete\n");
        delay_ms(1000);
    }
}
