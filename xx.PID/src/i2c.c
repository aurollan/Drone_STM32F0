#include "i2c.h"

void  I2C_Init()
{
	/* Init the I2C  Clock*/
	RCC->APB1ENR |= RCC_APB1ENR_I2C1EN;            /*!< I2C clock enable */

	// Deinit Peripheral => Software RESET
	I2C1->CR1 &= ~I2C_CR1_PE;

	// But if you want to nake sure nothing is set
	// all unreserved bits are set to 0
	// we must NOT reset reserved bits
	I2C1->CR1 &= ~((uint32_t)0x00FFDFFF); 

	// For 8 Mhz I2C clock Standart mode 100 Khz
	// PRESC = (0x1 << 28)
	I2C1->TIMINGR |= (0x1 << 28);
	// SCLDEL =  (0x4 << 20) 
	I2C1->TIMINGR |= (0x4 << 20);
	// SDADEL = (0x2 << 16)
	I2C1->TIMINGR |= (0x2 << 16);
	// SCLH = (0xF << 8)
	I2C1->TIMINGR |= (0xF << 8);
	// SCLL = (0x13 << 0)
	I2C1->TIMINGR |= (0x13 << 0);

	// Enable Peripheral
	I2C1->CR1 |= I2C_CR1_PE;
}

void ENABLE_GPIOB_SCA_SCL(void)
{
	// Enable GPIOB clock
	RCC->AHBENR |= RCC_AHBENR_GPIOBEN;

	// Setting alternate function MODE
	GPIOB->MODER |= GPIO_Mode_AF << 6 * 2; // alternate function mode
	GPIOB->MODER |= GPIO_Mode_AF << 7 * 2; // alternate function mode

	// Clearing previous Alternate Function configuration
	GPIOB->AFR[0] &= ~(0xF << (6 * 4));
	GPIOB->AFR[0] &= ~(0xF << (7 * 4));

	// Setting New Alternate Function configuration 
	GPIOB->AFR[0] |= (GPIO_AF_4 << (6 * 4));
	GPIOB->AFR[0] |= (GPIO_AF_4 << (7 * 4));
	
	// Open Drain is mandatory for I2C communication
	GPIOB->OTYPER |= GPIO_OType_OD << 6;
	GPIOB->OTYPER |= GPIO_OType_OD << 7;

	// Medium Speed ( < 10 Mhz) is enought for our I2C clock at 8 Mhz
	GPIOB->OSPEEDR |= GPIO_Speed_Level_2 << 6 * 2;
	GPIOB->OSPEEDR |= GPIO_Speed_Level_2 << 7 * 2;

	// NO PULL for I2C
	GPIOB->PUPDR |= GPIO_PuPd_NOPULL << 6 * 2;
	GPIOB->PUPDR |= GPIO_PuPd_NOPULL << 7 * 2;

	I2C_Init();
}


uint8_t  READ_REGISTER(uint16_t DeviceAddr, uint16_t RegisterAddr)
{
	uint8_t data;
	uint32_t timeout = I2C_TIMEOUT;

	// Check if line is used by another master, but usefull for debug purpose
	while ((I2C1->ISR & I2C_ISR_BUSY) != 0)
	{
		if((timeout--) == 0)
		{
			_write(0, "ERROR ISRBUSY\n", 14);
			return (0);
		}
	}

	/*************************************************************************/
	/*  							Frame 1			 						 */
	/*************************************************************************/
	// Reinit CR2
	// Send device addr (Accelerometer or Magnetometer)
	// 1 byte len
	// Software en mode wait for me to set the stop bit
	// Ask for write (0x00)
	// Send the start signal
	I2C1->CR2 = (I2C1->CR2 & 0xF8000000U) \
				| ((uint32_t)(((uint32_t)DeviceAddr & I2C_CR2_SADD) \
				| (((uint32_t)1 << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES) \
				| (uint32_t)I2C_SOFTEND_MODE \
				| (uint32_t)I2C_GENERATE_START_WRITE));

	// Wait for the transmission buffer to be ready (empty)
	timeout = I2C_TIMEOUT;
	while ((I2C1->ISR & I2C_ISR_TXIS) == 0)
	{
		if((timeout--) == 0)
		{
			_write(0, "ERROR ISRTXIS\n", 14);
			return (0);
		}
	}

	// Write the register address to want to read from
	I2C1->TXDR = ((uint8_t)((uint16_t)((RegisterAddr) & (uint16_t)(0x00FFU))));

	// Wait the transfer to complete
	timeout = I2C_TIMEOUT;
	while ((I2C1->ISR & I2C_ISR_TC) == 0)
	{
		if((timeout--) == 0)
		{
			_write(0, "ERROR ISRTC\n", 12);
			return (0);
		}
	}

	/*************************************************************************/
	/*  							Frame 2			 						 */
	/*************************************************************************/
	// Reinit CR2
	// Send device addr (Accelerometer or Magnetometer)
	// 1 byte len
	// Autoend modem hard send STOP after last byte read
	// Ask for read (0x01)
	// Send the start signal
	I2C1->CR2 = (I2C1->CR2 & 0xF8000000U) \
				| ((uint32_t)(((uint32_t)DeviceAddr & I2C_CR2_SADD) \
				| (((uint32_t)1 << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES) \
				|  (uint32_t)I2C_AUTOEND_MODE \
				| (uint32_t)I2C_GENERATE_START_READ));

	// Wait for the recetption buffer to be ready (empty)
	timeout = I2C_TIMEOUT;
	while ((I2C1->ISR & I2C_ISR_RXNE) == 0)
	{
		if((timeout--) == 0)
		{
			_write(0, "ERROR ISRRXNE\n", 14);
			return (0);
		}
	}
	// Read data from register
	data = (uint8_t)I2C1->RXDR;

	// Wait for stop condition from autoend 
	timeout = I2C_TIMEOUT;
	while ((I2C1->ISR & I2C_ISR_STOPF) == 0)
	{
		if((timeout--) == 0)
		{
			_write(0, "ERROR ISRSTOPF\n", 15);
			return (0);
		}
	}
	return data;
}

void  WRITE_REGISTER(uint16_t DeviceAddr, uint16_t RegisterAddr, uint8_t RegisterConfig)
{
	uint32_t timeout = I2C_TIMEOUT;

	// Check if line is used by another master, but usefull for debug purpose
	while ((I2C1->ISR & I2C_ISR_BUSY) != 0)
	{
		if((timeout--) == 0)
		{
			_write(0, "ERROR ISRBUSY\n", 14);
			return ;
		}
	}

	/*************************************************************************/
	/*  							Frame 1			 						 */
	/*************************************************************************/
	// Reinit CR2
	// Send device addr (Accelerometer or Magnetometer)
	// 1 byte len
	// Software en mode wait for me to set the stop bit
	// Ask for write (0x00)
	// Send the start signal
	I2C1->CR2 = (I2C1->CR2 & 0xF8000000U) | ((uint32_t)(((uint32_t)DeviceAddr & I2C_CR2_SADD) | (((uint32_t)1 << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES) | (uint32_t)I2C_RELOAD_MODE | (uint32_t)I2C_GENERATE_START_WRITE));

	// Wait for the transmission buffer to be ready (empty)
	timeout = I2C_TIMEOUT;
	while ((I2C1->ISR & I2C_ISR_TXIS) == 0)
	{
		if((timeout--) == 0)
		{
			_write(0, "ERROR ISRTXIS\n", 14);
			return ;
		}
	}

	// Write the register address to want to read from
	I2C1->TXDR = ((uint8_t)((uint16_t)((RegisterAddr) & (uint16_t)(0x00FFU))));

	// Wait the transfer to complete
	timeout = I2C_TIMEOUT;
	while ((I2C1->ISR & I2C_ISR_TCR) == 0)
	{
		if((timeout--) == 0)
		{
			_write(0, "ERROR ISRTC\n", 12);
			return ;
		}
	}

	/*************************************************************************/
	/*  							Frame 2			 						 */
	/*************************************************************************/
	// Reinit CR2
	// Send device addr (Accelerometer or Magnetometer)
	// 1 byte len
	// Software en mode wait for me to set the stop bit
	// Ask for write (0x00)
	// Send the start signal
	I2C1->CR2 = (I2C1->CR2 & 0xF8000000U) | ((uint32_t)(((uint32_t)DeviceAddr & I2C_CR2_SADD) | (((uint32_t)1 << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES) | (uint32_t)I2C_AUTOEND_MODE | (uint32_t)I2C_NO_STARTSTOP));

	// Wait for the transmission buffer to be ready (empty)
	timeout = I2C_TIMEOUT;
	while ((I2C1->ISR & I2C_ISR_TXIS) == 0)
	{
		if((timeout--) == 0)
		{
			_write(0, "ERROR ISRTXIS\n", 14);
			return ;
		}
	}
	// Write the register configuration to send
	I2C1->TXDR = RegisterConfig;

	// Wait for stop condition from autoend 
	timeout = I2C_TIMEOUT;
	while ((I2C1->ISR & I2C_ISR_STOPF) == 0)
	{
		if((timeout--) == 0)
		{
			_write(0, "ERROR ISRSTOPF\n", 15);
			return ;
		}
	}
}


void LSM303DLHC_GetData_Acc(uint8_t *pDataXYZ)
{
	pDataXYZ[0] = READ_REGISTER(ACC_I2C_ADDRESS, LSM303DLHC_OUT_X_L_A);
	pDataXYZ[1] = READ_REGISTER(ACC_I2C_ADDRESS, LSM303DLHC_OUT_X_H_A);
	pDataXYZ[2] = READ_REGISTER(ACC_I2C_ADDRESS, LSM303DLHC_OUT_Y_L_A);
	pDataXYZ[3] = READ_REGISTER(ACC_I2C_ADDRESS, LSM303DLHC_OUT_Y_H_A);
	pDataXYZ[4] = READ_REGISTER(ACC_I2C_ADDRESS, LSM303DLHC_OUT_Z_L_A);
	pDataXYZ[5] = READ_REGISTER(ACC_I2C_ADDRESS, LSM303DLHC_OUT_Z_H_A);
}

void LSM303DLHC_GetData_Mag(uint8_t *pDataXYZ)
{
	pDataXYZ[0] = READ_REGISTER(MAG_I2C_ADDRESS, LSM303DLHC_OUT_X_L_M);
	pDataXYZ[1] = READ_REGISTER(MAG_I2C_ADDRESS, LSM303DLHC_OUT_X_H_M);
	pDataXYZ[2] = READ_REGISTER(MAG_I2C_ADDRESS, LSM303DLHC_OUT_Y_L_M);
	pDataXYZ[3] = READ_REGISTER(MAG_I2C_ADDRESS, LSM303DLHC_OUT_Y_H_M);
	pDataXYZ[4] = READ_REGISTER(MAG_I2C_ADDRESS, LSM303DLHC_OUT_Z_L_M);
	pDataXYZ[5] = READ_REGISTER(MAG_I2C_ADDRESS, LSM303DLHC_OUT_Z_H_M);
}

void LSM303DLHC_Config(void)
{
	/*************************************************************************/
	/*							ACCELEROMETER								 */
	/*************************************************************************/
	// ACCELEROMETER ODR 100hz
	// Enable  x/y/x axes 
	WRITE_REGISTER(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG1_A, 0x57);

	// Continuous update
	// data LSB at lower address
	// Full Scale selection +-2g
	// hight resolution ENABLE (bit 3)
	// 4-wire interface
	WRITE_REGISTER(ACC_I2C_ADDRESS, LSM303DLHC_CTRL_REG4_A, 0x00 | (1 << 3));
	
	/*************************************************************************/
	/*							MAGNETOMETER								 */
	/*************************************************************************/
	// MAGNETOMETER ODR 220hz
	// Temperature sensor enable
	WRITE_REGISTER(MAG_I2C_ADDRESS, LSM303DLHC_CRA_REG_M, 0x9C);

	// Sensor input field range +-2.5
	WRITE_REGISTER(MAG_I2C_ADDRESS, LSM303DLHC_CRB_REG_M, 0x20);

	// Continuous conversion mode
	WRITE_REGISTER(MAG_I2C_ADDRESS, LSM303DLHC_MR_REG_M, 0x00);
}

void LSM303DLHC_GetData_MR(uint8_t *data, 
						   uint8_t device_addr, 
						   uint8_t register_addr_start)
{
	uint32_t timeout = I2C_TIMEOUT;


	// Set the auto-increment bit as expected by the device
	register_addr_start |= 0x80;

	// Check if line is used by another master, but usefull for debug purpose
	while ((I2C1->ISR & I2C_ISR_BUSY) != 0)
	{
		if((timeout--) == 0)
		{
			_write(0, "ERROR ISRBUSY\n", 14);
			return ;
		}
	}

	/*************************************************************************/
	/*  							Frame 1			 						 */
	/*************************************************************************/
	// Reinit CR2
	// Send device addr (Accelerometer or Magnetometer)
	// 1 byte len
	// Software en mode wait for me to set the stop bit
	// Ask for write (0x00)
	// Send the start signal
	I2C1->CR2 = (I2C1->CR2 & 0xF8000000U) \
				| ((uint32_t)(((uint32_t)device_addr & I2C_CR2_SADD) \
				| (((uint32_t)1 << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES) \
				| (uint32_t)I2C_SOFTEND_MODE \
				| (uint32_t)I2C_GENERATE_START_WRITE));

	// Wait for the transmission buffer to be ready (empty)
	timeout = I2C_TIMEOUT;
	while ((I2C1->ISR & I2C_ISR_TXIS) == 0)
	{
		if((timeout--) == 0)
		{
			_write(0, "ERROR ISRTXIS\n", 14);
			return ;
		}
	}

	// Write the register address to want to read from
	I2C1->TXDR = ((uint8_t)((uint16_t)((register_addr_start) & (uint16_t)(0x00FFU))));

	// Wait the transfer to complete
	timeout = I2C_TIMEOUT;
	while ((I2C1->ISR & I2C_ISR_TC) == 0)
	{
		if((timeout--) == 0)
		{
			_write(0, "ERROR ISRTC\n", 12);
			return ;
		}
	}

	/*************************************************************************/
	/*  							Frame 2			 						 */
	/*************************************************************************/
	// Reinit CR2
	// Send register addr with the auto 0increment byte set
	// 6 byte len
	// Autoend modem hard send STOP after last byte read
	// Ask for read (0x01)
	// Send the start signal
	I2C1->CR2 = (I2C1->CR2 & 0xF8000000U) \
				| ((uint32_t)(((uint32_t)device_addr & I2C_CR2_SADD) \
				| (((uint32_t)6 << I2C_CR2_NBYTES_Pos) & I2C_CR2_NBYTES) \
				|  (uint32_t)I2C_AUTOEND_MODE \
				| (uint32_t)I2C_GENERATE_START_READ));

	int a = 0;
	while (a < 6)
	{
		// Wait for the recetption buffer to be ready (empty)
		timeout = I2C_TIMEOUT;
		while ((I2C1->ISR & I2C_ISR_RXNE) == 0)
		{
			if((timeout--) == 0)
			{
				_write(0, "ERROR ISRRXNE\n", 14);
				return ;
			}
		}
		// Read data from register
		data[a] = (uint8_t)I2C1->RXDR;
		a++;
	}

	// Wait for stop condition from autoend 
	timeout = I2C_TIMEOUT;
	while ((I2C1->ISR & I2C_ISR_STOPF) == 0)
	{
		if((timeout--) == 0)
		{
			_write(0, "ERROR ISRSTOPF\n", 15);
			return ;
		}
	}
}
