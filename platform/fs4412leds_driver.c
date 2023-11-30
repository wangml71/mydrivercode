#include "fs4412leds_driver.h"

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
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
int fs4412leds_driver_num = 1;

struct led_ctl{
	int offset;
	volatile unsigned long *con;
	volatile unsigned char *dat;
};

struct fs4412leds_driver_dev{
	struct cdev mydev;
	struct mutex mtx;
	struct led_ctl led[4];
};

struct fs4412leds_driver_dev *pgmydev;

int fs4412leds_driver_open(struct inode *pnode, struct file *pfile)
{
	pfile->private_data = (void*)container_of(pnode->i_cdev, struct fs4412leds_driver_dev, mydev);	
	printk("fs4412leds_driver_open is called!\n");
	return 0;
}

int fs4412leds_driver_close(struct inode *pnode, struct file *pfile)
{
	//struct fs4412leds_driver_dev *pmydev = (struct fs4412leds_driver_dev*)pfile->private_data;
	printk("fs4412leds_driver_close is called!\n");
	return 0;
}

long fs4412leds_driver_ioctl(struct file *pfile, unsigned int cmd, unsigned long arg)
{
	int lednum = (int)arg - 2;
	unsigned char tmpb = 0;
	struct fs4412leds_driver_dev *pmydev = (struct fs4412leds_driver_dev*)pfile->private_data;
	if(lednum<0 || lednum>=4)
	{
		printk("Led num is unknown\n");
		return -1;
	}
	switch(cmd) {
	case LED_IOCTL_ON:
		mutex_lock(&pmydev->mtx);
		tmpb = readb(pmydev->led[lednum].dat);
		writeb(tmpb | (0x1<<pmydev->led[lednum].offset), pmydev->led[lednum].dat);
		mutex_unlock(&pmydev->mtx);
		break;
	case LED_IOCTL_OFF:
		mutex_lock(&pmydev->mtx);
		tmpb = readb(pmydev->led[lednum].dat);
		writeb(tmpb & (~(0x1)<<pmydev->led[lednum].offset), pmydev->led[lednum].dat);
		mutex_unlock(&pmydev->mtx);
		break;
	case LED_IOCTL_TOGGLE:
		mutex_lock(&pmydev->mtx);
		tmpb = readb(pmydev->led[lednum].dat);
		writeb(tmpb ^ (0x1<<pmydev->led[lednum].offset), pmydev->led[lednum].dat);
		mutex_unlock(&pmydev->mtx);
		break;
	default:
		printk("The cmd is unknown\n");
		return -1;
	pmydev = (struct fs4412leds_driver_dev*)pfile->private_data;
	}
	return 0;
}

struct file_operations myops = {
	.owner = THIS_MODULE,
	.open = fs4412leds_driver_open,
	.release = fs4412leds_driver_close,
	.unlocked_ioctl = fs4412leds_driver_ioctl,
};

void led_init(struct fs4412leds_driver_dev *pgmydev, struct platform_device *p_pltdev)
{
	int lednum = 0;
	unsigned long tmpl = 0, tmpb = 0;
	struct resource *pres = NULL;

	pgmydev->led[0].offset = 7;
	pres = platform_get_resource(p_pltdev, IORESOURCE_MEM, 2);
	pgmydev->led[0].con = (unsigned long*)ioremap(pres->start, sizeof(unsigned int));
	pres = platform_get_resource(p_pltdev, IORESOURCE_MEM, 3);
	pgmydev->led[0].dat = (unsigned char*)ioremap(pres->start, sizeof(unsigned char));

	pgmydev->led[1].offset = 0;
	pres = platform_get_resource(p_pltdev, IORESOURCE_MEM, 0);
	pgmydev->led[1].con = (unsigned long*)ioremap(pres->start, sizeof(unsigned int));
	pres = platform_get_resource(p_pltdev, IORESOURCE_MEM, 1);
	pgmydev->led[1].dat = (unsigned char*)ioremap(pres->start, sizeof(unsigned char));

	pgmydev->led[2].offset = 4;
	pres = platform_get_resource(p_pltdev, IORESOURCE_MEM, 4);
	pgmydev->led[2].con = (unsigned long*)ioremap(pres->start, sizeof(unsigned int));
	pres = platform_get_resource(p_pltdev, IORESOURCE_MEM, 5);
	pgmydev->led[2].dat = (unsigned char*)ioremap(pres->start, sizeof(unsigned char));

	pgmydev->led[3].offset = 5;
	pres = platform_get_resource(p_pltdev, IORESOURCE_MEM, 4);
	pgmydev->led[3].con = (unsigned long*)ioremap(pres->start, sizeof(unsigned int));
	pres = platform_get_resource(p_pltdev, IORESOURCE_MEM, 5);
	pgmydev->led[3].dat = (unsigned char*)ioremap(pres->start, sizeof(unsigned char));

	for(lednum = 0; lednum < 4; lednum++)
	{
		tmpl = readl(pgmydev->led[lednum].con);
		writel((tmpl & ~((0xF)<<(pgmydev->led[lednum].offset*4))) | (0x1<<(pgmydev->led[lednum].offset*4)), pgmydev->led[lednum].con);
		tmpb = readb(pgmydev->led[lednum].dat);
		writeb(tmpb & (~(0x1)<<pgmydev->led[lednum].offset), pgmydev->led[lednum].dat);
	}

	printk("led_init finished\n");
}

int fs4412leds_driver_probe(struct platform_device *p_pltdev)
{
	int ret = 0;
	int i = 0;
	dev_t devno = MKDEV(major, minor);
	/*申请设备号*/
	ret = register_chrdev_region(devno, fs4412leds_driver_num, "fs4412leds_driver");
	if(ret)
	{
		ret = alloc_chrdev_region(&devno, minor, fs4412leds_driver_num, "fs4412leds_driver");
		if(ret)
		{
			printk("get devno failed!\n");
			return -1;
		}
		major = MAJOR(devno);
		minor = MINOR(devno);
	}
	printk("register succeed!(%d, %d)\n", major, minor);

	pgmydev = kmalloc(sizeof(struct fs4412leds_driver_dev), GFP_KERNEL);
	/*将设备对象添加进内核对应的数据结构里*/
	devno = MKDEV(major, minor+i);
	cdev_init(&pgmydev->mydev, &myops); // 指定操作函数集
	pgmydev->mydev.owner = THIS_MODULE;
	cdev_add(&pgmydev->mydev, devno, 1);

	mutex_init(&pgmydev->mtx);
	led_init(pgmydev, p_pltdev);

	return 0;
}

int fs4412leds_driver_remove(struct platform_device *p_pltdev)
{
	dev_t devno = MKDEV(major, minor);
	int lednum;
	for(lednum = 0; lednum < 4; lednum++)
	{
		iounmap(pgmydev->led[lednum].con);
		iounmap(pgmydev->led[lednum].dat);
	}
	cdev_del(&pgmydev->mydev); // 删除设备对象
	unregister_chrdev_region(devno, fs4412leds_driver_num); // 注销设备号
	kfree(pgmydev);
	pgmydev = NULL;
	printk("fs4412leds_driver_remove is called\n");
	return 0;
}

struct platform_device_id hellodrv_ids[] = {
	[0] = {.name = "fs4412leds"},
	[1] = {.name = "hello"},
	[2] = {},
};

struct platform_driver fs4412leds_driver = {
	.driver.name = "fs4412led",
	.probe = fs4412leds_driver_probe,
	.remove = fs4412leds_driver_remove,

	.id_table = hellodrv_ids,
};

int __init fs4412leds_driver_init(void)
{
	platform_driver_register(&fs4412leds_driver);
	return 0;
}
void __exit fs4412leds_driver_exit(void)
{
	platform_driver_unregister(&fs4412leds_driver);
	printk("fs4412leds_driver will exit\n");
}

MODULE_LICENSE("GPL");

module_init(fs4412leds_driver_init);
module_exit(fs4412leds_driver_exit);
