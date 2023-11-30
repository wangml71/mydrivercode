#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/timer.h>
#include <linux/device.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>
#include "mychar.h"

int major = 11;
int minor = 0;
int mychar_num = 1;

struct mychar_dev{
	struct cdev mydev;
	
	int second;
	struct timer_list tm;
	
	atomic_t openflag;

	struct class *pcls;
	struct device *pdev;
};

struct mychar_dev gmydev;

void second_func(unsigned long arg)
{
	struct mychar_dev *pmydev = (struct mychar_dev*)arg;

	pmydev->second++;

	mod_timer(&pmydev->tm, jiffies + 1 * HZ);
}

int mychar_open(struct inode *pnode, struct file *pfile)
{
	struct mychar_dev *pmydev;
	pfile->private_data = (void*)container_of(pnode->i_cdev, struct mychar_dev, mydev);

	pmydev = (struct mychar_dev*)pfile->private_data;
	if(atomic_dec_and_test(&pmydev->openflag))
	{
		pmydev->second = 0;
		pmydev->tm.expires = jiffies + 1 * HZ;
		pmydev->tm.function = second_func;
		pmydev->tm.data = (unsigned long)pmydev;

		add_timer(&pmydev->tm);

		return 0;
	}
	else
	{
		atomic_inc(&pmydev->openflag);
		printk("The device is already opened\n");
		return -1;
	}
	printk("mychar_open is called!\n");
	return 0;
}

int mychar_close(struct inode *pnode, struct file *pfile)
{
	struct mychar_dev *pmydev = (struct mychar_dev*)pfile->private_data;
	atomic_set(&pmydev->openflag, 1);
	del_timer(&pmydev->tm);
	printk("mychar_close is called!\n");
	return 0;
}

ssize_t mychar_read(struct file *pfile, char __user *puser, size_t size, loff_t *p_pos)
{
	int ret = 0;
	struct mychar_dev *pmydev = (struct mychar_dev*)pfile->private_data;

	if(size >= sizeof(int))
		size = sizeof(int);
	else
	{
		printk("size error!\n");
		return -1;
	}
#if linux_3_14
	ret = copy_to_user(puser, &pmydev->second, size);
#else
	ret = raw_copy_to_user(puser, &pmydev->second, size);
#endif
	if(ret)
	{
		printk("copy error");
		return -1;
	}
	return size;
}

struct file_operations myops = {
	.owner = THIS_MODULE,
	.open = mychar_open,
	.release = mychar_close,
	.read = mychar_read,
};

int __init mychar_init(void)
{
	int ret = 0;
	int i = 0;
	dev_t devno = MKDEV(major, minor);
	/*申请设备号*/
	ret = register_chrdev_region(devno, mychar_num, "atomicmychar");
	if(ret)
	{
		ret = alloc_chrdev_region(&devno, minor, mychar_num, "atomicmychar");
		if(ret)
		{
			printk("get devno failed!\n");
			return -1;
		}
		major = MAJOR(devno);
		minor = MINOR(devno);
	}
	printk("register succeed!(%d, %d)\n", major, minor);

	/*将设备对象添加进内核对应的数据结构里*/
	devno = MKDEV(major, minor+i);
	cdev_init(&gmydev.mydev, &myops); // 指定操作函数集
	gmydev.mydev.owner = THIS_MODULE;
	cdev_add(&gmydev.mydev, devno, 1);

	atomic_set(&gmydev.openflag, 1);
	init_timer(&gmydev.tm);

	gmydev.pcls = class_create(THIS_MODULE, "mydev");
	if(IS_ERR(gmydev.pcls))
	{
		printk("class_create failed\n");
		cdev_del(&gmydev.mydev); // 删除设备对象
		unregister_chrdev_region(devno, mychar_num); // 注销设备号
		return -1;
	}
	gmydev.pdev = device_create(gmydev.pcls, NULL, devno, NULL, "mysec");
	if(!gmydev.pdev)
	{
		printk("device_create failed\n");
		class_destroy(gmydev.pcls);
		cdev_del(&gmydev.mydev); // 删除设备对象
		unregister_chrdev_region(devno, mychar_num); // 注销设备号
		return -1;
	}

	return 0;
}

void __exit mychar_exit(void)
{
	dev_t devno = MKDEV(major, minor);
	device_destroy(gmydev.pcls, devno);
	class_destroy(gmydev.pcls);
	cdev_del(&gmydev.mydev); // 删除设备对象
	unregister_chrdev_region(devno, mychar_num); // 注销设备号
	printk("mychar will exit\n");
}

MODULE_LICENSE("GPL");

module_init(mychar_init);
module_exit(mychar_exit);
