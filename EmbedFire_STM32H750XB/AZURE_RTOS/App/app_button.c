/* Private includes ----------------------------------------------------------*/
#include "app_azure_rtos.h"
#include "multi_button.h"

/* Private define ------------------------------------------------------------*/
#define BUTTON_THREAD_STACK_SIZE 	1024
#define BUTTON_THREAD_PRIO       	10
#define BUTTON_THREAD_NAME			"button"

/* Private variables ---------------------------------------------------------*/
static TX_THREAD button_thread;
static __attribute__((aligned(8))) CHAR button_thread_stack[BUTTON_THREAD_STACK_SIZE];
static struct Button button_sw1;
static struct Button button_sw2;

/* Private function prototypes -----------------------------------------------*/
static uint8_t button_sw1_read(uint8_t paras)
{
    return (uint8_t)USR_KEY_SW1_READ();
}

static uint8_t button_sw2_read(uint8_t paras)
{
    return (uint8_t)USR_KEY_SW2_READ();
}

static void button_thread_entry(ULONG thread_input)
{
    while(1)
    {
        button_ticks();
        tx_thread_sleep(TICKS_INTERVAL);
	}
}

static void cb1_single_click(void *paras)
{
	tx_kprintf("usr sw1 double click\r\n");
}

static void cb2_single_click(void *paras)
{
	tx_kprintf("usr sw2 single click\r\n");
}

UINT app_button_thread_init(VOID)
{
    button_init(&button_sw1, button_sw1_read, 1, 0);
    button_attach(&button_sw1, DOUBLE_CLICK, cb1_single_click);
    button_start(&button_sw1);

    button_init(&button_sw2, button_sw2_read, 1, 1);
    button_attach(&button_sw2, SINGLE_CLICK, cb2_single_click);
    button_start(&button_sw2);

	/* Create button thread.  */
    if (tx_thread_create(&button_thread, BUTTON_THREAD_NAME, button_thread_entry, 0, button_thread_stack,
                         BUTTON_THREAD_STACK_SIZE, BUTTON_THREAD_PRIO, BUTTON_THREAD_PRIO,
                         TX_NO_TIME_SLICE, TX_AUTO_START) != TX_SUCCESS)
    {
        return TX_THREAD_ERROR;
    }
	
	return TX_SUCCESS;
}