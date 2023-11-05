/* Private includes ----------------------------------------------------------*/
#include "app_azure_rtos.h"
#include "adc.h"
#include "tim.h"

/* Private define ------------------------------------------------------------*/
#define ADC_THREAD_STACK_SIZE   1024
#define ADC_THREAD_PRIO         6
#define ADC_THREAD_NAME         "adc"

#define ADC_EVENT_FLAG_NAME     "adc"
/* Private typedef -----------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
static TX_THREAD adc_thread;
static CHAR adc_thread_stack[ADC_THREAD_STACK_SIZE];

static TX_EVENT_FLAGS_GROUP adc_event_flag;

static uint32_t raw_data[64] __attribute__((aligned(32)));
__attribute__((aligned(8))) sys_vol_info_t sys_vol_info = {0};
/* Private function prototypes -----------------------------------------------*/
static void adc_get_ave(uint32_t *addr, uint32_t *ave)
{
    uint32_t sum[4] = {0};

    for (int i = 0; i < 32; i++)	sum[i % 4] += addr[i];
    ave[0] = sum[0] / 8;
    ave[1] = sum[1] / 8;
    ave[2] = sum[2] / 8;
    ave[3] = sum[3] / 8;
}

static void adc_thread_entry(ULONG thread_input)
{
    /* AD Res & Vbat & Temperature sensor & Vref calibration values */
    uint16_t TS_CAL1 = *TEMPSENSOR_CAL1_ADDR;
    uint16_t TS_CAL2 = *TEMPSENSOR_CAL2_ADDR;
    uint16_t VREF_CAL = *VREFINT_CAL_ADDR;
    uint32_t ave_data[4];
    ULONG flag = 0;

    /* Adc Start */
    HAL_TIM_Base_Start(&htim6);
    HAL_ADCEx_Calibration_Start(&hadc3, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED);
    HAL_ADC_Start_DMA(&hadc3, raw_data, 64);

    while (1)
    {
        tx_event_flags_get(&adc_event_flag, 0x11, TX_OR_CLEAR, &flag, TX_WAIT_FOREVER);
        if (flag == 0x01)    adc_get_ave(&raw_data[0], ave_data);
        else if (flag == 0x10)   adc_get_ave(&raw_data[32], ave_data);

        sys_vol_info.ad_res = (double)ave_data[0] * 3.3 / 65536;
        sys_vol_info.vbat = (double)ave_data[1] * 3.3 / 65536 * 4;
        sys_vol_info.temp = (110 - 30) *
                            (ave_data[2] - TS_CAL1) / (TS_CAL2 - TS_CAL1) + 30;
        sys_vol_info.verf = 3.3 * VREF_CAL / ave_data[3];

//      tx_kprintf("ad_res: %f\r\n", sys_vol_info.ad_res);
//      tx_kprintf("vbat: %f\r\n", sys_vol_info.vbat);
//      tx_kprintf("temp: %f\r\n", sys_vol_info.temp);
//      tx_kprintf("verf: %f\r\n", sys_vol_info.verf);
    }
}

UINT app_adc_thread_init(VOID)
{
    if (TX_SUCCESS != tx_event_flags_create(&adc_event_flag, ADC_EVENT_FLAG_NAME))
    {
        return TX_GROUP_ERROR;
    }

    if (tx_thread_create(&adc_thread, ADC_THREAD_NAME, adc_thread_entry, 0, adc_thread_stack,
                         ADC_THREAD_STACK_SIZE, ADC_THREAD_PRIO, ADC_THREAD_PRIO,
                         TX_NO_TIME_SLICE, TX_AUTO_START) != TX_SUCCESS)
    {
        return TX_THREAD_ERROR;
    }

    return TX_SUCCESS;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc == &hadc3)
    {
        tx_event_flags_set(&adc_event_flag, 0x10, TX_OR);
        SCB_InvalidateDCache_by_Addr((uint32_t *)(&raw_data[32]), 128);
    }
}

void HAL_ADC_ConvHalfCpltCallback(ADC_HandleTypeDef *hadc)
{
    if (hadc == &hadc3)
    {
        tx_event_flags_set(&adc_event_flag, 0x01, TX_OR);
        SCB_InvalidateDCache_by_Addr((uint32_t *)raw_data, 128);
    }
}