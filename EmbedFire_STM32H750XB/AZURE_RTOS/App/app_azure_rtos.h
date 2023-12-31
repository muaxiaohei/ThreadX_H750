/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    app_azure_rtos.h
  * @author  MCD Application Team
  * @brief   app_azure_rtos application header file
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2020-2021 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef APP_AZURE_RTOS_H
#define APP_AZURE_RTOS_H
#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "app_azure_rtos_config.h"

#include "app_threadx.h"
/* Private includes ----------------------------------------------------------*/
/* USER CODE BEGIN Includes */
#include <main.h>
/* USER CODE END Includes */

/* Exported types ------------------------------------------------------------*/
/* USER CODE BEGIN ET */
typedef struct sys_vol_info_s
{
    double ad_res;
    double vbat;
    double temp;
    double verf;
} sys_vol_info_t;
/* USER CODE END ET */

/* Exported constants --------------------------------------------------------*/
/* USER CODE BEGIN EC */

/* USER CODE END EC */

/* Exported macro ------------------------------------------------------------*/
/* USER CODE BEGIN EM */

/* USER CODE END EM */

/* Exported functions prototypes ---------------------------------------------*/
/* USER CODE BEGIN EFP */
void tx_kprintf(const char *fmt, ...);

UINT app_io_thread_init(VOID);
UINT app_adc_thread_init(VOID);
UINT app_idle_thread_init(VOID);
UINT app_mb_thread_init(VOID);
/* USER CODE END EFP */

/* Private defines -----------------------------------------------------------*/
/* USER CODE BEGIN PD */

/* USER CODE END PD */

#ifdef __cplusplus
}
#endif

#endif /* APP_AZURE_RTOS_H */
