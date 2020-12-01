#include "i2c.h"
#include "stdio.h"
#include "math.h"


void calibrate_acc(t_pos_data *offset)
{
	int test_nb;
	uint8_t data[6] = {0};
	int sum_offset_x;
	int sum_offset_y;
	int sum_offset_z;
	int max_test_nb;
	t_pos_data value;

	test_nb = 0;
	max_test_nb = 1000;
	sum_offset_x = 0;
	sum_offset_y = 0;
	sum_offset_z = 0;
	while (test_nb < max_test_nb)
	{
		LSM303DLHC_GetData_MR(&data[0], 
							  ACC_I2C_ADDRESS, 
							  LSM303DLHC_OUT_X_L_A);

		value.x = ((int16_t)(data[0])) + ((int16_t)(data[1] << 8));
		value.y = ((int16_t)(data[2])) + ((int16_t)(data[3] << 8));
		value.z = ((int16_t)(data[4])) + ((int16_t)(data[5] << 8));

		sum_offset_x += value.x;
		sum_offset_y += value.y;
		sum_offset_z += value.z;
		
		test_nb++;
	}
	offset->x = sum_offset_x / max_test_nb;
	offset->y = sum_offset_y / max_test_nb;
	offset->z = (sum_offset_z / max_test_nb) - 1000;

	printf("offset->x = [%d]\n", offset->x);
	printf("offset->y = [%d]\n", offset->y);
	printf("offset->z = [%d]\n", offset->z);
}

void read_data_acc(uint8_t data[6], t_pos_data offset, t_pos_data *value)
{
	value->x = ((int16_t)(data[0])) | ((int16_t)(data[1] << 8));
	value->y = ((int16_t)(data[2])) | ((int16_t)(data[3] << 8));
	value->z = ((int16_t)(data[4])) | ((int16_t)(data[5] << 8));

	value->x -= offset.x;
	value->y -= offset.y;
	value->z -= offset.z;

	value->x >>= 4;
	value->y >>= 4;
	value->z >>= 4;

	printf("value->x = [%d]\n", value->x);
	printf("value->y = [%d]\n", value->y);
	printf("value->z = [%d]\n", value->z);
}

void convert_to_angle_acc(t_pos_data value,
								t_angle_data *angle)
{
	float pitch;
	float roll;
	float yaw;
	float total_vector;

	// 100 Hz
	// +-2g
	// 1 least significant bit =  1 mg
	// 0.004 g

	// Put f because default is double float
	angle->x = value.x * 0.001f;
	angle->y = value.y * 0.001f;
	angle->z = value.z * 0.001f; 

	printf("angle->x = [%f]\n", angle->x);
	printf("angle->y = [%f]\n", angle->y);
	printf("angle->z = [%f]\n", angle->z);

	total_vector = sqrt((angle->z * angle->z) \
				 + (angle->y * angle->y) \
				 + (angle->x * angle->x));
	pitch = atan2(angle->x, (sqrt((angle->z * angle->z) + (angle->y * angle->y)))) * 180 * M_PI;
	roll = atan2(angle->y, (sqrt((angle->z * angle->z) + (angle->x * angle->x)))) * 180 * M_PI;
	yaw = atan2(angle->z, (sqrt((angle->x * angle->x) + (angle->y * angle->y)))) * 180 * M_PI;

	pitch = asin(angle->x/total_vector) * 57.296f;
	roll = asin(angle->y/total_vector) * (-57.296f);
	// yaw = asin(angle->z) * 57.296f;

	printf("pitch->x = [%f]\n", pitch);
	printf("roll = [%f]\n", roll);
	printf("yaw = [%f]\n", yaw);
}
