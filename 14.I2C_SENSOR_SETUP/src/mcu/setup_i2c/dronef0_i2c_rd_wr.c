#include "dronef0_i2c.h"
#include "mcu/setup_usart/dronef0_uart.h"

/**
 * @brief   Wait i2c_flag to be set to flag_status 
 */
uint32_t i2c_wait_flag_status(I2C_TypeDef* I2Cx , uint32_t i2c_flag, FlagStatus flag_status, uint32_t retry)
{
    uint32_t status;

    status = 0;
    while ((flag_status != I2C_GetFlagStatus(I2Cx, i2c_flag)) && (retry))
    {
        retry--;
    }
    /**
     * I2C_FLAG_TIMEOUT is used for SMBus communication
     * Here we use the I2C_FLAG_TIMEOUT for convenience 
     * because in simple I2C communication (we just setup) 
     * we won't use this flag but if you are implementing a 
     * SMBus communication you SHOULD NOT use this flag like this
     */
    if (0 == retry)
    {
        status = I2C_FLAG_TIMEOUT;
    }
    return (status);
}

/**
 * @brief   Check if an i2c communication error occured
 */
uint32_t i2c_error_occur(I2C_TypeDef* I2Cx)
{
    uint32_t    i2c_isr_err_flags;

    i2c_isr_err_flags = 0;
    if (SET == I2C_GetFlagStatus(I2Cx, I2C_FLAG_BERR))
    {
        i2c_isr_err_flags |= I2C_FLAG_BERR;
    }
    if (SET == I2C_GetFlagStatus(I2Cx, I2C_FLAG_BUSY))
    {
        i2c_isr_err_flags |= I2C_FLAG_BUSY;
    }
    if (SET == I2C_GetFlagStatus(I2Cx, I2C_FLAG_ARLO))
    {
        i2c_isr_err_flags |= I2C_FLAG_ARLO;
    }
    if (SET == I2C_GetFlagStatus(I2Cx, I2C_FLAG_OVR))
    {
        i2c_isr_err_flags |= I2C_FLAG_OVR;
    }
    return (i2c_isr_err_flags);
}

/**
 * @brief   receive data from device and check if everything went right
 * @param   I2Cx   I2C_TypeDef*.   I2C channel selected
 * @return  i2c_isr_err_occured uint32_t. Contains only I2C ISR register error bits
 */
uint32_t I2C_receive_data_and_wait(I2C_TypeDef* I2Cx, uint8_t* received_data)
{
    uint32_t    i2c_isr_err_occured;

    i2c_isr_err_occured = 0;
    i2c_isr_err_occured |= i2c_wait_flag_status(I2Cx, I2C_FLAG_RXNE, SET, I2C_MAX_RETRY);
    if (!i2c_isr_err_occured)
    {
        *received_data = I2C_ReceiveData(I2Cx);
    }
    i2c_isr_err_occured |= i2c_error_occur(I2Cx);
    if (!i2c_isr_err_occured) 
    {
        i2c_isr_err_occured = i2c_wait_flag_status(I2Cx, I2C_FLAG_TC, SET, I2C_MAX_RETRY);
    }
    return (i2c_isr_err_occured);
}

/**
 * @brief   send data to device and check if everything went right
 * @param   I2Cx    I2C_TypeDef*.   I2C channel selected
 * @return  i2c_isr_err_occured uint32_t. Contains only I2C ISR register error bits
 */
uint32_t I2C_send_data_and_wait(I2C_TypeDef* I2Cx, uint8_t data_to_send)
{
    uint32_t    i2c_isr_err_occured;

    i2c_isr_err_occured = 0;
    i2c_isr_err_occured = i2c_wait_flag_status(I2Cx, I2C_FLAG_TXE, SET, I2C_MAX_RETRY);
    if (!i2c_isr_err_occured)
    {
        I2C_SendData(I2Cx, data_to_send);
    }
    i2c_isr_err_occured |= i2c_error_occur(I2Cx);
    if (!i2c_isr_err_occured) 
    {
        i2c_isr_err_occured = i2c_wait_flag_status(I2Cx, I2C_FLAG_TC, SET, I2C_MAX_RETRY);
    }
    return (i2c_isr_err_occured);
}

/**
 * @brief   Ask peripheral a read of number_of_bytes starting at register_to_read
 * @param   I2Cx                        I2C_TypeDef*.   I2C channel selected
 * @param   register_to_read            uint8_t.        Peripheral register to start to read from
 * @param   received_data               uint8_t*.       Memory to write data to
 * @param   number_of_bytes_to_read     uint8_t.        Number of bytes to read from peripheral
 * @return  i2c_isr_err_occured uint32_t. Contains only I2C ISR register error bits
 */
uint32_t i2c_read(I2C_TypeDef* I2Cx, uint16_t register_to_read, uint8_t *received_data, uint8_t number_of_bytes_to_read)
{
    uint32_t    index;
    uint32_t    i2c_isr_err_occured;

    index       = 0;
    i2c_isr_err_occured = 0;
    I2C_TransferHandling(I2Cx, register_to_read, 1, I2C_Generate_Start_Read, I2C_SoftEnd_Mode);
    i2c_isr_err_occured  = I2C_send_data_and_wait(I2Cx, register_to_read);
    if (i2c_isr_err_occured)
    {
        uart_send_data(USART1, (uint8_t*)"ERR ASK READ\n", 12);
        uart_send_data(USART2, (uint8_t*)"ERR ASK READ\n", 12);
    }
    if (!i2c_isr_err_occured)
    {
        I2C_TransferHandling(I2Cx, register_to_read, number_of_bytes_to_read, I2C_Generate_Start_Read, I2C_AutoEnd_Mode);
        while (index < number_of_bytes_to_read)
        {
            i2c_isr_err_occured = I2C_receive_data_and_wait(I2Cx, &(received_data[index]));
            if (i2c_isr_err_occured)
            {
                uart_send_data(USART1, (uint8_t*)"ERR ASK READ\n", 12);
                uart_send_data(USART2, (uint8_t*)"ERR ASK READ\n", 12);
                break;
            }
            index++;
        }
        if (!i2c_isr_err_occured)
        {
            i2c_isr_err_occured = i2c_wait_flag_status(I2Cx, I2C_FLAG_STOPF, SET, I2C_MAX_RETRY);
        }
    }
    return (i2c_isr_err_occured);
}

/**
 * @brief   Write the data_to_write value to the register_to_write 
 * @param   I2Cx              I2C_TypeDef*. I2C channel selected
 * @param   register_to_write uint8_t.      Peripheral register to write
 * @param   data_to_write     uint8_t.      Data to write to register
 * @return  i2c_isr_err_occured       uint32_t.     Contains only register error bits
 */
uint32_t i2c_write(I2C_TypeDef* I2Cx, uint8_t register_to_write, uint8_t data_to_write)
{
    uint32_t    i2c_isr_err_occured;
    uint32_t    number_of_bytes_to_read;
    uint32_t    number_of_bytes_to_write;

    i2c_isr_err_occured              = 0;
    number_of_bytes_to_read  = 1;
    number_of_bytes_to_write = 1;
    I2C_TransferHandling(I2Cx, register_to_write, number_of_bytes_to_read, I2C_Generate_Start_Read, I2C_SoftEnd_Mode);
    i2c_isr_err_occured = I2C_send_data_and_wait(I2Cx, register_to_write);
    if (!i2c_isr_err_occured)
    {
            I2C_TransferHandling(I2Cx, register_to_write, number_of_bytes_to_write, I2C_Generate_Start_Write, I2C_AutoEnd_Mode);
            i2c_isr_err_occured = I2C_send_data_and_wait(I2Cx, data_to_write);
            i2c_isr_err_occured |= i2c_wait_flag_status(I2Cx, I2C_FLAG_STOPF, SET, I2C_MAX_RETRY);
    }
    return (i2c_isr_err_occured);
}

