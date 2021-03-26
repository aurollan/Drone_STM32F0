#pragma once
#include <stdint.h>

#define I2C_SLAVE_ADDR_AD0 0b01101000
#define I2C_SLAVE_ADDR_AD1 0b01101001

/**
 * @brief   Creating define to manipulate register in a readable way.
 *          Data direcly sourced from mpu-6050 register map and descriptions
 */
#define SELF_TEST_X             ((uint8_t)0x0D) /**< 013(decimal) R/W   XA_TEST[4-2] | XG_TEST[4-0]                                                                                                 */
#define SELF_TEST_Y             ((uint8_t)0x0E) /**< 014(decimal) R/W   YA_TEST[4-2] | YG_TEST[4-0]                                                                                                 */
#define SELF_TEST_Z             ((uint8_t)0x0F) /**< 015(decimal) R/W   ZA_TEST[4-2] | ZG_TEST[4-0]                                                                                                 */
#define SELF_TEST_A             ((uint8_t)0x10) /**< 016(decimal) R/W   RESERVED | XA_TEST[1-0] | YA_TEST[1-0] | ZA_TEST[1-0]                                                                       */
#define SMPLRT_DIV              ((uint8_t)0x19) /**< 025(decimal) R/W   SMPLRT_DIV[7:0]                                                                                                             */
#define CONFIG                  ((uint8_t)0x1A) /**< 026(decimal) R/W   - | - | EXT_SYNC_SET[2:0] | DLPF_CFG[2:0]                                                                                   */
#define GYRO_CONFIG             ((uint8_t)0x1B) /**< 027(decimal) R/W   - | - | - | FS_SEL[1:0] - | - | -                                                                                           */
#define ACCEL_CONFIG            ((uint8_t)0x1C) /**< 028(decimal) R/W   XA_ST | YA_ST | ZA_ST | AFS_SEL[1:0] | - | -                                                                                */
#define FIFO_EN                 ((uint8_t)0x23) /**< 035(decimal) R/W   TEMP_FIFO_EN | XG_FIFO_EN | YG_FIFO_EN | ZG_FIFO_EN | ACCEL_FIFO_EN | SLV2_FIFO_EN | SLV1_FIFO_ENS | SLV0_FIFO_EN           */
#define I2C_MST_CTRL            ((uint8_t)0x24) /**< 036(decimal) R/W   MULT_MST_EN | WAIT_FOR_ES | SLV_3_FIFO_EN | I2C_MST_P_NSR | I2C_MST_CLK[3:0]                                                */
#define I2C_SLV0_ADDR           ((uint8_t)0x25) /**< 037(decimal) R/W   I2C_SLV0_RW | I2C_SLV0_ADDR[6:0]                                                                                            */
#define I2C_SLV0_REG            ((uint8_t)0x26) /**< 038(decimal) R/W   I2C_SLV0_REG[7:0]                                                                                                           */
#define I2C_SLV0_CTRL           ((uint8_t)0x27) /**< 039(decimal) R/W   I2C_SLV0_EN | I2C_SLV0_BYTE_SW | I2C_SLV0_REG_DIS | I2C_SLV0_GRP | I2C_SLV0_LEN[3:0]                                        */
#define I2C_SLV1_ADDR           ((uint8_t)0x28) /**< 040(decimal) R/W   I2C_SLV1_RW | I2C_SLV1_ADDR[6:0]                                                                                            */
#define I2C_SLV1_REG            ((uint8_t)0x29) /**< 041(decimal) R/W   I2C_SLV1_REG[7:0]                                                                                                           */
#define I2C_SLV1_CTRL           ((uint8_t)0x2A) /**< 042(decimal) R/W   I2C_SLV1_EN | I2C_SLV1_BYTE_SW | I2C_SLV1_REG_DIS | I2C_SLV1_GRP | I2C_SLV1_LEN[3:0]                                        */
#define I2C_SLV2_ADDR           ((uint8_t)0x2B) /**< 043(decimal) R/W   I2C_SLV2_RW | I2C_SLV2_ADDR[6:0]                                                                                            */
#define I2C_SLV2_REG            ((uint8_t)0x2C) /**< 044(decimal) R/W   I2C_SLV2_REG[7:0]                                                                                                           */
#define I2C_SLV2_CTRL           ((uint8_t)0x2D) /**< 045(decimal) R/W   I2C_SLV2_EN | I2C_SLV2_BYTE_SW | I2C_SLV2_REG_DIS | I2C_SLV2_GRP | I2C_SLV2_LEN[3:0]                                        */
#define I2C_SLV3_ADDR           ((uint8_t)0x2E) /**< 046(decimal) R/W   I2C_SLV3 _RWI2C_SLV3_ADDR[6:0]                                                                                              */
#define I2C_SLV3_REG            ((uint8_t)0x2F) /**< 047(decimal) R/W   I2C_SLV3_REG[7:0]                                                                                                           */
#define I2C_SLV3_CTRL           ((uint8_t)0x30) /**< 048(decimal) R/W   I2C_SLV3_EN | I2C_SLV3_BYTE_SW | I2C_SLV3_REG_DIS | I2C_SLV3_GRP | I2C_SLV3_LEN[3:0]                                        */
#define I2C_SLV4_ADDR           ((uint8_t)0x31) /**< 049(decimal) R/W   I2C_SLV4_RW | I2C_SLV4_ADDR[6:0]                                                                                            */
#define I2C_SLV4_REG            ((uint8_t)0x32) /**< 050(decimal) R/W   I2C_SLV4_REG[7:0]                                                                                                           */
#define I2C_SLV4_DO             ((uint8_t)0x33) /**< 051(decimal) R/W   I2C_SLV4_DO[7:0]                                                                                                            */
#define I2C_SLV4_CTRL           ((uint8_t)0x34) /**< 052(decimal) R/W   I2C_SLV4_EN | I2C_SLV4_INT_EN | I2C_SLV4_REG_DIS | I2C_MST_DLY[4:0]                                                         */
#define I2C_SLV4_DI             ((uint8_t)0x35) /**< 053(decimal) R     I2C_SLV4_DI[7:0]                                                                                                            */
#define I2C_MST_STATUS          ((uint8_t)0x36) /**< 054(decimal) R     PASS_THROUGH | I2C_SLV4_DONE | I2C_LOST_ARB | I2C_SLV4_NACK | I2C_SLV3_NACK | I2C_SLV2_NACK | I2C_SLV1_NACK | I2C_SLV0_NACK */
#define INT_PIN_CFG             ((uint8_t)0x37) /**< 055(decimal) R/W   INT_LEVEL | INT_OPEN | LATCH_INT_EN | INT_RD_CLEAR | FSYNC_INT_LEVEL | FSYNC_INT_EN | I2C_BYPASS_EN | -                     */
#define INT_ENABLE              ((uint8_t)0x38) /**< 056(decimal) R/W   - | - | - | FIFO_OFLOW_EN | I2C_MST_INT_EN | - | - | DATA_RDY_EN                                                            */
#define INT_STATUS              ((uint8_t)0x3A) /**< 058(decimal) R     - | - | - | FIFO_OFLOW_INT | I2C_MST_INT | - | - | DATA_RDY_IN                                                              */

#define ACCEL_XOUT_H            ((uint8_t)0x3B) /**< 059(decimal) R     ACCEL_XOUT[15:8]                                                                                                            */
#define ACCEL_XOUT_L            ((uint8_t)0x3C) /**< 060(decimal) R     ACCEL_XOUT[7:0]                                                                                                             */
#define ACCEL_YOUT_H            ((uint8_t)0x3D) /**< 061(decimal) R     ACCEL_YOUT[15:8]                                                                                                            */
#define ACCEL_YOUT_L            ((uint8_t)0x3E) /**< 062(decimal) R     ACCEL_YOUT[7:0]                                                                                                             */
#define ACCEL_ZOUT_H            ((uint8_t)0x3F) /**< 063(decimal) R     ACCEL_ZOUT[15:8]                                                                                                            */
#define ACCEL_ZOUT_L            ((uint8_t)0x40) /**< 064(decimal) R     ACCEL_ZOUT[7:0]                                                                                                             */
#define TEMP_OUT_H              ((uint8_t)0x41) /**< 065(decimal) R     TEMP_OUT[15:8]                                                                                                              */
#define TEMP_OUT_L              ((uint8_t)0x42) /**< 066(decimal) R     TEMP_OUT[7:0]                                                                                                               */
#define GYRO_XOUT_H             ((uint8_t)0x43) /**< 067(decimal) R     GYRO_XOUT[15:8]                                                                                                             */
#define GYRO_XOUT_L             ((uint8_t)0x44) /**< 068(decimal) R     GYRO_XOUT[7:0]                                                                                                              */
#define GYRO_YOUT_H             ((uint8_t)0x45) /**< 069(decimal) R     GYRO_YOUT[15:8]                                                                                                             */
#define GYRO_YOUT_L             ((uint8_t)0x46) /**< 070(decimal) R     GYRO_YOUT[7:0]                                                                                                              */
#define GYRO_ZOUT_H             ((uint8_t)0x47) /**< 071(decimal) R     GYRO_ZOUT[15:8]                                                                                                             */
#define GYRO_ZOUT_L             ((uint8_t)0x48) /**< 072(decimal) R     GYRO_ZOUT[7:0]                                                                                                              */
#define EXT_SENS_DATA_00        ((uint8_t)0x49) /**< 073(decimal) R     EXT_SENS_DATA_00[7:0]                                                                                                       */
#define EXT_SENS_DATA_01        ((uint8_t)0x4A) /**< 074(decimal) R     EXT_SENS_DATA_01[7:0]                                                                                                       */
#define EXT_SENS_DATA_02        ((uint8_t)0x4B) /**< 075(decimal) R     EXT_SENS_DATA_02[7:0]                                                                                                       */
#define EXT_SENS_DATA_03        ((uint8_t)0x4C) /**< 076(decimal) R     EXT_SENS_DATA_03[7:0]                                                                                                       */
#define EXT_SENS_DATA_04        ((uint8_t)0x4D) /**< 077(decimal) R     EXT_SENS_DATA_04[7:0]                                                                                                       */
#define EXT_SENS_DATA_05        ((uint8_t)0x4E) /**< 078(decimal) R     EXT_SENS_DATA_05[7:0]                                                                                                       */
#define EXT_SENS_DATA_06        ((uint8_t)0x4F) /**< 079(decimal) R     EXT_SENS_DATA_06[7:0]                                                                                                       */
#define EXT_SENS_DATA_07        ((uint8_t)0x50) /**< 080(decimal) R     EXT_SENS_DATA_07[7:0]                                                                                                       */
#define EXT_SENS_DATA_08        ((uint8_t)0x51) /**< 081(decimal) R     EXT_SENS_DATA_08[7:0]                                                                                                       */
#define EXT_SENS_DATA_09        ((uint8_t)0x52) /**< 082(decimal) R     EXT_SENS_DATA_09[7:0]                                                                                                       */
#define EXT_SENS_DATA_10        ((uint8_t)0x53) /**< 083(decimal) R     EXT_SENS_DATA_10[7:0]                                                                                                       */
#define EXT_SENS_DATA_11        ((uint8_t)0x54) /**< 084(decimal) R     EXT_SENS_DATA_11[7:0]                                                                                                       */
#define EXT_SENS_DATA_12        ((uint8_t)0x55) /**< 085(decimal) R     EXT_SENS_DATA_12[7:0]                                                                                                       */
#define EXT_SENS_DATA_13        ((uint8_t)0x56) /**< 086(decimal) R     EXT_SENS_DATA_13[7:0]                                                                                                       */
#define EXT_SENS_DATA_14        ((uint8_t)0x57) /**< 087(decimal) R     EXT_SENS_DATA_14[7:0]                                                                                                       */
#define EXT_SENS_DATA_15        ((uint8_t)0x58) /**< 088(decimal) R     EXT_SENS_DATA_15[7:0]                                                                                                       */
#define EXT_SENS_DATA_16        ((uint8_t)0x59) /**< 089(decimal) R     EXT_SENS_DATA_16[7:0]                                                                                                       */
#define EXT_SENS_DATA_17        ((uint8_t)0x5A) /**< 090(decimal) R     EXT_SENS_DATA_17[7:0]                                                                                                       */
#define EXT_SENS_DATA_18        ((uint8_t)0x5B) /**< 091(decimal) R     EXT_SENS_DATA_18[7:0]                                                                                                       */
#define EXT_SENS_DATA_19        ((uint8_t)0x5C) /**< 092(decimal) R     EXT_SENS_DATA_19[7:0]                                                                                                       */
#define EXT_SENS_DATA_20        ((uint8_t)0x5D) /**< 093(decimal) R     EXT_SENS_DATA_20[7:0]                                                                                                       */
#define EXT_SENS_DATA_21        ((uint8_t)0x5E) /**< 094(decimal) R     EXT_SENS_DATA_21[7:0]                                                                                                       */
#define EXT_SENS_DATA_22        ((uint8_t)0x5F) /**< 095(decimal) R     EXT_SENS_DATA_22[7:0]                                                                                                       */
#define EXT_SENS_DATA_23        ((uint8_t)0x60) /**< 096(decimal) R     EXT_SENS_DATA_23[7:0]                                                                                                       */
#define I2C_SLV0_DO             ((uint8_t)0x63) /**< 099(decimal) R/W   I2C_SLV0_DO[7:0]                                                                                                            */
#define I2C_SLV1_DO             ((uint8_t)0x64) /**< 100(decimal) R/W   I2C_SLV1_DO[7:0]                                                                                                            */
#define I2C_SLV2_DO             ((uint8_t)0x65) /**< 101(decimal) R/W   I2C_SLV2_DO[7:0]                                                                                                            */
#define I2C_SLV3_DO             ((uint8_t)0x66) /**< 102(decimal) R/W   I2C_SLV3_DO[7:0                                                                                                             */

#define I2C_MST_DELAY_CTRL      ((uint8_t)0x67) /**< 103(decimal) R/W   DELAY_ES_SHADOW | - | - | I2C_SLV4_DLY_EN | I2C_SLV3_DLY_EN | I2C_SLV2_DLY_EN | I2C_SLV1_DLY_EN | I2C_SLV0_DLY_EN           */
#define SIGNAL_PATH_RESET       ((uint8_t)0x68) /**< 104(decimal) R/W   GYRO_RESET | ACCEL_RESET | TEMP_RESET                                                                                       */
#define USER_CTRL               ((uint8_t)0x6A) /**< 106(decimal) R/W   FIFO_EN | I2C_MST_EN | I2C_IF_DIS | - | FIFO_RESET | I2C_MST_RESET | SIG_COND_RESET                                         */
#define PWR_MGMT_1              ((uint8_t)0x6B) /**< 107(decimal) R/W   DEVICE_RESET | SLEEPCYCLE | - | TEMP_DIS | CLKSEL[2:0]                                                                      */
#define PWR_MGMT_2              ((uint8_t)0x6C) /**< 108(decimal) R/W   LP_WAKE_CTRL[1:0] | STBY_XA | STBY_YA | STBY_ZA | STBY_XG | STBY_YG | STBY_ZG                                               */
#define FIFO_COUNTH             ((uint8_t)0x72) /**< 114(decimal) R/W   FIFO_COUNT[15:8]                                                                                                            */
#define FIFO_COUNTL             ((uint8_t)0x73) /**< 115(decimal) R/W   FIFO_COUNT[7:0]                                                                                                             */
#define FIFO_R_W                ((uint8_t)0x74) /**< 116(decimal) R/W   FIFO_DATA[7:0]                                                                                                              */
#define WHO_AM_I                ((uint8_t)0x75) /**< 117(decimal) R     - | WHO_AM_I[6:1] | -                                                                                                       */

