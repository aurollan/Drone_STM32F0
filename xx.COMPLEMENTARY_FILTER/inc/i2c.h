#ifndef __I2C_H__
#define __I2C_H__

#include "itm.h"
#include "timer.h"
#include "stm32f303xc.h"


typedef enum
{
  GPIO_PuPd_NOPULL = 0x00,
  GPIO_PuPd_UP     = 0x01,
  GPIO_PuPd_DOWN   = 0x02
}GPIOPuPd_TypeDef;

typedef enum
{
  GPIO_Speed_Level_1  = 0x01, /*!< Fast Speed     */
  GPIO_Speed_Level_2  = 0x02, /*!< Meduim Speed   */
  GPIO_Speed_Level_3  = 0x03  /*!< High Speed     */
}GPIOSpeed_TypeDef;

typedef enum
{
  GPIO_OType_PP = 0x00,
  GPIO_OType_OD = 0x01
}GPIOOType_TypeDef;

typedef enum
{
  GPIO_Mode_IN   = 0x00, /*!< GPIO Input Mode */
  GPIO_Mode_OUT  = 0x01, /*!< GPIO Output Mode */
  GPIO_Mode_AF   = 0x02, /*!< GPIO Alternate function Mode */
  GPIO_Mode_AN   = 0x03  /*!< GPIO Analog In/Out Mode      */
}GPIOMode_TypeDef;

#define ACC_I2C_ADDRESS                      0x32
#define LSM303DLHC_CTRL_REG1_A               0x20  /* Control register 1 acceleration */
#define LSM303DLHC_CTRL_REG2_A               0x21  /* Control register 2 acceleration */
#define LSM303DLHC_CTRL_REG3_A               0x22  /* Control register 3 acceleration */
#define LSM303DLHC_CTRL_REG4_A               0x23  /* Control register 4 acceleration */
#define LSM303DLHC_CTRL_REG5_A               0x24  /* Control register 5 acceleration */
#define LSM303DLHC_CTRL_REG6_A               0x25  /* Control register 6 acceleration */
#define LSM303DLHC_OUT_X_L_A                 0x28  /* Output Register X acceleration */
#define LSM303DLHC_OUT_X_H_A                 0x29  /* Output Register X acceleration */
#define LSM303DLHC_OUT_Y_L_A                 0x2A  /* Output Register Y acceleration */
#define LSM303DLHC_OUT_Y_H_A                 0x2B  /* Output Register Y acceleration */
#define LSM303DLHC_OUT_Z_L_A                 0x2C  /* Output Register Z acceleration */
#define LSM303DLHC_OUT_Z_H_A                 0x2D  /* Output Register Z acceleration */

#define MAG_I2C_ADDRESS                      0x3C
#define LSM303DLHC_CRA_REG_M	0x00
#define LSM303DLHC_CRB_REG_M	0x01
#define LSM303DLHC_MR_REG_M		0x02
#define LSM303DLHC_OUT_X_H_M                 0x03  /* Output Register X magnetic field */
#define LSM303DLHC_OUT_X_L_M                 0x04  /* Output Register X magnetic field */
#define LSM303DLHC_OUT_Z_H_M                 0x05  /* Output Register Z magnetic field */
#define LSM303DLHC_OUT_Z_L_M                 0x06  /* Output Register Z magnetic field */ 
#define LSM303DLHC_OUT_Y_H_M                 0x07  /* Output Register Y magnetic field */
#define LSM303DLHC_OUT_Y_L_M                 0x08  /* Output Register Y magnetic field */

#define  GPIO_SPEED_FREQ_HIGH     (0x00000003U)  /*!< range 10 MHz to 50 MHz, please refer to the product datasheet */
#define GPIO_AF_4            ((uint8_t)0x04) /* I2C1, I2C2, TIM1, TIM8, TIM16, TIM17 */
#define TIMING_CLEAR_MASK       ((uint32_t)0xF0FFFFFF)  /*<! I2C TIMING clear register Mask */
#define I2C_NOSTRETCH_DISABLE           (0x00000000U)
#define I2C_GENERALCALL_DISABLE         (0x00000000U)
#define ACCELERO_I2C_ADDRESS             0x32
#define I2C_DUALADDRESS_DISABLE         (0x00000000U)
#define I2C_DUALADDRESS_ENABLE          I2C_OAR2_OA2EN
#define ACCELERO_I2C_ADDRESS             0x32
#define I2C_TIMEOUT         ((uint32_t)0x3FFFF) /*!< I2C Time out */
#define  I2C_NO_STARTSTOP               (0x00000000U)
#define  I2C_GENERATE_STOP              (uint32_t)(0x80000000U | I2C_CR2_STOP)
#define  I2C_GENERATE_START_READ        (uint32_t)(0x80000000U | I2C_CR2_START | I2C_CR2_RD_WRN)
#define  I2C_GENERATE_START_WRITE       (uint32_t)(0x80000000U | I2C_CR2_START)
#define  I2C_RELOAD_MODE                I2C_CR2_RELOAD
#define  I2C_AUTOEND_MODE               I2C_CR2_AUTOEND
#define  I2C_SOFTEND_MODE               (0x00000000U)
#define I2C_CR2_NBYTES_Pos           (16U)
#define LSM303DLHC_BLE_LSB                 ((uint8_t)0x00) /*!< Little Endian: data LSB @ lower address */
#define LSM303DLHC_BLE_MSB                 ((uint8_t)0x40) /*!< Big Endian: data MSB @ lower address */
#define LSM303DLHC_FULLSCALE_2G            ((uint8_t)0x00)  /*!< ±2 g */
#define LSM303DLHC_FULLSCALE_4G            ((uint8_t)0x10)  /*!< ±4 g */
#define LSM303DLHC_FULLSCALE_8G            ((uint8_t)0x20)  /*!< ±8 g */
#define LSM303DLHC_FULLSCALE_16G           ((uint8_t)0x30)  /*!< ±16 g */
#define LSM303DLHC_ACC_SENSITIVITY_2G     ((uint8_t)1)  /*!< accelerometer sensitivity with 2 g full scale [mg/LSB] */
#define LSM303DLHC_ACC_SENSITIVITY_4G     ((uint8_t)2)  /*!< accelerometer sensitivity with 4 g full scale [mg/LSB] */
#define LSM303DLHC_ACC_SENSITIVITY_8G     ((uint8_t)4)  /*!< accelerometer sensitivity with 8 g full scale [mg/LSB] */
#define LSM303DLHC_ACC_SENSITIVITY_16G    ((uint8_t)12) /*!< accelerometer sensitivity with 12 g full scale [mg/LSB] */

/* Init I2C */
void  I2C_Init();
void ENABLE_GPIOB_SCA_SCL(void);

/* Configure peripheral */
void LSM303DLHC_Config(void);

/* Send and receive data */
uint8_t  READ_REGISTER(uint16_t DeviceAddr, uint16_t RegisterAddr);
void  WRITE_REGISTER(uint16_t DeviceAddr, uint16_t RegisterAddr, uint8_t RegisterConfig);

/* Fill array with data */
void LSM303DLHC_GetData_Mag(uint8_t *pDataXYZ);
void LSM303DLHC_GetData_Acc(uint8_t *pDataXYZ);
void LSM303DLHC_GetData_MR(uint8_t *tab, 
						   uint8_t device_addr, 
						   uint8_t register_addr_start);

typedef struct	s_pos_data
{
	int16_t x;
	int16_t y;
	int16_t z;
}				t_pos_data;

typedef struct	s_angle_data
{
	float x;
	float y;
	float z;
}				t_angle_data;

/* read data as expected */
void calibrate_acc(t_pos_data *offset);
void read_data_acc(uint8_t data[6], t_pos_data offset, t_pos_data *value);
void convert_to_angle_acc(t_pos_data value,
								t_angle_data *angle);
#endif
