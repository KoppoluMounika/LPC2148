#include <LPC214x.h>
#include"header.h"
#include"timer.h"

#define SLAVE_ADDRESS 0x50  // 7-bit address



int main(void) {
    i2c_init();  // Initialize I2C master on P0.2 (SCL), P0.3 (SDA)
		uart_init(9600);
		uart_tx_string("Sending to slave\n");
    
    i2c_start();                         // START condition
    i2c_write(SLAVE_ADDRESS << 1);       // SLA+W (write mode)
    i2c_write('A');                      // Send 'A' to slave
    i2c_stop();                          // STOP condition
		uart_tx_string("Done\n");
    delay_ms(100);                             // Wait before next send
    
	  while(1);
}
