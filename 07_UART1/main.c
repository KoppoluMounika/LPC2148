#include"header.h"
#include"timer.h"
#include<LPC21XX.h>
int main()
{
	init_uart(9600);
	while(1){
		uart_tx_string("initialised UART0");
		uart_tx_string("\n\r");
		delay_ms(100);
	}
}


