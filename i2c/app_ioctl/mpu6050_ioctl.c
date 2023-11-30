#include "mpu6050.h"

static int read_data_from_mpu6050(int fd, unsigned char slave, unsigned char reg, unsigned char *pdata)
{
	struct i2c_rdwr_ioctl_data work = {NULL};
	struct i2c_msg msgs[2] = {{0}};
	unsigned char buf1[1] = {reg};
	unsigned char buf2[1] = {0};
	int ret = 0;

	work.msgs = msgs;
	work.nmsgs = 2;

	msgs[0].addr = slave;
	msgs[0].flags = 0;
	msgs[0].buf = buf1;
	msgs[0].len = 1;

	msgs[1].addr = slave;
	msgs[1].flags = I2C_M_RD;
	msgs[1].buf = buf2;
	msgs[1].len = 1;
	
	ret = ioctl(fd, I2C_RDWR, &work);
	if(ret < 0)
	{
		perror("ioctl");
		return -1;
	}

	*pdata = buf2[0];

	return 0;
}


static int write_data_to_mpu6050(int fd, unsigned char slave, unsigned char reg, unsigned char data)
{
	int ret = 0;
	unsigned char buf[2] = {reg, data};
	struct i2c_rdwr_ioctl_data work = {NULL};
	struct i2c_msg msg = {0};

	work.msgs = &msg;
	work.nmsgs = 1;

	msg.addr = slave;
	msg.flags = 0;
	msg.buf = buf;
	msg.len = 2;

	ret = ioctl(fd, I2C_RDWR, &work);
	if(ret < 0)
	{
		perror("ioctl");
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
	ret = ioctl(fd, I2C_SLAVE, SLAVE_ADDR);
	if(ret < 0)
	{
		perror("ioctl");
		return -1;
	}

	ret = write_data_to_mpu6050(fd, SLAVE_ADDR, PWR_MGMT_1, 0x00);
	ret += write_data_to_mpu6050(fd, SLAVE_ADDR, SMPLRT_DIV, 0x07);
	ret += write_data_to_mpu6050(fd, SLAVE_ADDR, ACCEL_CONFIG, 0x19);
	ret += write_data_to_mpu6050(fd, SLAVE_ADDR, GYRO_CONFIG, 0xF8);
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
	ret = read_data_from_mpu6050(fd, SLAVE_ADDR, ACCEL_XOUT_L, &dl);
	ret += read_data_from_mpu6050(fd, SLAVE_ADDR, ACCEL_XOUT_H, &dh);
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
	ret = read_data_from_mpu6050(fd, SLAVE_ADDR, ACCEL_YOUT_L, &dl);
	ret += read_data_from_mpu6050(fd, SLAVE_ADDR, ACCEL_YOUT_H, &dh);
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
	ret = read_data_from_mpu6050(fd, SLAVE_ADDR, ACCEL_ZOUT_L, &dl);
	ret += read_data_from_mpu6050(fd, SLAVE_ADDR, ACCEL_ZOUT_H, &dh);
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
	ret = read_data_from_mpu6050(fd, SLAVE_ADDR, TEMP_OUT_L, &dl);
	ret += read_data_from_mpu6050(fd, SLAVE_ADDR, TEMP_OUT_H, &dh);
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
	ret = read_data_from_mpu6050(fd, SLAVE_ADDR, GYRO_XOUT_L, &dl);
	ret += read_data_from_mpu6050(fd, SLAVE_ADDR, GYRO_XOUT_H, &dh);
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
	ret = read_data_from_mpu6050(fd, SLAVE_ADDR, GYRO_YOUT_L, &dl);
	ret += read_data_from_mpu6050(fd, SLAVE_ADDR, GYRO_YOUT_H, &dh);
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
	ret = read_data_from_mpu6050(fd, SLAVE_ADDR, GYRO_ZOUT_L, &dl);
	ret += read_data_from_mpu6050(fd, SLAVE_ADDR, GYRO_ZOUT_H, &dh);
	if(ret < 0)
	{
		perror("read_data_from_mpu6050");
		return -1;
	}
	val = (dh<<8) | dl;
	return val;
}

