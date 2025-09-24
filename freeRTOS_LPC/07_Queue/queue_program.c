#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include <stdio.h>
#include <LPC214x.h>

/* UART Functions */
void init_uart(unsigned int baudrate);
void uart_tx(unsigned char data);
void uart_tx_string(char *str);
unsigned char uart_rx(void);

/* FreeRTOS Tasks */
void sender(void *q);
void receiver(void *q);

/* Queue Handle */
xQueueHandle myqueue;

int main(void) {
    init_uart(9600);

    myqueue = xQueueCreate(5, sizeof(unsigned char)); // Queue holds 5 numbers

    if (myqueue != NULL) {
        xTaskCreate(sender, "Sender", 128, NULL, 1, NULL);
        xTaskCreate(receiver, "Receiver", 128, NULL, 1, NULL);
        vTaskStartScheduler();
    }

    while (1); // Should never reach here
}

/* Send numbers from 0 to 255 repeatedly */
void sender(void *q) {
    unsigned char num = 0;
    while (1) {
        xQueueSendToBack(myqueue, &num, portMAX_DELAY);
        num++;
        vTaskDelay(pdMS_TO_TICKS(100)); // 100 ms delay
    }
}

/* Receive and print numbers */
void receiver(void *q) {
    unsigned char receivedValue;
    char buffer[10];
    while (1) {
        if (xQueueReceive(myqueue, &receivedValue, portMAX_DELAY) == pdPASS) {
            sprintf(buffer, "%d\r\n", receivedValue);
            uart_tx_string(buffer);
        }
    }
}

/* Stack overflow hook */
void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName) {
    uart_tx_string("Stack Overflow!\r\n");
    while (1);
}

/* UART Driver Implementation */
void init_uart(unsigned int baudrate) {
    unsigned int divisor = (60000000 / (16 * baudrate)); // Assuming PCLK=60MHz
    PINSEL0 |= 0x00000005;   // P0.0=TXD0, P0.1=RXD0
    U0LCR = 0x83;            // 8-bit, 1 stop, no parity, DLAB=1
    U0DLL = divisor & 0xFF;
    U0DLM = (divisor >> 8) & 0xFF;
    U0LCR = 0x03;            // DLAB=0
}

void uart_tx(unsigned char data) {
    while (!(U0LSR & (1 << 5))); // Wait for THR empty
    U0THR = data;
}

void uart_tx_string(char *str) {
    while (*str) {
        uart_tx(*str++);
    }
}

unsigned char uart_rx(void) {
    while (!(U0LSR & 0x01)); // Wait for data ready
    return U0RBR;
}
