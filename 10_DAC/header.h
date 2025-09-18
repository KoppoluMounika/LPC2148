#include<LPC214X.h>
void delay_ms(int ms );
void delay_us(int us );
void uart_init(unsigned int baud );
void uart_tx(unsigned char data );
void uart_tx_string(const char *message );
unsigned char uart_rx(void );
void  adc_init(void );
unsigned int adc_read(void );
void uart_tx_int(unsigned int num);
void dac_init(void );
void dac_write(unsigned int digital_data);
