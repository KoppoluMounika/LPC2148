#include <LPC214x.h>
#include "FreeRTOS.h"
#include "task.h"

/* ---------- Function Declarations ---------- */
void task1(void *param);
void task2(void *param);
void init_pll(void);
void initserial(unsigned int baudrate);
void sendserial(char c);

/* ---------- Global Clock ---------- */
static unsigned long PCLK;

/* ---------- Main ---------- */
int main(void)
{
    init_pll();             // Initialize PLL (System Clock)
    initserial(9600);       // Initialize UART0 at 9600 baud

    // Create two tasks
    xTaskCreate(task1, "Task1", 128, NULL, 2, NULL);
    xTaskCreate(task2, "Task2", 128, NULL, 1, NULL);

    // Start the scheduler
    vTaskStartScheduler();

    // Should never reach here
    while (1);
}

/* ---------- Task 1 ---------- */
void task1(void *param)
{
    const char *msg = "Task 1 is running\r\n";
    while (1)
    {
        const char *p = msg;
        while (*p)
            sendserial(*p++);
        vTaskDelay(pdMS_TO_TICKS(1000));
    }
}

/* ---------- Task 2 ---------- */
void task2(void *param)
{
    const char *msg = "Task 2 is running\r\n";
    while (1)
    {
        const char *p = msg;
        while (*p)
            sendserial(*p++);
        vTaskDelay(pdMS_TO_TICKS(1500));
    }
}

/* ---------- UART0 ---------- */
void initserial(unsigned int baudrate)
{
    unsigned int divisor;

    VPBDIV = 0x01;              // PCLK = CCLK
    PCLK   = 60000000;          // 60 MHz after PLL

    PINSEL0 |= 0x05;            // P0.0=TXD0, P0.1=RXD0
    U0LCR   = 0x83;             // 8N1, DLAB=1

    divisor = (PCLK / (16 * baudrate));
    U0DLL   = divisor & 0xFF;
    U0DLM   = (divisor >> 8) & 0xFF;

    U0LCR   = 0x03;             // DLAB=0, 8N1
}

void sendserial(char c)
{
    while (!(U0LSR & (1 << 5)));  // Wait for THR empty
    U0THR = c;
}

/* ---------- PLL ---------- */
void init_pll(void)
{
    PLL0CON = 0x01;          // Enable PLL
    PLL0CFG = 0x24;          // M=5, P=2 (12MHz * 5 = 60MHz)
    PLL0FEED = 0xAA;
    PLL0FEED = 0x55;

    while (!(PLL0STAT & (1 << 10)));  // Wait for PLL lock

    PLL0CON = 0x03;          // Connect PLL
    PLL0FEED = 0xAA;
    PLL0FEED = 0x55;

    VPBDIV = 0x01;           // PCLK = CCLK = 60 MHz
    PCLK   = 60000000;
}

/* ---------- FreeRTOS Hooks ---------- */
void vApplicationMallocFailedHook(void)
{
    while (1);   // Trap on malloc failure
}

void vApplicationStackOverflowHook(TaskHandle_t xTask, char *pcTaskName)
{
    (void)xTask;
    (void)pcTaskName;
    while (1);   // Trap on stack overflow
}

void vApplicationIdleHook(void)
{
    // Do nothing (no WFI, not supported on ARM7TDMI)
}
