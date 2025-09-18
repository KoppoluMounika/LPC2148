#include<LPC21XX.h>
//#include"header.h"
void init_uart(unsigned int baud);
void uart_tx(unsigned char data);
void uart_tx_string(const char *str);
unsigned char uart_rx(void);

#define THRE ((U0LSR>>5)&1)
#define RDR (U0LSR&1)


void init_uart(unsigned int baud){
  int result;
  int a[] = {1, 4, 2, 1};
  unsigned int pclk = a[VPBDIV & 0x03] * 15000000;

  PINSEL0 |= 0x05;

  result = (pclk / (baud * 16));

  U0LCR = 0x83;
  U0DLL = (result & 0xFF);
  U0DLM = ((result >> 8) & 0xFF);
  U0LCR = 0x03;
	U0LCR=0x03;
}

void uart_tx(unsigned char data){
	U0THR=data;
	while(THRE==0);
}

void uart_tx_string(const char *str){
	int i;
	for(i=0;str[i];i++){
		uart_tx(str[i]);
	}
}

unsigned char uart_rx(void){
	unsigned char data;
	while(RDR==0);
	data=U0RBR;
	return data;
}
	
	
