#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/ioctl.h>
#include <unistd.h>
#include <fcntl.h>
#include "mpu6050_driver.h"

int main(int argc, const char *argv[])
{
	int fd = -1;
	union mpu6050_data data;
	if(argc < 1)
	{
		printf("The argument is not enough!\n");
		return 1;
	}

	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		printf("open %s failed\n", argv[1]);
		return 2;
	}

	while(1)
	{
		sleep(2);
		ioctl(fd, GET_ACCEL, &data);
		printf("ACCEL-x = 0x%x\n", data.accel.x);
		printf("ACCEL-y = 0x%x\n", data.accel.y);
		printf("ACCEL-z = 0x%x\n", data.accel.z);
		ioctl(fd, GET_GYRO, &data);
		printf("GYRO-x = 0x%x\n", data.gyro.x);
		printf("GYRO-y = 0x%x\n", data.gyro.y);
		printf("GYRO-z = 0x%x\n", data.gyro.z);
		ioctl(fd, GET_TEMP, &data);
		printf("TEMP = 0x%x\n\n", data.temp);
	}

	close(fd);
	fd = -1;
	
	return 0;
}
