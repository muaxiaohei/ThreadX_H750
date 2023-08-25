#include <stdio.h>
#include "main.h"
#include "dwt.h"

void dwt_init(void)
{
    DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
    DWT->CYCCNT = (uint32_t)0u;
    CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
}	

void dwt_delay_ms(uint32_t ms)
{
	dwt_delay_us(1000 * ms);
}

void dwt_delay_us(uint32_t us)
{
    uint32_t tCnt, tDelayCnt;
	uint32_t tStart;
		
	tStart = DWT->CYCCNT;                          	/* �ս���ʱ�ļ�����ֵ */
	tCnt = 0;
	tDelayCnt = us * (SystemCoreClock / 1000000);	 /* ��Ҫ�Ľ����� */ 		      

	while(tCnt < tDelayCnt)
	{
		tCnt = DWT->CYCCNT - tStart; 				/* ��������У����������һ��32λ���������¼�������Ȼ������ȷ���� */	
	}
}

void dwt_delay_ticks(uint32_t ticks)
{
    uint32_t tCnt, tDelayCnt;
	uint32_t tStart;
		
	tCnt = 0;
	tDelayCnt = ticks;	 				/* ��Ҫ�Ľ����� */ 		      
	tStart = DWT->CYCCNT;         		/* �ս���ʱ�ļ�����ֵ */
	
	while(tCnt < tDelayCnt)
	{
		tCnt = DWT->CYCCNT - tStart; 	/* ��������У����������һ��32λ���������¼�������Ȼ������ȷ���� */	
	}
}

// ���½�����оƬ����64λ��������STM32H750Ҳ���˹���
#if 0
typedef struct
{
	__IOM uint32_t CNTCR;
	__IM  uint32_t CNTSR;
	__IOM uint32_t CNTCVL;
	__IOM uint32_t CNTCVU;
	__IOM uint32_t CNTFID0;
	__IM  uint32_t PIDR4;
	__IM  uint32_t PIDR5;
	__IM  uint32_t PIDR6;
	__IM  uint32_t PIDR7;
	__IM  uint32_t PIDR0;
	__IM  uint32_t PIDR1;
	__IM  uint32_t PIDR2;
	__IM  uint32_t PIDR3;
	__IM  uint32_t CIDR0;
	__IM  uint32_t CIDR1;
	__IM  uint32_t CIDR2;
	__IM  uint32_t CIDR3;
}TSG_TYPE;
#define TSG ((TSG_TYPE *) 0x5C005000)

void tsg_init(void)
{
	TSG->CNTCR = 0x00000000;		// ��ֹ������
	TSG->CNTCVL = 0;				// ��ռ�����
	TSG->CNTCVU = 0;		
	TSG->CNTCR = 0x00000001;		// ʹ�ܼ�����
	TSG->CNTFID0 = 240000000;		// ��Ƶ��һ��
}

void tsg_delay_ms(uint64_t ms)
{
	tsg_delay_us(1000 * ms);
}

void tsg_delay_us(uint64_t us)
{
    uint64_t tCnt, tDelayCnt;
	uint64_t tStart;
		
	tStart = TSG->CNTCVL;                          	/* �ս���ʱ�ļ�����ֵ */
	tStart <<= 32;
	tStart |= TSG->CNTCVU;
	
	tCnt = 0;
	tDelayCnt = us * (TSG->CNTFID0);	 /* ��Ҫ�Ľ����� */ 		      

	while(tCnt < tDelayCnt)
	{
		tCnt = TSG->CNTCVL;                          	/* �ս���ʱ�ļ�����ֵ */
		tCnt <<= 32;
		tCnt |= TSG->CNTCVU;
		tCnt -= tStart; 								/* ��������У����������һ��64λ���������¼�������Ȼ������ȷ���� */	
	}
}

#endif