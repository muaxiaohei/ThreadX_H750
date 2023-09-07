/* Private includes ----------------------------------------------------------*/
#include "app_azure_rtos.h"
#include "adc.h"
#include "dma.h"
#include "tim.h"

/* Private define ------------------------------------------------------------*/
#define ADC_THREAD_STACK_SIZE 	1024
#define ADC_THREAD_PRIO       	11
#define ADC_THREAD_NAME			"adc"

#define ADC_SEM_NAME			"adc"

/* Private typedef -----------------------------------------------------------*/
typedef struct sys_vol_info_s
{
	float ad_res;
	float vbat;
	float temp;
	float verf;
}sys_vol_info_t;
sys_vol_info_t sys_vol_info = {0};

/* Private variables ---------------------------------------------------------*/
static TX_THREAD adc_thread;
static __attribute__((aligned(8), section(".SDRAM"))) CHAR adc_thread_stack[ADC_THREAD_STACK_SIZE];

static TX_SEMAPHORE adc_sem;

static __attribute__((aligned(32))) uint32_t adc_data[4];

/* Private function prototypes -----------------------------------------------*/
static void adc_thread_entry(ULONG thread_input)
{
	/* Temperature sensor calibration values */
	uint16_t TS_CAL1 = *TEMPSENSOR_CAL1_ADDR;
	uint16_t TS_CAL2 = *TEMPSENSOR_CAL2_ADDR;
	uint16_t VREF_CAL = *VREFINT_CAL_ADDR;
	
	/* Adc Start */
    HAL_TIM_Base_Start(&htim6);
    HAL_ADCEx_Calibration_Start(&hadc3, ADC_CALIB_OFFSET_LINEARITY, ADC_SINGLE_ENDED);
    HAL_ADC_Start_DMA(&hadc3, adc_data, 4);

    while(1)
    {
        tx_semaphore_get(&adc_sem, TX_WAIT_FOREVER);

        SCB_InvalidateDCache_by_Addr((uint32_t *)adc_data, sizeof(adc_data));
		sys_vol_info.ad_res = (float)adc_data[0] * 3.3 / 65536;
		sys_vol_info.vbat = (float)adc_data[1] * 3.3 / 65536 * 4;
		sys_vol_info.temp = (110 - 30) * 
								(adc_data[2] - TS_CAL1) / (TS_CAL2 - TS_CAL1) + 30;
		sys_vol_info.verf = 3.3 * VREF_CAL / adc_data[3];
    }
}

UINT app_adc_thread_init(VOID)
{
    if(TX_SUCCESS != tx_semaphore_create(&adc_sem, ADC_SEM_NAME, 0))
    {
        return TX_SEMAPHORE_ERROR;
    }

    if (tx_thread_create(&adc_thread, ADC_THREAD_NAME, adc_thread_entry, 0, adc_thread_stack,
                         ADC_THREAD_STACK_SIZE, ADC_THREAD_PRIO, ADC_THREAD_PRIO,
                         TX_NO_TIME_SLICE, TX_AUTO_START) != TX_SUCCESS)
    {
        return TX_SEMAPHORE_ERROR;
    }

    return TX_SUCCESS;
}

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef *hadc)
{
    if(hadc == &hadc3)
    {
        tx_semaphore_put(&adc_sem);
    }
}