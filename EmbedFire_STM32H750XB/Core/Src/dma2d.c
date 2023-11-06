/* USER CODE BEGIN Header */
/**
  ******************************************************************************
  * @file    dma2d.c
  * @brief   This file provides code for the configuration
  *          of the DMA2D instances.
  ******************************************************************************
  * @attention
  *
  * Copyright (c) 2023 STMicroelectronics.
  * All rights reserved.
  *
  * This software is licensed under terms that can be found in the LICENSE file
  * in the root directory of this software component.
  * If no LICENSE file comes with this software, it is provided AS-IS.
  *
  ******************************************************************************
  */
/* USER CODE END Header */
/* Includes ------------------------------------------------------------------*/
#include "dma2d.h"

/* USER CODE BEGIN 0 */

/* USER CODE END 0 */

DMA2D_HandleTypeDef hdma2d;

/* DMA2D init function */
void MX_DMA2D_Init(void)
{

  /* USER CODE BEGIN DMA2D_Init 0 */

  /* USER CODE END DMA2D_Init 0 */

  /* USER CODE BEGIN DMA2D_Init 1 */

  /* USER CODE END DMA2D_Init 1 */
  hdma2d.Instance = DMA2D;
  hdma2d.Init.Mode = DMA2D_M2M;
  hdma2d.Init.ColorMode = DMA2D_OUTPUT_ARGB8888;
  hdma2d.Init.OutputOffset = 0;
  hdma2d.LayerCfg[1].InputOffset = 0;
  hdma2d.LayerCfg[1].InputColorMode = DMA2D_INPUT_ARGB8888;
  hdma2d.LayerCfg[1].AlphaMode = DMA2D_NO_MODIF_ALPHA;
  hdma2d.LayerCfg[1].InputAlpha = 0;
  hdma2d.LayerCfg[1].AlphaInverted = DMA2D_REGULAR_ALPHA;
  hdma2d.LayerCfg[1].RedBlueSwap = DMA2D_RB_REGULAR;
  hdma2d.LayerCfg[1].ChromaSubSampling = DMA2D_NO_CSS;
  if (HAL_DMA2D_Init(&hdma2d) != HAL_OK)
  {
    Error_Handler();
  }
  if (HAL_DMA2D_ConfigLayer(&hdma2d, 1) != HAL_OK)
  {
    Error_Handler();
  }
  /* USER CODE BEGIN DMA2D_Init 2 */

  /* USER CODE END DMA2D_Init 2 */

}

void HAL_DMA2D_MspInit(DMA2D_HandleTypeDef* dma2dHandle)
{

  if(dma2dHandle->Instance==DMA2D)
  {
  /* USER CODE BEGIN DMA2D_MspInit 0 */

  /* USER CODE END DMA2D_MspInit 0 */
    /* DMA2D clock enable */
    __HAL_RCC_DMA2D_CLK_ENABLE();
  /* USER CODE BEGIN DMA2D_MspInit 1 */

  /* USER CODE END DMA2D_MspInit 1 */
  }
}

void HAL_DMA2D_MspDeInit(DMA2D_HandleTypeDef* dma2dHandle)
{

  if(dma2dHandle->Instance==DMA2D)
  {
  /* USER CODE BEGIN DMA2D_MspDeInit 0 */

  /* USER CODE END DMA2D_MspDeInit 0 */
    /* Peripheral clock disable */
    __HAL_RCC_DMA2D_CLK_DISABLE();
  /* USER CODE BEGIN DMA2D_MspDeInit 1 */

  /* USER CODE END DMA2D_MspDeInit 1 */
  }
}

/* USER CODE BEGIN 1 */
/**
  * @brief  dma2d fill color function
  * @note   dma2d fill color function
  * @param  dst: color data destination
  * @param  x_size: x axis size, pixels per row
  * @param  y_size: y axis size, row number
  * @param  offline: foreground layer image picture row offset
  * @param  color: color block color
  * @param  pixelformat: destination area color format
  * @retval none
  */
void __dma2d_fill(void *dst, uint32_t x_size, uint32_t y_size,
                  uint32_t offline, uint32_t color, uint32_t pixelformat)
{
    /* DMA2D ���üĴ������洢��ģʽ, ����ģʽ�ò���ǰ����ͱ����� */
    DMA2D->CR = (0x03UL << 16) | (1 << 9);
    DMA2D->OCOLR = color;

    /* ����������ɫĿ�ĵ�ַ */
    DMA2D->OMAR    = (uint32_t)dst;

    /* Ŀ����ƫ�Ƶ�ַ */
    DMA2D->OOR     = offline;

    /* ������ɫ��ʽ */
    DMA2D->OPFCCR  = pixelformat;

    /* ��������С */
    DMA2D->NLR     = (uint32_t)(x_size << 16) | (uint16_t)y_size;

    /* �������� */
    DMA2D->CR     |= DMA2D_CR_START;

    /* �ȴ�DMA2D������� */
    while (DMA2D->CR & DMA2D_CR_START);
}

/**
  * @brief  dma2d copy color data from forground layer to destination
  * @note   dma2d copy certain area color data from forground layer to destination
  * @param  src: color data source
  * @param  dst: color data destination
  * @param  x_size: x axis size, pixels per row
  * @param  y_size: y axis size, row number
  * @param  src_offline: foreground layer image picture row offset
  * @param  dst_offline: output row offset
  * @param  pixelformat: destination area color format
  * @retval none
  */
void __dma2d_copy(void *src, void *dst, uint32_t x_size, uint32_t y_size,
                  uint32_t src_offline, uint32_t dst_offline, uint32_t pixelformat)
{
    /* DMA2D ���ô洢�����洢��ģʽ, ����ģʽ��ǰ������Ϊ DMA2D ���� */
    DMA2D->CR = (0x00UL) | (1 << 9);
    DMA2D->FGMAR = (uint32_t)src;
    DMA2D->OMAR = (uint32_t)dst;
    DMA2D->FGOR = src_offline;
    DMA2D->OOR = dst_offline;

    /* ǰ�����������򶼲��õ� ARGB8888 ��ɫ��ʽ */
    DMA2D->FGPFCCR = pixelformat;
    DMA2D->OPFCCR = pixelformat;

    DMA2D->NLR = (uint32_t)(x_size << 16) | (uint16_t)y_size;
	
	SCB_CleanInvalidateDCache();
    /* �������� */
    DMA2D->CR     |= DMA2D_CR_START;

    /* �ȴ�DMA2D������� */
    while (DMA2D->CR & DMA2D_CR_START);
}

/**
  * @brief  dma2d color blending between foreground layer and target area
  * @note   dma2d color blending between foreground layer and target area
  * @param  src: color data source
  * @param  dst: color data destination
  * @param  x_size: x axis size, pixels per row
  * @param  y_size: y axis size, row number
  * @param  src_offline: foreground layer image picture row offset
  * @param  dst_offline: output row offset
  * @param  alpha: set the transparency of the foreground layer, 
  *			255 represents complete opacity, 0 represents complete transparency
  * @retval none
  */
void __dma2d_mixcolorsbulk(void *src, void *dst, uint32_t x_size, uint32_t y_size,
                           uint32_t src_offline, uint32_t dst_offline, uint8_t alpha)
{
    /* DMA2D ���ô洢�����洢��ģʽ, ����ģʽǰ����ͱ�������Ϊ DMA2D ���룬��֧����ɫ��ʽת������ɫ��� */
    DMA2D->CR = (0x02UL << 16) | (1 << 9);
    DMA2D->FGMAR = (uint32_t)src;
    DMA2D->BGMAR = (uint32_t)dst;
    DMA2D->OMAR = (uint32_t)dst;
    DMA2D->FGOR = src_offline;
    DMA2D->BGOR = dst_offline;
    DMA2D->OOR = dst_offline;

    /* ǰ���㣬�����������������õ� ARGB8888 ��ʽ */
    DMA2D->FGPFCCR = LTDC_PIXEL_FORMAT_ARGB8888 | (1UL << 16) | ((uint32_t)alpha << 24);
    DMA2D->BGPFCCR = LTDC_PIXEL_FORMAT_ARGB8888;
    DMA2D->OPFCCR = LTDC_PIXEL_FORMAT_ARGB8888;

    DMA2D->NLR = (uint32_t)(x_size << 16) | (uint16_t)y_size;

    /* �������� */
    DMA2D->CR     |= DMA2D_CR_START;

    /* �ȴ�DMA2D������� */
    while (DMA2D->CR & DMA2D_CR_START);
}

/**
  * @brief  dma2d color blending between foreground layer and background layer
  * @note   dma2d color blending between foreground layer and background layer
  * @param  fg_src: foreground layer color data source
  * @param  bg_src: background layer color data source
  * @param  dst: color data destination
  * @param  x_size: x axis size, pixels per row
  * @param  y_size: y axis size, row number
  * @param  src_offline: foreground layer image picture row offset
  * @param  bg_offline: background layer image picture row offset
  * @param  dst_offline: output row offset
  * @retval none
  */
void __dma2d_alphablendingbulk(void *fg_src, void *bg_src, void *dst, uint32_t x_size, uint32_t y_size,
                               uint32_t fg_offline, uint32_t bg_offline, uint32_t dst_offline)
{
    /* DMA2D ���ô洢�����洢��ģʽ, ����ģʽǰ����ͱ�������Ϊ DMA2D ���룬��֧����ɫ��ʽת������ɫ��� */
    DMA2D->CR = (0x02UL << 16) | (1 << 9);
    DMA2D->FGMAR = (uint32_t)fg_src;
    DMA2D->BGMAR = (uint32_t)bg_src;
    DMA2D->OMAR = (uint32_t)dst;
    DMA2D->FGOR = fg_offline;
    DMA2D->BGOR = bg_offline;
    DMA2D->OOR = dst_offline;

    /* ǰ���㣬�����������������õ� ARGB8888 ��ʽ */
    DMA2D->FGPFCCR = LTDC_PIXEL_FORMAT_ARGB8888;
    DMA2D->BGPFCCR = LTDC_PIXEL_FORMAT_ARGB8888;
    DMA2D->OPFCCR = LTDC_PIXEL_FORMAT_ARGB8888;

    DMA2D->NLR = (uint32_t)(x_size << 16) | (uint16_t)y_size;

    /* �������� */
    DMA2D->CR     |= DMA2D_CR_START;

    /* �ȴ�DMA2D������� */
    while (DMA2D->CR & DMA2D_CR_START);
}

/**
  * @brief  dma2d ARGB8888 format bitmap display
  * @note   dma2d ARGB8888 format bitmap display
  * @param  src: color data source
  * @param  dst: color data destination
  * @param  x_size: x axis size, pixels per row
  * @param  y_size: y axis size, row number
  * @param  src_offline: foreground layer image picture row offset
  * @param  dst_offline: output row offset
  * @param  pixelformat: destination area color format
  * @retval none
  */
void __dma2d_drawalpha_bitmap(void *src, void *dst, uint32_t x_size, uint32_t y_size,
                              uint32_t src_offline, uint32_t dst_offline, uint32_t pixelformat)
{
    /* DMA2D ���ô洢�����洢��ģʽ, ����ģʽǰ����ͱ�������Ϊ DMA2D ���룬��֧����ɫ��ʽת������ɫ��� */
    DMA2D->CR = (0x02UL << 16) | (1 << 9);
    DMA2D->FGMAR = (uint32_t)src;
    DMA2D->BGMAR = (uint32_t)dst;
    DMA2D->OMAR = (uint32_t)dst;
    DMA2D->FGOR = src_offline;
    DMA2D->BGOR = dst_offline;
    DMA2D->OOR = dst_offline;

    /* ǰ������ɫ��ʽ�� LTDC_PIXEL_FORMAT_ARGB8888����λͼ����ɫ��ʽ����������������ɫ��ʽ������ */
    DMA2D->FGPFCCR = LTDC_PIXEL_FORMAT_ARGB8888;
    DMA2D->BGPFCCR = pixelformat;
    DMA2D->OPFCCR = pixelformat;

    DMA2D->NLR = (uint32_t)(x_size << 16) | (uint16_t)y_size;

    /* �������� */
    DMA2D->CR     |= DMA2D_CR_START;

    /* �ȴ�DMA2D������� */
    while (DMA2D->CR & DMA2D_CR_START);
}
/* USER CODE END 1 */
