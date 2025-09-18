#include <LPC214x.h> 

#define LED     (1 << 10)   // P0.10
#define SWITCH  (1 << 14)   // P0.14

// Simple delay (~1ms at 60 MHz)
void delay_ms(unsigned int ms) {
    unsigned int i, j;
    for (i = 0; i < ms; i++) {
        for (j = 0; j < 6000; j++);  
    }
}

int main(void) {
    IO0DIR |= LED;      // P0.10 as output
    IO0DIR &= ~SWITCH;  // P0.14 as input

    while (1) {
        if (!(IO0PIN & SWITCH)) {   // switch pressed (active low)
            IO0SET = LED;           // Turn ON LED
            delay_ms(500);
            IO0CLR = LED;           // Turn OFF LED
            delay_ms(500);
        } else {
            IO0CLR = LED;           // switch not pressed ? LED OFF
        }
    }
}
