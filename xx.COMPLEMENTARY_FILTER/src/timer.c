#include "timer.h"

void TIM6_enable(void)
{
	/* Enable TIM6 */
	RCC->APB1ENR |= RCC_APB1ENR_TIM6EN;
	// SET OPM
	TIM6->CR1 |= (uint16_t)(1 << 3);
}

/* Delay function using system clock */
/* SR, the status register. */
/* EGR, the event generation register. */
/* CNT, the counter register. */
/* PSC, the prescaler register. */
/* ARR, the autoreload register. */
void delay(uint16_t ms)
{
	/* Set PSC frequency */
	TIM6->PSC = (uint16_t)799;
	/* Value to reach */
	TIM6->ARR = ms;
	/* enable clock */
	TIM6->CR1 |= (uint16_t)1;
	/* wait event signaling that counter has reach value */
	while (TIM6->SR == 0);
	/* Reset event */
	TIM6->SR = 0;
}
