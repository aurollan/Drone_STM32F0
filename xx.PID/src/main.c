/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   main.c                                           .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: aurollan <aurollan@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2020/01/22 11:11:06 by aurollan     #+#   ##    ##    #+#       */
/*   Updated: 2020/03/13 14:38:48 by aurollan    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "i2c.h"
#include "itm.h"
#include "timer.h"
#include "stdio.h"

void			ft_print_hexa(uint8_t data)
{
	char	hex_char;

	if (((data & 0b11110000) >> 4) > 9)
		hex_char = ((data & 0b11110000) >> 4) + 55;
	else
		hex_char = ((data & 0b11110000) >> 4) + 48;
	_write(0, &hex_char, 1);
	if ((data & 0b1111) > 9)
		hex_char = (data & 0b1111) + 55;
	else
		hex_char = (data & 0b1111) + 48;
	_write(0, &hex_char, 1);
}

void ft_print(uint8_t data[6])
{
		ft_print_hexa(data[1]);
		ft_print_hexa(data[0]);
		_write(0, "\n", 1);
		ft_print_hexa(data[3]);
		ft_print_hexa(data[2]);
		_write(0, "\n", 1);
		ft_print_hexa(data[5]);
		ft_print_hexa(data[4]);
		_write(0, "\n", 1);
}

int main(void)
{
	uint8_t data[6];
	t_pos_data value;
	t_pos_data offset;
	t_angle_data angle;

	angle.x = 0.0f;
	angle.y = 0.0f;
	angle.z = 0.0f;
	offset.x = 0.0f;
	offset.y = 0.0f;
	offset.z = 0.0f;

	// Debug
	ITM_init();
	TIM6_enable();

	// I2C project
	I2C_Init();
	ENABLE_GPIOB_SCA_SCL();
	LSM303DLHC_Config();

	// calibrate_acc(&offset);
	while (1)
	{
		LSM303DLHC_GetData_Acc(data);
		// LSM303DLHC_GetData_MR(data,
		// 					  ACC_I2C_ADDRESS, 
		// 				   	  LSM303DLHC_OUT_X_L_A);
		ft_print(data);
		// read data
		read_data_acc(data, offset, &value);
		convert_to_angle_acc(value, &angle);
		delay(10000);
		(void)angle;
	}
	return (0);
}

