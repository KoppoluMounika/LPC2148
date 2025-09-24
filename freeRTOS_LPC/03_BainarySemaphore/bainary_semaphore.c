#include <LPC214x.h>
#include <stdlib.h>
#include "FreeRTOS.h"
#include "task.h"
#include "semphr.h"

// ------------------ UART0 DRIVER ------------------
void initserial(void);
void sendsserial(const char *p);

void initserial(void) {
    VPBDIV = 0x01;                   // PCLK = CCLK
    PINSEL0 |= 0x00000005;           // Enable TxD0, RxD0
    U0LCR = 0x83;                    // 8 bits, no parity, 1 stop bit, DLAB=1
    U0DLM = 0x00;
    U0DLL = 97;                      // 9600 baud @ 15MHz PCLK
    U0LCR = 0x03;                    // DLAB = 0
}

void sendsserial(const char *p) {
    while (*p) {
        while (!(U0LSR & 0x20));     // Wait for THR empty
        U0THR = *p++;
    }
}

// ------------------ PLL INIT ------------------
void initpll(void) {
    PLL0CON = 0x01;
    PLL0CFG = 0x24;                  // M=5, P=2 ? CCLK = 60MHz
    PLL0FEED = 0xAA;
    PLL0FEED = 0x55;
    while (!(PLL0STAT & (1 << 10)));
    PLL0CON = 0x03;
    PLL0FEED = 0xAA;
    PLL0FEED = 0x55;
    VPBDIV = 0x01;                   // PCLK = CCLK
}

// ------------------ TASKS ------------------
void task1(void *p);
void task2(void *p);

SemaphoreHandle_t binarysem;

// ------------------ MAIN ------------------
int main(void) {
    initpll();
    initserial();

    binarysem = xSemaphoreCreateBinary();
    if (binarysem != NULL) {
        xSemaphoreGive(binarysem);   // give once initially
    }

    xTaskCreate(task1, "task1", 128, NULL, 1, NULL);
    xTaskCreate(task2, "task2", 128, NULL, 1, NULL);

    vTaskStartScheduler();

    while (1);  // should never reach here
}

// ------------------ TASK DEFINITIONS ------------------
void task1(void *p) {
    while (1) {
        if (xSemaphoreTake(binarysem, portMAX_DELAY) == pdTRUE) {
            sendsserial("Task1 functioning\r\n");
            xSemaphoreGive(binarysem);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));   // delay 1s
    }
}

void task2(void *p) {
    while (1) {
        if (xSemaphoreTake(binarysem, portMAX_DELAY) == pdTRUE) {
            sendsserial("Task2 functioning\r\n");
            xSemaphoreGive(binarysem);
        }
        vTaskDelay(pdMS_TO_TICKS(1000));   // delay 1s
    }
}
