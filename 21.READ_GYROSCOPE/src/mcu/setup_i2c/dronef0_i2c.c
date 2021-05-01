#include "stm32f0xx_i2c.h"
#include "stm32f0xx_gpio.h"
#include "stm32f0xx_rcc.h"

static void GPIOB_for_i2c1_initialize()
{
    GPIO_InitTypeDef GPIOB_init;

    /** 
     * Init struct with default setup
     */
    GPIO_StructInit(&GPIOB_init);

    /** 
     * Enabling clock
     * GPIOB on AHBENR
     */
    RCC_AHBPeriphClockCmd(RCC_AHBPeriph_GPIOB, ENABLE);

    /**
     * GPIOB6 AF1  = I2C1_SCL  => available but potentialy used by USART1
     * GPIOB7 AF1  = I2C1_SDA  => available but potentialy used by USART1
     *
     * GPIOB8 AF1  = I2C1_SCL  => available and selected
     * GPIOB9 AF1  = I2C1_SDA  => available and selected
     *
     * GPIOB10 AF1 = I2C2_SCL  => available and selected
     * GPIOB11 AF1 = I2C2_SDA  => available and selected
     */

    GPIOB_init.GPIO_Mode  = GPIO_Mode_AF;
    GPIOB_init.GPIO_OType = GPIO_OType_OD;
    GPIOB_init.GPIO_Speed = GPIO_Speed_Level_2;
    GPIOB_init.GPIO_PuPd  = GPIO_PuPd_NOPULL;
    GPIOB_init.GPIO_Pin   = GPIO_Pin_8 | GPIO_Pin_9 | GPIO_Pin_10 | GPIO_Pin_11;

    /**
     * Init GPIOB for I2C
     */
    GPIO_Init(GPIOB, &GPIOB_init);

    /**
     * Alternate Function = 1
     * Note That we don't use the same Pin Macro
     * And both pin use the same AF.
     */
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource8,  GPIO_AF_1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource9,  GPIO_AF_1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource10, GPIO_AF_1);
    GPIO_PinAFConfig(GPIOB, GPIO_PinSource11, GPIO_AF_1);
}


void I2C1_initialize()
{
    I2C_InitTypeDef I2C1_init;

    I2C_ClearFlag(I2C1,I2C_FLAG_BUSY);
    I2C_DeInit(I2C1);
    /** 
     * Init struct with default setup
     */
    I2C_StructInit(&I2C1_init);

    /**
     * Enabling clock
     * I2C1 is on APB1ENR
     */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1, ENABLE);

    /**
     * Disabling i2c as asked in reference manual
     */
    I2C_Cmd(I2C1, DISABLE);

    /**
     * Setting I2C1 according to our needs
     */
    I2C1_init.I2C_Ack                 = I2C_Ack_Disable;
    I2C1_init.I2C_AcknowledgedAddress = I2C_AcknowledgedAddress_7bit;
    I2C1_init.I2C_AnalogFilter        = I2C_AnalogFilter_Enable;
    I2C1_init.I2C_Mode                = I2C_Mode_I2C;
    I2C1_init.I2C_DigitalFilter       = 0;
    I2C1_init.I2C_OwnAddress1         = 0;
    /**
     * config tool from reference manual example page 559 
     * SYSCLOCK = 8 Mhz
     * PRESC    = 1
     * SCLL     = 0x13
     * SCLH     = 0xF
     * SDADEL   = 0x2
     * SCLDEL   = 0x4
     * */
    I2C1_init.I2C_Timing              = 0x10240F13;

    I2C_Init(I2C1, &I2C1_init);

    /**
     * Don't forget to enable your i2c too
     */
    I2C_Cmd(I2C1, ENABLE);
}


void i2c_initialize() 
{
    /** 
     * Setting up all available GPIOB pins for I2C1
     */
    GPIOB_for_i2c1_initialize();

    /** 
     * Setting up I2C1
     */
    I2C1_initialize();
}
