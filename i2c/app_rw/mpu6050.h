#ifndef MPU_6050_H
#define MPU_6050_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ioctl.h>

int init_mpu6050(int fd);
int read_accelx(int fd);
int read_accely(int fd);
int read_accelz(int fd);
int read_temp(int fd);
int read_gyrox(int fd);
int read_gyroy(int fd);
int read_gyroz(int fd);

#define SMPLRT_DIV  0x19 //陀螺仪采样率，典型值：0x07(125Hz)
#define CONFIG   0x1A //低通滤波频率，典型值：0x06(5Hz)
#define GYRO_CONFIG  0x1B //陀螺仪自检及测量范围，典型值：0xF8(不自检，+/-2000deg/s)
#define ACCEL_CONFIG 0x1C //加速计自检、测量范围，典型值：0x19(不自检，+/-G)
#define ACCEL_XOUT_H 0x3B
#define ACCEL_XOUT_L 0x3C
#define ACCEL_YOUT_H 0x3D
#define ACCEL_YOUT_L 0x3E
#define ACCEL_ZOUT_H 0x3F
#define ACCEL_ZOUT_L 0x40
#define TEMP_OUT_H  0x41
#define TEMP_OUT_L  0x42
#define GYRO_XOUT_H  0x43
#define GYRO_XOUT_L  0x44
#define GYRO_YOUT_H  0x45
#define GYRO_YOUT_L  0x46
#define GYRO_ZOUT_H  0x47
#define GYRO_ZOUT_L  0x48
#define PWR_MGMT_1  0x6B //电源管理，典型值：0x00(正常启用)
#define I2C_SLAVE	0x0703	/* Use this slave address */
#define I2C_SLAVE_FORCE	0x0706	/* Use this slave address, even if it
				   is already in use by a driver! */
#define I2C_TENBIT	0x0704	/* 0 for 7 bit addrs, != 0 for 10 bit */

#define I2C_FUNCS	0x0705	/* Get the adapter functionality mask */

#define I2C_RDWR	0x0707	/* Combined R/W transfer (one STOP only) */

#define I2C_PEC		0x0708	/* != 0 to use PEC with SMBus */
#define I2C_SMBUS	0x0720	/* SMBus transfer */

#endif
