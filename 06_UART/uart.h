#ifndef UART_H
#define UART_H

void init_uart(unsigned int baud);
void uart_tx(char c);
void uart_tx_string(char *str);

#endif
