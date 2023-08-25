#include "app_azure_rtos.h"

#define TEST_THREAD_STACK_SIZE 	4096
#define TEST_THREAD_PRIO       	31

TX_THREAD test_thread;
__attribute__((aligned(8))) CHAR test_stack[TEST_THREAD_STACK_SIZE];

VOID test_entry(ULONG thread_input)
{
	while(1)
	{
		tx_kprintf("test looping\r\n");
		tx_thread_sleep(1000);
	}
}

UINT test_thread_init(VOID)
{
    if(TX_SUCCESS != tx_thread_create(&test_thread, "test", test_entry, 0,
                                      &test_stack[0], TEST_THREAD_STACK_SIZE,
                                      TEST_THREAD_PRIO, TEST_THREAD_PRIO, TX_NO_TIME_SLICE, TX_AUTO_START))
        return TX_THREAD_ERROR;
	
	return TX_SUCCESS;
}