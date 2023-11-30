#include "mychar.h"
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/spinlock.h>
#include <asm/uaccess.h>
#include <asm/atomic.h>

#define MY_CHAR_MAGIC 'k'

int major = 11;
int minor = 0;
int mychar_num = 1;

struct mychar_dev{
	struct cdev mydev;
	int openflag;
	spinlock_t lock;
};

struct mychar_dev gmydev;

int mychar_open(struct inode *pnode, struct file *pfile)
{
	struct mychar_dev *pmydev;
	pfile->private_data = (void*)container_of(pnode->i_cdev, struct mychar_dev, mydev);

	pmydev = (struct mychar_dev*)pfile->private_data;

	spin_lock(&pmydev->lock);
	if(pmydev->openflag)
	{
		pmydev->openflag = 0;
		spin_unlock(&pmydev->lock);
		return 0;
	}
	else
	{
		spin_unlock(&pmydev->lock);
		printk("The device is already opened\n");
		return -1;
	}
	printk("mychar_open is called!\n");
	return 0;
}

int mychar_close(struct inode *pnode, struct file *pfile)
{
	struct mychar_dev *pmydev = (struct mychar_dev*)pfile->private_data;
	spin_lock(&pmydev->lock);
	pmydev->openflag = 1;
	spin_unlock(&pmydev->lock);
	printk("mychar_close is called!\n");
	return 0;
}

struct file_operations myops = {
	.owner = THIS_MODULE,
	.open = mychar_open,
	.release = mychar_close,
};

int __init mychar_init(void)
{
	int ret = 0;
	int i = 0;
	dev_t devno = MKDEV(major, minor);
	/*申请设备号*/
	ret = register_chrdev_region(devno, mychar_num, "spinlockmychar");
	if(ret)
	{
		ret = alloc_chrdev_region(&devno, minor, mychar_num, "spinlockmychar");
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

	gmydev.openflag = 1;
	spin_lock_init(&gmydev.lock);

	return 0;
}

void __exit mychar_exit(void)
{
	dev_t devno = MKDEV(major, minor);
	cdev_del(&gmydev.mydev); // 删除设备对象
	unregister_chrdev_region(devno, mychar_num); // 注销设备号
	printk("mychar will exit\n");
}

MODULE_LICENSE("GPL");

module_init(mychar_init);
module_exit(mychar_exit);
