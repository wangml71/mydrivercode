#include "dtledmychar.h"

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/mm.h>
#include <linux/mutex.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/device.h>
#include <asm/uaccess.h>

int major = 11;
int minor = 0;
int mychar_num = 1;

struct led_ctl{
};

struct mychar_dev{
	struct cdev mydev;
	struct mutex mtx;
	unsigned int led[4];

	struct class *pcls;
	struct device *pdev;
};

struct mychar_dev *pgmydev;

int mychar_open(struct inode *pnode, struct file *pfile)
{
	pfile->private_data = (void*)container_of(pnode->i_cdev, struct mychar_dev, mydev);	
	printk("mychar_open is called!\n");
	return 0;
}

int mychar_close(struct inode *pnode, struct file *pfile)
{
	//struct mychar_dev *pmydev = (struct mychar_dev*)pfile->private_data;
	printk("mychar_close is called!\n");
	return 0;
}

long mychar_ioctl(struct file *pfile, unsigned int cmd, unsigned long arg)
{
	int lednum = (int)arg - 2;
	struct mychar_dev *pmydev = (struct mychar_dev*)pfile->private_data;
	if(lednum<0 || lednum>=4)
	{
		printk("Led num is unknown\n");
		return -1;
	}
	switch(cmd) {
	case LED_IOCTL_ON:
		mutex_lock(&pmydev->mtx);
		gpio_set_value(pmydev->led[lednum], 1);
		mutex_unlock(&pmydev->mtx);
		break;
	case LED_IOCTL_OFF:
		mutex_lock(&pmydev->mtx);
		gpio_set_value(pmydev->led[lednum], 0);
		mutex_unlock(&pmydev->mtx);
		break;
	case LED_IOCTL_TOGGLE:
		mutex_lock(&pmydev->mtx);
		gpio_set_value(pmydev->led[lednum], !gpio_get_value(pmydev->led[lednum]));
		mutex_unlock(&pmydev->mtx);
		break;
	default:
		printk("The cmd is unknown\n");
		return -1;
	pmydev = (struct mychar_dev*)pfile->private_data;
	}
	return 0;
}

struct file_operations myops = {
	.owner = THIS_MODULE,
	.open = mychar_open,
	.release = mychar_close,
	.unlocked_ioctl = mychar_ioctl,
};

void led_init(struct mychar_dev *pmydev, struct device_node *pnode)
{
	int lednum = 0;

	pmydev->led[0] = of_get_named_gpio(pnode, "led2-gpio", 0);
	gpio_request(pmydev->led[0], "led2");
	pmydev->led[1] = of_get_named_gpio(pnode, "led3-gpio", 0);
	gpio_request(pmydev->led[1], "led3");
	pmydev->led[2] = of_get_named_gpio(pnode, "led4-gpio", 0);
	gpio_request(pmydev->led[2], "led4");
	pmydev->led[3] = of_get_named_gpio(pnode, "led5-gpio", 0);
	gpio_request(pmydev->led[3], "led5");

	for(lednum = 0; lednum < 4; lednum++)
	{
		gpio_direction_output(pmydev->led[lednum], 0);
	}
}

void led_free(struct mychar_dev *pmydev)
{
	int lednum = 0;
	for(lednum=0; lednum<4; lednum++)
	{
		gpio_free(pmydev->led[lednum]);
	}
}

int __init mychar_init(void)
{
	int ret = 0;
	int i = 0;
	struct device_node *pnode = NULL;
	dev_t devno = MKDEV(major, minor);
	/*申请设备号*/
	ret = register_chrdev_region(devno, mychar_num, "mychar");
	if(ret)
	{
		ret = alloc_chrdev_region(&devno, minor, mychar_num, "mychar");
		if(ret)
		{
			printk("get devno failed!\n");
			return -1;
		}
		major = MAJOR(devno);
		minor = MINOR(devno);
	}
	printk("register succeed!(%d, %d)\n", major, minor);

	pgmydev = kmalloc(sizeof(struct mychar_dev), GFP_KERNEL);
	/*将设备对象添加进内核对应的数据结构里*/
	devno = MKDEV(major, minor+i);
	cdev_init(&pgmydev->mydev, &myops); // 指定操作函数集
	pgmydev->mydev.owner = THIS_MODULE;
	cdev_add(&pgmydev->mydev, devno, 1);

	mutex_init(&pgmydev->mtx);

	pnode = of_find_node_by_path("/fs4412-leds");
	if(!pnode)
	{
		printk("find pnode failed\n");
		return -1;
	}
	led_init(pgmydev, pnode);

	pgmydev->pcls = class_create(pgmydev->mydev.owner, "myled");
	if(IS_ERR(pgmydev->pcls))
	{
		printk("class_create failed\n");
		cdev_del(&pgmydev->mydev);
		unregister_chrdev_region(devno, mychar_num);
		return -1;
	}
	pgmydev->pdev = device_create(pgmydev->pcls, NULL, devno, NULL, "ledmydev");
	if(!pgmydev->pdev)
	{
		printk("device_create failed\n");
		class_destroy(pgmydev->pcls);
		cdev_del(&pgmydev->mydev);
		unregister_chrdev_region(devno, mychar_num);
		return -1;
	}

	return 0;
}

void __exit mychar_exit(void)
{
	dev_t devno = MKDEV(major, minor);
	device_destroy(pgmydev->pcls, devno);
	class_destroy(pgmydev->pcls);
	led_free(pgmydev);
	cdev_del(&pgmydev->mydev); // 删除设备对象
	unregister_chrdev_region(devno, mychar_num); // 注销设备号
	kfree(pgmydev);
	pgmydev = NULL;
	printk("mychar will exit\n");
}


MODULE_LICENSE("GPL");

module_init(mychar_init);
module_exit(mychar_exit);
