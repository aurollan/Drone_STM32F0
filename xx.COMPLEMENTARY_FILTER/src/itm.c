#include "itm.h"

void ITM_init(void)
{
	CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;
	TPI->ACPR = 8000000 / 2000000 - 1;
	TPI->FFCR |= 0x100; // default value bti 8 always at 1 and bit 2 activate formatter
	TPI->SPPR = 2; // other asynchronous value : NRZ
	DBGMCU->CR |= DBGMCU_CR_TRACE_IOEN;
	ITM->TPR = ITM_TPR_PRIVMASK_Msk;
	ITM->LAR = 0xC5ACCE55;						/* ITM Lock Access Register */
	TPI->CSPSR |= (1 << 0); // 0x1 for 1 pin (default)
	ITM->TCR |= ITM_TCR_ITMENA_Msk | (1 << 3) | (1 << 16);     /* ITM enabled */
	ITM->TER |= (1UL << 0); 			/* ITM Port #0 enabled */
}

int _write(int32_t file, char* ptr, int32_t len)
{
	(void)file;
	int i=0;
	for(i=0 ; i<len ; i++)
		ITM_SendChar((*ptr++));
	return i;
}
