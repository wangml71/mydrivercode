#include "mpu6050_driver.h"

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/i2c.h>
#include <linux/cdev.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <linux/platform_device.h>
#include <asm/uaccess.h>
#include <asm/io.h>

int major = 11;
int minor = 0;
int mpu6050_driver_num = 1;

struct mpu6050_driver_dev{
	struct cdev mydev;
	struct mutex mtx;
	struct i2c_client *pclt;
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

int mpu6050_driver_open(struct inode *pnode, struct file *pfile)
{
	pfile->private_data = (void*)container_of(pnode->i_cdev, struct mpu6050_driver_dev, mydev);	
	printk("mpu6050_driver_open is called!\n");
	return 0;

}

int mpu6050_driver_close(struct inode *pnode, struct file *pfile)
{
	//struct mpu6050_driver_dev *pmydev = (struct mpu6050_driver_dev*)pfile->private_data;
	printk("mpu6050_driver_close is called!\n");
	return 0;
}

long mpu6050_driver_ioctl(struct file *pfile, unsigned int cmd, unsigned long arg)
{
	struct mpu6050_driver_dev *pmydev = (struct mpu6050_driver_dev*)pfile->private_data;
	union mpu6050_data data;
	switch(cmd){
	case GET_ACCEL:
		data.accel.x = mpu6050_read_byte(pmydev->pclt, ACCEL_XOUT_L);
		data.accel.x |= mpu6050_read_byte(pmydev->pclt, ACCEL_XOUT_H)<<8;
		data.accel.y = mpu6050_read_byte(pmydev->pclt, ACCEL_YOUT_L);
		data.accel.y |= mpu6050_read_byte(pmydev->pclt, ACCEL_YOUT_H)<<8;
		data.accel.z = mpu6050_read_byte(pmydev->pclt, ACCEL_ZOUT_L);
		data.accel.z |= mpu6050_read_byte(pmydev->pclt, ACCEL_ZOUT_H)<<8;
		break;
	case GET_GYRO:
		data.gyro.x = mpu6050_read_byte(pmydev->pclt, GYRO_XOUT_L);
		data.gyro.x |= mpu6050_read_byte(pmydev->pclt, GYRO_XOUT_H)<<8;
		data.gyro.y = mpu6050_read_byte(pmydev->pclt, GYRO_YOUT_L);
		data.gyro.y |= mpu6050_read_byte(pmydev->pclt, GYRO_YOUT_H)<<8;
		data.gyro.z = mpu6050_read_byte(pmydev->pclt, GYRO_ZOUT_L);
		data.gyro.z |= mpu6050_read_byte(pmydev->pclt, GYRO_ZOUT_H)<<8;
		break;
	case GET_TEMP:
		data.temp = mpu6050_read_byte(pmydev->pclt, TEMP_OUT_L);
		data.temp |= mpu6050_read_byte(pmydev->pclt, TEMP_OUT_H)<<8;
		break;
	default:
		return -EINVAL;
	}

	if(copy_to_user((void*)arg, &data, sizeof(data)))
		return -EFAULT;

	return sizeof(data);
}

struct file_operations myops = {
	.owner = THIS_MODULE,
	.open = mpu6050_driver_open,
	.release = mpu6050_driver_close,
	.unlocked_ioctl = mpu6050_driver_ioctl,
};

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
	int i = 0;
	dev_t devno = MKDEV(major, minor);
	/*申请设备号*/
	ret = register_chrdev_region(devno, mpu6050_driver_num, "mpu6050_driver");
	if(ret)
	{
		ret = alloc_chrdev_region(&devno, minor, mpu6050_driver_num, "mpu6050_driver");
		if(ret)
		{
			printk("get devno failed!\n");
			return -1;
		}
		major = MAJOR(devno);
		minor = MINOR(devno);
	}
	printk("register succeed!(%d, %d)\n", major, minor);

	pgmydev = kmalloc(sizeof(struct mpu6050_driver_dev), GFP_KERNEL);
	if(!pgmydev)
	{
		unregister_chrdev_region(devno, mpu6050_driver_num);
		printk("kmalloc failed\n");
		return -1;
	}
	memset(pgmydev, 0, sizeof(struct mpu6050_driver_dev));
	
	pgmydev->pclt = pclt;
	
	/*将设备对象添加进内核对应的数据结构里*/
	devno = MKDEV(major, minor+i);
	cdev_init(&pgmydev->mydev, &myops); // 指定操作函数集
	pgmydev->mydev.owner = THIS_MODULE;
	cdev_add(&pgmydev->mydev, devno, 1);

	mutex_init(&pgmydev->mtx);
	mpu6050_init(pgmydev->pclt);

	return 0;
}

int mpu6050_driver_remove(struct i2c_client *pclt)
{
	dev_t devno = MKDEV(major, minor);
	cdev_del(&pgmydev->mydev); // 删除设备对象
	unregister_chrdev_region(devno, mpu6050_driver_num); // 注销设备号
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
