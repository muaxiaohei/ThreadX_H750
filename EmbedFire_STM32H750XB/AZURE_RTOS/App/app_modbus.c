/* Private includes ----------------------------------------------------------*/
#include "agile_modbus.h"
#include "agile_modbus_rtu.h"
#include "app_azure_rtos.h"
#include "ringbuffer.h"
#include "usart.h"

/* Private define ------------------------------------------------------------*/
#define MB_THREAD_STACK_SIZE 	4096
#define MB_THREAD_PRIO 			5
#define MB_THREAD_NAME 			"modbus"

#define MB_BUF_MAX_SIZE 		256
#define MB_SEM_NAME 			"modbus"
/* Private variables ---------------------------------------------------------*/
/* mb thread & sem & buf*/
static TX_THREAD mb_thread;
static CHAR mb_thread_stack[MB_THREAD_STACK_SIZE];

static TX_SEMAPHORE mb_sem;

static __attribute__((aligned(32))) uint8_t mb_buf[2][MB_BUF_MAX_SIZE]; // dual buffer
static volatile uint16_t mb_buf_size = 0;		// current receive size
static volatile uint8_t mb_buf_pos = 0;  		// current buffer

/* agile modbus rtu */
static agile_modbus_rtu_t rtu;
static uint8_t rtu_send_buf[MB_THREAD_STACK_SIZE];
static uint8_t rtu_read_buf[MB_THREAD_STACK_SIZE];

/* Private function prototypes -----------------------------------------------*/
static void mb_thread_entry(ULONG thread_input)		// 此线程只负责解析是否有数据传入，数据的反序列化解析应该交给调用发送和解析的线程
{
    uint8_t buf[MB_BUF_MAX_SIZE] = {0};
    uint8_t buf_pos = 0;
    agile_modbus_t *ctx = &rtu._ctx;

    agile_modbus_rtu_init(&rtu, rtu_send_buf, MB_THREAD_STACK_SIZE, rtu_read_buf, MB_THREAD_STACK_SIZE);
    agile_modbus_set_slave(ctx, 1);

    while (1)
    {
        memset(buf, 0, MB_BUF_MAX_SIZE); // flush receive buffer
        tx_semaphore_get(&mb_sem, TX_WAIT_FOREVER);

        SCB_InvalidateDCache_by_Addr((uint32_t *)mb_buf[mb_buf_pos], MB_BUF_MAX_SIZE);
        buf_pos = (mb_buf_pos != 0 ? 0 : 1);
        memcpy(buf, mb_buf[buf_pos], mb_buf_size);
        tx_kprintf("rec: %s\r\n", buf);
    }
}

/* Exported functions --------------------------------------------------------*/
UINT app_mb_thread_init(VOID)
{
    HAL_UART_ReceiverTimeout_Config(&huart2, huart2.Init.BaudRate / 100); // 10ms receiver timeout
    HAL_UART_EnableReceiverTimeout(&huart2);
    HAL_UART_Receive_DMA(&huart2, mb_buf[mb_buf_pos], MB_BUF_MAX_SIZE);

    if (TX_SUCCESS != tx_semaphore_create(&mb_sem, MB_SEM_NAME, 0))
        return TX_SEMAPHORE_ERROR;

    if (tx_thread_create(&mb_thread, MB_THREAD_NAME, mb_thread_entry, 0, mb_thread_stack, MB_THREAD_STACK_SIZE,
                         MB_THREAD_PRIO, MB_THREAD_PRIO, TX_NO_TIME_SLICE, TX_AUTO_START) != TX_SUCCESS)
    {
        return TX_THREAD_ERROR;
    }

    return TX_SUCCESS;
}

void HAL_UART_ErrorCallback(UART_HandleTypeDef *huart)
{
    if (huart == &huart2)
    {
        if ((huart->ErrorCode & HAL_UART_ERROR_RTO) == HAL_UART_ERROR_RTO)
        {
            mb_buf_size = MB_BUF_MAX_SIZE - __HAL_DMA_GET_COUNTER(huart->hdmarx);
            tx_semaphore_put(&mb_sem);
            mb_buf_pos = (mb_buf_pos != 0 ? 0 : 1);
            HAL_UART_Receive_DMA(&huart2, mb_buf[mb_buf_pos], MB_BUF_MAX_SIZE); // switch to another buffer
        }
    }
}