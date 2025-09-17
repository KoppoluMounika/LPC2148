#include <LPC214x.h>

//software delay
void delay(int d) {
    int i, j;
    for (i = 0; i < d; i++) {
        for (j = 0; j < 6000; j++);  //delay
    }
}
int main(void) {
    IO0DIR |= (1 << 11);      // Set P0.11 as output

    while (1) {
        IO0SET = (1 << 11);   // Set P0.11 HIGH ,LED ON
        delay(500);

        IO0CLR = (1 << 11);   // Set P0.11 LOW ,LED OFF
        delay(500);
    }
}
