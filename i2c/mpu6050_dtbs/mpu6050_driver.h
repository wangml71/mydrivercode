#ifndef MPU6050_DRIVER_H
#define MPU6050_DRIVER_H

#include <asm/ioctl.h>

#define SLAVE_ADDR 0x68
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


struct accel_data{
	unsigned short x;
	unsigned short y;
	unsigned short z;
};
struct gyro_data{
	unsigned short x;
	unsigned short y;
	unsigned short z;
};
union mpu6050_data{
	struct accel_data accel;
	struct gyro_data gyro;
	unsigned short temp;
};

#define MPU6050_MAGIC 'k'

#define GET_ACCEL _IOR(MPU6050_MAGIC, 0, union mpu6050_data)
#define GET_GYRO _IOR(MPU6050_MAGIC, 1, union mpu6050_data)
#define GET_TEMP _IOR(MPU6050_MAGIC, 2, union mpu6050_data)


#endif
