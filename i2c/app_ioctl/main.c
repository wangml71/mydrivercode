#include "mpu6050.h"

int main(int argc, const char *argv[])
{
	int fd = -1;
	if(argc < 2)
	{
		printf("Argument is not enough\n");
		return 1;
	}

	//open
	fd = open(argv[1], O_RDWR);
	if(fd < 0)
	{
		perror("open");
		return 2;
	}

	//init mpu6050
	init_mpu6050(fd);
	
	while(1)
	{
		sleep(2);
		//read and print data from mpu6050
		printf("Accel-X:%d\n", read_accelx(fd));
		printf("Accel-Y:%d\n", read_accely(fd));
		printf("Accel-Z:%d\n", read_accelz(fd));
		printf("TEMP:%d\n", read_temp(fd));
		printf("Gyro-X:%d\n", read_gyrox(fd));
		printf("Gyro-Y:%d\n", read_gyroy(fd));
		printf("Gyro-Z:%d\n", read_gyroz(fd));
	}

	//close
	close(fd);
	fd = -1;

	return 0;
}
