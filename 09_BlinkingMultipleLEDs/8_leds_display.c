#include <LPC214X.h>
#include "gpio.h"
int main()
{
	while(1)
	{
		portwrite(12,0xFF);
		delay();
		portwrite(12,0x00);
		delay();
	}
}

