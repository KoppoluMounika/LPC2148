#include<LPC21XX.h>

void delay_ms(int ms){
	T0TC=0;
	T0PR=15000-1;
	T0TCR=1;
	while(T0TC<ms);
	T0TCR=0;
}
void delay_us(int us){
	T0TC=0;
	T0PR=15-1;
	T0TCR=1;
	while(T0TC<us);
	T0TCR=0;
}

