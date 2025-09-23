#ifndef UART0_H
#define UART0_H

#include <LPC214x.h>

void initserial(unsigned int baudrate);
void sendserial(char c);

#endif /* UART0_H */

