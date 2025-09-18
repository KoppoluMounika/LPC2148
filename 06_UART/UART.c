#include <LPC21xx.h>
#include "uart.h"
#include "timer.h"

int main() {
    init_uart(9600);
    while (1) {
        uart_tx_string("hello world");
        uart_tx_string("\r\n");
        delay_ms(1000);
    }
		
}
