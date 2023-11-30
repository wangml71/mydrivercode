#include "mychar.h"

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <asm/uaccess.h>

#define MYCHAR_DEV_CNT 3

int major = 11;
int minor = 0;
int mychar_num = MYCHAR_DEV_CNT;

struct mychar_dev{
	struct cdev mydev;
	char mydev_buf[BUF_LEN];
	int curlen;
};

struct mychar_dev gmydev_arr[MYCHAR_DEV_CNT];

int mychar_open(struct inode *pnode, struct file *pfile)
{
	pfile->private_data = (void*)container_of(pnode->i_cdev, struct mychar_dev, mydev);
	printk("mychar_open is called!\n");
	return 0;
}

int mychar_close(struct inode *pnode, struct file *pfile)
{
	printk("mychar_close is called!\n");
	return 0;
}

ssize_t mychar_read(struct file *pfile, char __user *puser, size_t count, loff_t *ppos)
{
	struct mychar_dev *pmydev = (struct mychar_dev*)pfile->private_data;
	int size = 0, ret = 0;
	if(count > pmydev->curlen)
		size = pmydev->curlen;
	else
		size = count;
#if linux_3_14
	ret = copy_to_user(puser, pmydev->mydev_buf, size);
#else
	ret = raw_copy_to_user(puser, pmydev->mydev_buf, size);
#endif
	if(ret)
	{
		printk("copy_to_user failed\n");
		return -1;
	}

	memcpy(pmydev->mydev_buf, pmydev->mydev_buf + size, pmydev->curlen - size);
	pmydev->curlen -= size;

	return size;
}

ssize_t mychar_write(struct file *pfile, const char __user *puser, size_t count, loff_t *ppos)
{
	struct mychar_dev *pmydev = (struct mychar_dev*)pfile->private_data;
	int size = 0, ret = 0;
	if(count > BUF_LEN-pmydev->curlen)
		size = BUF_LEN-pmydev->curlen;
	else
		size = count;
	
#if linux_3_14
	ret = copy_from_user(pmydev->mydev_buf + pmydev->curlen, puser, size);
#else
	ret = raw_copy_from_user(pmydev->mydev_buf + pmydev->curlen, puser, size);
#endif
	if(ret)
	{
		printk("copy_from_user failed\n");
		return -1;
	}

	pmydev->curlen += size;

	return size;
}

long mychar_ioctl(struct file *pfile, unsigned int cmd, unsigned long arg)
{
	int __user *pret = (int*)arg;
	int maxlen = BUF_LEN;
	int ret = 0;
	struct mychar_dev *pmydev = (struct mychar_dev*)pfile->private_data;
	switch(cmd) {
	case MYCHAR_IOCTL_GET_MAXLEN:
#if linux_3_14
		ret = copy_to_user(pret, &maxlen, sizeof(int));
#else
		ret = raw_copy_to_user(pret, &maxlen, sizeof(int));
#endif
		if(ret)
		{
			printk("copy_to_user MAXLEN failed\n");
			return -1;
		}
		break;
	case MYCHAR_IOCTL_GET_CURLEN:
#if linux_3_14
		ret = copy_to_user(pret, &pmydev->curlen, sizeof(int));
#else
		ret = raw_copy_to_user(pret, &pmydev->curlen, sizeof(int));
#endif
		if(ret)
		{
			printk("copy_to_user CURLEN failed\n");
			return -1;
		}
		break;
	default:
		printk("The cmd is unknow\n");
		return -1;
	}
	return 0;
}

struct file_operations myops = {
	.owner = THIS_MODULE,
	.open = mychar_open,
	.release = mychar_close,
	.read = mychar_read,
	.write = mychar_write,
	.unlocked_ioctl = mychar_ioctl,
};

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

	/*将设备对象添加进内核对应的数据结构里*/
	for(i = 0; i<MYCHAR_DEV_CNT; i++)
	{
		devno = MKDEV(major, minor+i);
		cdev_init(&gmydev_arr[i].mydev, &myops); // 指定操作函数集
		gmydev_arr[i].mydev.owner = THIS_MODULE;
		cdev_add(&gmydev_arr[i].mydev, devno, 1);
	}

	return 0;
}

void __exit mychar_exit(void)
{
	dev_t devno = MKDEV(major, minor);
	int i;
	for(i = 0; i<MYCHAR_DEV_CNT; i++)
	{
		cdev_del(&gmydev_arr[i].mydev); // 删除设备对象
	}
	unregister_chrdev_region(devno, mychar_num); // 注销设备号
	printk("mychar will exit\n");
}


MODULE_LICENSE("GPL");

module_init(mychar_init);
module_exit(mychar_exit);
