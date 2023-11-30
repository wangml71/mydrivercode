#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/mm.h>
#include <linux/input.h>
#include <linux/jiffies.h>
#include <linux/i2c.h>
#include <linux/cdev.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <asm/uaccess.h>
#include <asm/io.h>

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

struct mpu6050_driver_dev{
	struct input_dev *pinput;
	struct i2c_client *pclt;
	struct delayed_work work;
};

struct mpu6050_driver_dev *pgmydev;

int mpu6050_read_byte(struct i2c_client *pclt, unsigned char reg)
{
	int ret = 0;
	char txbuf[1] = {reg};
	char rxbuf[1] = {0};
	struct i2c_msg msg[2] = {
		{pclt->addr, 0, 1, txbuf},
		{pclt->addr, I2C_M_RD, 1, rxbuf},
	};
	ret = i2c_transfer(pclt->adapter, msg, ARRAY_SIZE(msg));
	if(ret < 0)
	{
		printk("i2c_transfer error\n");
		return ret;
	}
	return rxbuf[0];
}

int mpu6050_write_byte(struct i2c_client *pclt, unsigned char reg, unsigned char val)
{
	int ret = 0;
	char txbuf[2] = {reg, val};
	struct i2c_msg msg[1] = {
		{pclt->addr, 0, 2, txbuf},
	};
	ret = i2c_transfer(pclt->adapter, msg, ARRAY_SIZE(msg));
	if(ret < 0)
	{
		printk("i2c_transfer error\n");
		return ret;
	}
	return 0;
}

void mpu6050_work_func(struct work_struct *pwk)
{
	struct mpu6050_driver_dev *pmydev = container_of((struct delayed_work*)pwk, struct mpu6050_driver_dev, work);
	unsigned short ax = 0;
	unsigned short ay = 0;
	unsigned short az = 0;
	unsigned short gx = 0;
	unsigned short gy = 0;
	unsigned short gz = 0;
	unsigned short temp = 0;
	
	ax = mpu6050_read_byte(pmydev->pclt, ACCEL_XOUT_L);
	ax |= mpu6050_read_byte(pmydev->pclt, ACCEL_XOUT_H)<<8;
	input_report_abs(pmydev->pinput, ABS_X, ax);
	ay = mpu6050_read_byte(pmydev->pclt, ACCEL_YOUT_L);
	ay |= mpu6050_read_byte(pmydev->pclt, ACCEL_YOUT_H)<<8;
	input_report_abs(pmydev->pinput, ABS_Y, ay);
	az = mpu6050_read_byte(pmydev->pclt, ACCEL_ZOUT_L);
	az |= mpu6050_read_byte(pmydev->pclt, ACCEL_ZOUT_H)<<8;
	input_report_abs(pmydev->pinput, ABS_Z, az);

	gx = mpu6050_read_byte(pmydev->pclt, GYRO_XOUT_L);
	gx |= mpu6050_read_byte(pmydev->pclt, GYRO_XOUT_H)<<8;
	input_report_abs(pmydev->pinput, ABS_RX, gx);
	gy = mpu6050_read_byte(pmydev->pclt, GYRO_YOUT_L);
	gy |= mpu6050_read_byte(pmydev->pclt, GYRO_YOUT_H)<<8;
	input_report_abs(pmydev->pinput, ABS_RY, gy);
	gz = mpu6050_read_byte(pmydev->pclt, GYRO_ZOUT_L);
	gz |= mpu6050_read_byte(pmydev->pclt, GYRO_ZOUT_H)<<8;
	input_report_abs(pmydev->pinput, ABS_RZ, gz);

	temp = mpu6050_read_byte(pmydev->pclt, TEMP_OUT_L);
	temp |= mpu6050_read_byte(pmydev->pclt, TEMP_OUT_H)<<8;
	input_report_abs(pmydev->pinput, ABS_MISC, temp);

	input_sync(pmydev->pinput);

	schedule_delayed_work(&pmydev->work, msecs_to_jiffies(1000));
}

void mpu6050_init(struct i2c_client *pclt)
{
	mpu6050_write_byte(pclt, PWR_MGMT_1, 0x00);
	mpu6050_write_byte(pclt, SMPLRT_DIV, 0x07);
	mpu6050_write_byte(pclt, CONFIG, 0x06);
	mpu6050_write_byte(pclt, GYRO_CONFIG, 0xF8);
	mpu6050_write_byte(pclt, ACCEL_CONFIG, 0x19);

	printk("mpu6050_init finished\n");
}

int mpu6050_driver_probe(struct i2c_client *pclt, const struct i2c_device_id *pid)
{
	int ret = 0;

	pgmydev = kmalloc(sizeof(struct mpu6050_driver_dev), GFP_KERNEL);
	if(!pgmydev)
	{
		printk("kmalloc failed\n");
		return -1;
	}
	memset(pgmydev, 0, sizeof(struct mpu6050_driver_dev));
	
	pgmydev->pclt = pclt;
	
	mpu6050_init(pgmydev->pclt);

	pgmydev->pinput = input_allocate_device();
	set_bit(EV_ABS, pgmydev->pinput->evbit);
	input_set_abs_params(pgmydev->pinput, ABS_X, -32768, 32767, 0, 0);
	input_set_abs_params(pgmydev->pinput, ABS_Y, -32768, 32767, 0, 0);
	input_set_abs_params(pgmydev->pinput, ABS_Z, -32768, 32767, 0, 0);
	input_set_abs_params(pgmydev->pinput, ABS_RX, -32768, 32767, 0, 0);
	input_set_abs_params(pgmydev->pinput, ABS_RY, -32768, 32767, 0, 0);
	input_set_abs_params(pgmydev->pinput, ABS_RZ, -32768, 32767, 0, 0);
	input_set_abs_params(pgmydev->pinput, ABS_MISC, -32768, 32767, 0, 0);

	ret = input_register_device(pgmydev->pinput);
	if(ret)
	{
		printk("input_register_device failed\n");
		input_free_device(pgmydev->pinput);
		pgmydev->pinput = NULL;
		kfree(pgmydev);
		pgmydev = NULL;
		return -1;
	}

	INIT_DELAYED_WORK(&pgmydev->work, mpu6050_work_func);
	schedule_delayed_work(&pgmydev->work, msecs_to_jiffies(1000));

	return 0;
}

int mpu6050_driver_remove(struct i2c_client *pclt)
{
	cancel_delayed_work(&pgmydev->work);
	input_unregister_device(pgmydev->pinput);
	input_free_device(pgmydev->pinput);
	pgmydev->pinput = NULL;
	kfree(pgmydev);
	pgmydev = NULL;
	printk("mpu6050_driver_remove is called\n");
	return 0;
}

struct of_device_id mpu6050_dts[] = {
	{.compatible = "invensense,mpu6050"},
	{}
};

struct i2c_device_id mpu6050_ids[] = {
	[0] = {"mpu6050", 0},
	[1] = {},
};

struct i2c_driver mpu6050_driver = {
	.driver = {
		.name = "mpu6050",
		.owner = THIS_MODULE,
		.of_match_table = mpu6050_dts,
	},
	.probe = mpu6050_driver_probe,
	.remove = mpu6050_driver_remove,

	.id_table = mpu6050_ids,
};

#if 0
int __init mpu6050_driver_init(void)
{
	i2c_add_driver(&mpu6050_driver);
	return 0;
}
void __exit mpu6050_driver_exit(void)
{
	i2c_del_driver(&mpu6050_driver);
}
module_init(mpu6050_driver_init);
module_exit(mpu6050_driver_exit);
#else
module_i2c_driver(mpu6050_driver);
#endif


MODULE_LICENSE("GPL");
