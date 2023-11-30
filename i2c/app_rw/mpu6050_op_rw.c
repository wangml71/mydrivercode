#include "mpu6050.h"

static int read_data_from_mpu6050(int fd, unsigned char reg, unsigned char *pdata)
{
	int ret = 0;
	unsigned char buf[1] = {reg};

	ret = write(fd, buf, 1);
	if(ret != 1)
	{
		perror("write");
		return -1;
	}

	buf[0] = 0;
	ret = read(fd, buf, 1);
	if(ret != 1)
	{
		perror("read");
		return -1;
	}

	*pdata = buf[0];

	return 0;
}


static int write_data_to_mpu6050(int fd, unsigned char reg, unsigned char data)
{
	int ret = 0;
	unsigned char buf[2] = {reg, data};

	ret = write(fd, buf, 2);
	if(ret != 2)
	{
		perror("write");
		return -1;
	}

	return 0;
}

int init_mpu6050(int fd)
{
	int ret = 0;

	ret = ioctl(fd, I2C_TENBIT, 0);
	if(ret < 0)
	{
		perror("ioctl");
		return -1;
	}
	ret = ioctl(fd, I2C_SLAVE, 0x68);
	if(ret < 0)
	{
		perror("ioctl");
		return -1;
	}

	ret = write_data_to_mpu6050(fd, PWR_MGMT_1, 0x00);
	ret += write_data_to_mpu6050(fd, SMPLRT_DIV, 0x07);
	ret += write_data_to_mpu6050(fd, ACCEL_CONFIG, 0x19);
	ret += write_data_to_mpu6050(fd, GYRO_CONFIG, 0xF8);
	if(ret < 0)
	{
		perror("write_data_to_mpu6050");
		return -1;
	}

	return 0;
}

int read_accelx(int fd)
{
	unsigned short val = 0;
	unsigned char dl = 0, dh = 0;
	int ret = 0;
	ret = read_data_from_mpu6050(fd, ACCEL_XOUT_L, &dl);
	ret += read_data_from_mpu6050(fd, ACCEL_XOUT_H, &dh);
	if(ret < 0)
	{
		perror("read_data_from_mpu6050");
		return -1;
	}
	val = (dh<<8) | dl;
	return val;
}

int read_accely(int fd)
{
	unsigned short val = 0;
	unsigned char dl = 0, dh = 0;
	int ret = 0;
	ret = read_data_from_mpu6050(fd, ACCEL_YOUT_L, &dl);
	ret += read_data_from_mpu6050(fd, ACCEL_YOUT_H, &dh);
	if(ret < 0)
	{
		perror("read_data_from_mpu6050");
		return -1;
	}
	val = (dh<<8) | dl;
	return val;
}

int read_accelz(int fd)
{
	unsigned short val = 0;
	unsigned char dl = 0, dh = 0;
	int ret = 0;
	ret = read_data_from_mpu6050(fd, ACCEL_ZOUT_L, &dl);
	ret += read_data_from_mpu6050(fd, ACCEL_ZOUT_H, &dh);
	if(ret < 0)
	{
		perror("read_data_from_mpu6050");
		return -1;
	}
	val = (dh<<8) | dl;
	return val;
}

int read_temp(int fd)
{
	unsigned short val = 0;
	unsigned char dl = 0, dh = 0;
	int ret = 0;
	ret = read_data_from_mpu6050(fd, TEMP_OUT_L, &dl);
	ret += read_data_from_mpu6050(fd, TEMP_OUT_H, &dh);
	if(ret < 0)
	{
		perror("read_data_from_mpu6050");
		return -1;
	}
	val = (dh<<8) | dl;
	return val;
}

int read_gyrox(int fd)
{
	unsigned short val = 0;
	unsigned char dl = 0, dh = 0;
	int ret = 0;
	ret = read_data_from_mpu6050(fd, GYRO_XOUT_L, &dl);
	ret += read_data_from_mpu6050(fd, GYRO_XOUT_H, &dh);
	if(ret < 0)
	{
		perror("read_data_from_mpu6050");
		return -1;
	}
	val = (dh<<8) | dl;
	return val;
}

int read_gyroy(int fd)
{
	unsigned short val = 0;
	unsigned char dl = 0, dh = 0;
	int ret = 0;
	ret = read_data_from_mpu6050(fd, GYRO_YOUT_L, &dl);
	ret += read_data_from_mpu6050(fd, GYRO_YOUT_H, &dh);
	if(ret < 0)
	{
		perror("read_data_from_mpu6050");
		return -1;
	}
	val = (dh<<8) | dl;
	return val;
}

int read_gyroz(int fd)
{
	unsigned short val = 0;
	unsigned char dl = 0, dh = 0;
	int ret = 0;
	ret = read_data_from_mpu6050(fd, GYRO_ZOUT_L, &dl);
	ret += read_data_from_mpu6050(fd, GYRO_ZOUT_H, &dh);
	if(ret < 0)
	{
		perror("read_data_from_mpu6050");
		return -1;
	}
	val = (dh<<8) | dl;
	return val;
}

