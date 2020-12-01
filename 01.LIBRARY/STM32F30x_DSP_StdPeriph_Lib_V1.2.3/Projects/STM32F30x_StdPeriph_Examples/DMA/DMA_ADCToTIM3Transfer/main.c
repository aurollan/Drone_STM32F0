/**
  ******************************************************************************
  * @file    DMA/DMA_ADCToTIM3Transfer/main.c 
  * @author  MCD Application Team
  * @version V1.1.2
  * @date    14-August-2015
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT 2015 STMicroelectronics</center></h2>
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software 
  * distributed under the License is distributed on an "AS IS" BASIS, 
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */


/* Includes ------------------------------------------------------------------*/
#include "stm32f30x.h"

/** @addtogroup STM32F30x_StdPeriph_Examples
  * @{
  */

/** @addtogroup DMA_ADCToTIM3Transfer
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
#define ADC1_DR_ADDRESS     0x50000040
#define TIM3_CCR3_ADDRESS   0x4000043C
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
__IO uint16_t calibration_value = 0;
__IO uint32_t TimingDelay = 0;
/* Private function prototypes -----------------------------------------------*/
static void ADC_Config(void);
static void DMA_Config(void);
static void TIM3_Config(void);
void Delay(__IO uint32_t nTime);
/* Private functions ---------------------------------------------------------*/

/**
  * @brief  Main program.
  * @param  None
  * @retval None
  */
int main(void)
{
  /*!< At this stage the microcontroller clock setting is already configured, 
       this is done through SystemInit() function which is called from startup
       file (startup_stm32f30x.s) before to branch to application main.
       To reconfigure the default setting of SystemInit() function, refer to
       system_stm32f30x.c file
       */
  
  /* DMA1 channel1 configuration */
  DMA_Config();
  
  /* TIM3 channel3 configuration */
  TIM3_Config();
  
  /* ADC channel7 configuration */
  ADC_Config();
  
  while (1)
  {
  }
}

/**
  * @brief  Configures DMA1 channel1 to transfer data from 
  *                    ADC1_DR_ADDRESS to TIM3_CCR3_ADDRESS
  * @param  None
  * @retval None
  */
static void DMA_Config(void)
{
  DMA_InitTypeDef  DMA_InitStructure;
  
  /* Enable DMA1 clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
  
  DMA_DeInit(DMA1_Channel1);
  DMA_InitStructure.DMA_PeripheralBaseAddr = (uint32_t)TIM3_CCR3_ADDRESS;
  DMA_InitStructure.DMA_MemoryBaseAddr = (uint32_t)ADC1_DR_ADDRESS;
  DMA_InitStructure.DMA_DIR = DMA_DIR_PeripheralDST;
  DMA_InitStructure.DMA_BufferSize = 1;
  DMA_InitStructure.DMA_PeripheralInc = DMA_PeripheralInc_Disable;
  DMA_InitStructure.DMA_MemoryInc = DMA_MemoryInc_Disable;
  DMA_InitStructure.DMA_PeripheralDataSize = DMA_PeripheralDataSize_HalfWord;
  DMA_InitStructure.DMA_MemoryDataSize = DMA_MemoryDataSize_HalfWord;
  DMA_InitStructure.DMA_Mode = DMA_Mode_Circular;
  DMA_InitStructure.DMA_Priority = DMA_Priority_High;
  DMA_InitStructure.DMA_M2M = DMA_M2M_Disable;
  DMA_Init(DMA1_Channel1, &DMA_InitStructure);
  
  /* Enable DMA1 Channel1 */
  DMA_Cmd(DMA1_Channel1, ENABLE);
}

/**
  * @brief  Configures the ADC1 channel7 in continuous mode.
  * @param  None
  * @retval None
  */
static void ADC_Config(void)
{
  GPIO_InitTypeDef   GPIO_InitStructure;
  ADC_InitTypeDef    ADC_InitStructure;
  ADC_CommonInitTypeDef ADC_CommonInitStructure;

  /* Enable the GPIOC Clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOC, ENABLE);
  
  /* Configure the ADC clock */  
  RCC_ADCCLKConfig(RCC_ADC12PLLCLK_Div2);

  /* ADC1 Periph clock enable */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_ADC12, ENABLE);
  
  /* Setup SysTick Timer for 1 �sec interrupts  */
  if (SysTick_Config(SystemCoreClock / 1000000))
  { 
    /* Capture error */ 
    while (1)
    {}
  }
  
  /* Configure PC.1 (ADC Channel7) in analog mode */
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AN;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_NOPULL;
  GPIO_Init(GPIOC, &GPIO_InitStructure);  

  ADC_StructInit(&ADC_InitStructure);
  
  /* Calibration procedure */
  ADC_VoltageRegulatorCmd(ADC1, ENABLE);
  
  /* Insert delay equal to 10 �s */
  Delay(10);
  
  ADC_SelectCalibrationMode(ADC1, ADC_CalibrationMode_Single);
  ADC_StartCalibration(ADC1);
  
  while(ADC_GetCalibrationStatus(ADC1) != RESET );
  calibration_value = ADC_GetCalibrationValue(ADC1);
  
  /* Configure the ADC1 in continuous mode */  
  ADC_CommonInitStructure.ADC_Mode = ADC_Mode_Independent;                                                                    
  ADC_CommonInitStructure.ADC_Clock = ADC_Clock_AsynClkMode;                  
  ADC_CommonInitStructure.ADC_DMAAccessMode = ADC_DMAAccessMode_Disabled;             
  ADC_CommonInitStructure.ADC_DMAMode = ADC_DMAMode_OneShot;                  
  ADC_CommonInitStructure.ADC_TwoSamplingDelay = 0;          
  
  ADC_CommonInit(ADC1, &ADC_CommonInitStructure);
  
  ADC_InitStructure.ADC_ContinuousConvMode = ADC_ContinuousConvMode_Enable;
  ADC_InitStructure.ADC_Resolution = ADC_Resolution_12b; 
  ADC_InitStructure.ADC_ExternalTrigConvEvent = ADC_ExternalTrigConvEvent_0;         
  ADC_InitStructure.ADC_ExternalTrigEventEdge = ADC_ExternalTrigEventEdge_None;
  ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
  ADC_InitStructure.ADC_OverrunMode = ADC_OverrunMode_Disable;   
  ADC_InitStructure.ADC_AutoInjMode = ADC_AutoInjec_Disable;   
  ADC_InitStructure.ADC_NbrOfRegChannel = 1;
  ADC_Init(ADC1, &ADC_InitStructure);
  
  /* ADC1 regular channel7 configuration */ 
  ADC_RegularChannelConfig(ADC1, ADC_Channel_7, 1, ADC_SampleTime_181Cycles5);
  
  /* Enable ADC1 */
  ADC_Cmd(ADC1, ENABLE);

  /* wait for ADRDY */
  while(!ADC_GetFlagStatus(ADC1, ADC_FLAG_RDY));
  
  /* ADC1 DMA Enable */
  ADC_DMACmd(ADC1, ENABLE);
  ADC_DMAConfig(ADC1, ADC_DMAMode_Circular);
  
  /* Start ADC1 Software Conversion */ 
  ADC_StartConversion(ADC1);
}

/**
  * @brief  Configures the TIM3 channel3 in PWM mode
  * @param  None
  * @retval None
  */
static void TIM3_Config(void)
{
  TIM_TimeBaseInitTypeDef   TIM_TimeBaseStructure;
  TIM_OCInitTypeDef         TIM_OCInitStructure;
  GPIO_InitTypeDef          GPIO_InitStructure;
  
  /* Enable GPIOB clock */
  RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);
  
  /* GPIOB Configuration: PB0(TIM3 CH3) as alternate function push-pull */
  GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF;
  GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
  GPIO_InitStructure.GPIO_OType = GPIO_OType_PP;
  GPIO_InitStructure.GPIO_PuPd  = GPIO_PuPd_UP;
  GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;
  GPIO_Init(GPIOB, &GPIO_InitStructure);
  GPIO_PinAFConfig(GPIOB, GPIO_PinSource0, GPIO_AF_2);

  /* Enable TIM3 clock */
  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
  
  /* Time Base configuration */
  TIM_TimeBaseStructInit(&TIM_TimeBaseStructure); 
  TIM_TimeBaseStructure.TIM_Period = 0xFF0;
  TIM_TimeBaseStructure.TIM_Prescaler = 0x0;
  TIM_TimeBaseStructure.TIM_ClockDivision = 0x0;
  TIM_TimeBaseStructure.TIM_CounterMode = TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, &TIM_TimeBaseStructure);
  
  /* Channel3 Configuration in PWM mode */
  TIM_OCInitStructure.TIM_OCMode = TIM_OCMode_PWM1; 
  TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;
  TIM_OCInitStructure.TIM_Pulse = 0xF0;
  TIM_OCInitStructure.TIM_OCPolarity = TIM_OCPolarity_High;
  TIM_OC3Init(TIM3, &TIM_OCInitStructure);

  /* Enable TIM3 */  
  TIM_Cmd(TIM3, ENABLE);
}

/**
  * @brief  Inserts a delay time.
  * @param  nTime: specifies the delay time length, in milliseconds.
  * @retval None
  */
void Delay(__IO uint32_t nTime)
{ 
  TimingDelay = nTime;

  while(TimingDelay != 0);
}

#ifdef  USE_FULL_ASSERT

/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t* file, uint32_t line)
{ 
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */

  /* Infinite loop */
  while (1)
  {
  }
}
#endif

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
