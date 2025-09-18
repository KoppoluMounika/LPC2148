#include <lpc21xx.h>
#include <stdint.h>

//-------------------- UART0 Init --------------------
void UART0_Init(void) {
    unsigned int divisor;

    // Select TXD0 (P0.0) and RXD0 (P0.1)
    PINSEL0 |= 0x00000005;  

    U0LCR = 0x83;          // 8-bit, 1 stop, no parity, DLAB=1

    // Baud rate = 9600, PCLK = 60 MHz
    divisor = 60000000 / (16 * 9600);  
    U0DLL = divisor & 0xFF;
    U0DLM = (divisor >> 8) & 0xFF;

    U0LCR = 0x03;          // Clear DLAB, 8-bit, 1 stop, no parity
    U0FCR = 0x07;          // Enable FIFO, clear RX/TX FIFO
}

//-------------------- Send One Character --------------------
void UART0_SendChar(char c) {
    while (!(U0LSR & (1 << 5)));  // Wait until THR empty
    U0THR = c;
}

//-------------------- Send String --------------------
void UART0_SendString(char *str) {
    while (*str) {
        UART0_SendChar(*str++);
    }
}

//-------------------- Receive One Character --------------------
char UART0_ReceiveChar(void) {
    while (!(U0LSR & (1 << 0)));  // Wait until RBR has data
    return U0RBR;
}

//-------------------- Delay (ms) --------------------
void delay_ms(uint32_t ms) {
    uint32_t i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 6000; j++);  // ~1ms delay @ 60 MHz
    }
}

//-------------------- MAIN --------------------
int main(void) {
    char c;
    UART0_Init();

    UART0_SendString("UART0 Initialized\r\n");

    while (1) {
        c = UART0_ReceiveChar();   // Wait for input
        UART0_SendChar(c);         // Echo back
    }
}
