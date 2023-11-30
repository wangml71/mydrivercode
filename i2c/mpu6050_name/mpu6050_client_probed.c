#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/i2c.h>

#define SLAVE_ADDR1 0x68
#define SLAVE_ADDR2 0x69


static unsigned short mpu6050_addr_list[] = {
	SLAVE_ADDR1,
	SLAVE_ADDR2,
	I2C_CLIENT_END,
};

static struct i2c_client *gpmpu6050_client = NULL;

static int __init mpu6050_client_init(void)
{
	struct i2c_adapter *padp = NULL;
	struct i2c_board_info mpu6050_info = {""};

	strcpy(mpu6050_info.type, "mpu6050");
	padp = i2c_get_adapter(5);
	gpmpu6050_client = i2c_new_probed_device(padp, &mpu6050_info, mpu6050_addr_list, NULL);
	i2c_put_adapter(padp);

	if(!gpmpu6050_client)
		return -ENODEV;
	
	return 0;
}

static void __exit mpu6050_client_exit(void)
{
	i2c_unregister_device(gpmpu6050_client);
}

module_init(mpu6050_client_init);
module_exit(mpu6050_client_exit);

MODULE_LICENSE("GPL");
