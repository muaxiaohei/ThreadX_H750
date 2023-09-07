/* Private includes ----------------------------------------------------------*/
#include "app_azure_rtos.h"
#include "multi_button.h"
#include "signal_led.h"

/* Private define ------------------------------------------------------------*/
#define IO_THREAD_STACK_SIZE 	1024
#define IO_THREAD_PRIO       	10
#define IO_THREAD_NAME			"io"

/* Private variables ---------------------------------------------------------*/
static TX_THREAD io_thread;
static __attribute__((aligned(8), section(".SDRAM"))) CHAR io_thread_stack[IO_THREAD_STACK_SIZE];
static struct Button button_sw1;
static struct Button button_sw2;

static led_t *led_r =  TX_NULL;
static led_t *led_g =  TX_NULL;
static led_t *led_b =  TX_NULL;

char *led_b_blink_mode = "200,800,";
/* Private function prototypes -----------------------------------------------*/
static uint8_t button_sw1_read(uint8_t paras)
{
    return (uint8_t)USR_KEY_SW1_READ();
}

static uint8_t button_sw2_read(uint8_t paras)
{
    return (uint8_t)USR_KEY_SW2_READ();
}

static void led_r_switch_on(void *args)
{
	LED_R_ON();
}

static void led_r_switch_off(void *args)
{
	LED_R_OFF();
}

static void led_g_switch_on(void *args)
{
	LED_G_ON();
}

static void led_g_switch_off(void *args)
{
	LED_G_OFF();
}

static void led_b_switch_on(void *args)
{
	LED_B_ON();
}

static void led_b_switch_off(void *args)
{
	LED_B_OFF();
}

static void cb1_single_click(void *paras)
{
	tx_kprintf("usr sw1 single click\r\n");
}

static void cb2_single_click(void *paras)
{
	tx_kprintf("usr sw2 single click\r\n");
}

static void io_thread_entry(ULONG thread_input)
{
    while(1)
    {
		led_ticks();
        button_ticks();
        tx_thread_sleep(TICKS_INTERVAL);
	}
}

UINT app_button_thread_init(VOID)
{
    button_init(&button_sw1, button_sw1_read, 1, 0);
    button_attach(&button_sw1, SINGLE_CLICK, cb1_single_click);
    button_start(&button_sw1);

    button_init(&button_sw2, button_sw2_read, 1, 1);
    button_attach(&button_sw2, SINGLE_CLICK, cb2_single_click);
    button_start(&button_sw2);
	
	led_b = led_create(led_b_switch_on, led_b_switch_off, TX_NULL);
	led_set_mode(led_b, 5, led_b_blink_mode);
	led_start(led_b);

	/* Create io thread.  */
    if (tx_thread_create(&io_thread, IO_THREAD_NAME, io_thread_entry, 0, io_thread_stack,
                         IO_THREAD_STACK_SIZE, IO_THREAD_PRIO, IO_THREAD_PRIO,
                         TX_NO_TIME_SLICE, TX_AUTO_START) != TX_SUCCESS)
    {
        return TX_THREAD_ERROR;
    }
	
	return TX_SUCCESS;
}