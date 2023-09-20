/* Private includes ----------------------------------------------------------*/
#include "app_azure_rtos.h"
#include "iwdg.h"

/* Private define ------------------------------------------------------------*/
#define IDLE_THREAD_STACK_SIZE 	1024
#define IDLE_THREAD_PRIO       	31
#define IDLE_THREAD_NAME			"idle"

/* Private variables ---------------------------------------------------------*/
static TX_THREAD idle_thread;
static __attribute__((aligned(8), section(".SDRAM"))) CHAR idle_thread_stack[IDLE_THREAD_STACK_SIZE];

static void idle_thread_entry(ULONG thread_input)
{
	while(1)
	{
		HAL_IWDG_Refresh(&hiwdg1);
		tx_thread_sleep(100);
	}
}

UINT app_idle_thread_init(VOID)
{
	if (tx_thread_create(&idle_thread, IDLE_THREAD_NAME, idle_thread_entry, 0, idle_thread_stack,
                         IDLE_THREAD_STACK_SIZE, IDLE_THREAD_PRIO, IDLE_THREAD_PRIO,
                         TX_NO_TIME_SLICE, TX_AUTO_START) != TX_SUCCESS)
    {
        return TX_THREAD_ERROR;
    }

    return TX_SUCCESS;
}