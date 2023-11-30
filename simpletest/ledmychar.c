#include "ledmychar.h"

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/mutex.h>
#include <linux/slab.h>
#include <asm/uaccess.h>
#include <asm/io.h>

int major = 11;
int minor = 0;
int mychar_num = 1;

struct led_ctl{
	int offset;
	volatile unsigned long *con;
	volatile unsigned char *dat;
};

struct mychar_dev{
	struct cdev mydev;
	struct mutex mtx;
	struct led_ctl led[4];
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
	unsigned char tmpb = 0;
	struct mychar_dev *pmydev = (struct mychar_dev*)pfile->private_data;
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

void led_init(struct mychar_dev *pgmydev)
{
	int lednum = 0;
	unsigned long tmpl = 0, tmpb = 0;

	pgmydev->led[0].offset = 7;
	pgmydev->led[0].con = (unsigned long*)ioremap(0x11000C40, sizeof(unsigned int));
	pgmydev->led[0].dat = (unsigned char*)ioremap(0x11000C44, sizeof(unsigned char));

	pgmydev->led[1].offset = 0;
	pgmydev->led[1].con = (unsigned long*)ioremap(0x11000C20, sizeof(unsigned int));
	pgmydev->led[1].dat = (unsigned char*)ioremap(0x11000C24, sizeof(unsigned char));

	pgmydev->led[2].offset = 4;
	pgmydev->led[2].con = (unsigned long*)ioremap(0x114001E0, sizeof(unsigned int));
	pgmydev->led[2].dat = (unsigned char*)ioremap(0x114001E4, sizeof(unsigned char));

	pgmydev->led[3].offset = 5;
	pgmydev->led[3].con = (unsigned long*)ioremap(0x114001E0, sizeof(unsigned int));
	pgmydev->led[3].dat = (unsigned char*)ioremap(0x114001E4, sizeof(unsigned char));

	for(lednum = 0; lednum < 4; lednum++)
	{
		tmpl = readl(pgmydev->led[lednum].con);
		writel((tmpl & ~((0xF)<<(pgmydev->led[lednum].offset*4))) | (0x1<<(pgmydev->led[lednum].offset*4)), pgmydev->led[lednum].con);
		tmpb = readb(pgmydev->led[lednum].dat);
		writeb(tmpb & (~(0x1)<<pgmydev->led[lednum].offset), pgmydev->led[lednum].dat);
	}
}

int __init mychar_init(void)
{
	int ret = 0;
	int i = 0;
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
	led_init(pgmydev);

	//printk("led4con=%p led4dat=%p\n", gmydev.led[2].con, gmydev.led[2].dat);
	//printk("led5con=%p led5dat=%p\n", gmydev.led[3].con, gmydev.led[3].dat);

	return 0;
}

void __exit mychar_exit(void)
{
	dev_t devno = MKDEV(major, minor);
	int lednum;
	for(lednum = 0; lednum < 4; lednum++)
	{
		iounmap(pgmydev->led[lednum].con);
		iounmap(pgmydev->led[lednum].dat);
	}
	cdev_del(&pgmydev->mydev); // 删除设备对象
	unregister_chrdev_region(devno, mychar_num); // 注销设备号
	kfree(pgmydev);
	pgmydev = NULL;
	printk("mychar will exit\n");
}


MODULE_LICENSE("GPL");

module_init(mychar_init);
module_exit(mychar_exit);
