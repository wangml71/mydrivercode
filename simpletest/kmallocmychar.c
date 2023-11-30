#include "mychar.h"

#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/wait.h>
#include <linux/sched.h>
#include <linux/poll.h>
#include <linux/mutex.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <asm/uaccess.h>

int major = 11;
int minor = 0;
int mychar_num = 1;

struct mychar_dev{
	struct cdev mydev;
	char mydev_buf[BUF_LEN];
	int curlen;
	struct mutex mtx;
	wait_queue_head_t rq;
	wait_queue_head_t wq;
	struct fasync_struct *pasync_obj;
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
	struct mychar_dev *pmydev = (struct mychar_dev*)pfile->private_data;
	if(pmydev->pasync_obj != NULL)
		fasync_helper(-1, pfile, 0, &pmydev->pasync_obj);
	printk("mychar_close is called!\n");
	return 0;
}

ssize_t mychar_read(struct file *pfile, char __user *puser, size_t count, loff_t *ppos)
{
	struct mychar_dev *pmydev = (struct mychar_dev*)pfile->private_data;
	int size = 0, ret = 0;

	mutex_lock(&pmydev->mtx);
	if(pmydev->curlen <= 0)
	{
		if(pfile->f_flags & O_NONBLOCK)
		{
			mutex_unlock(&pmydev->mtx);
			printk("O_NONBLOCK No Data Read!\n");
			return -1;
		}
		else
		{
			mutex_unlock(&pmydev->mtx);
			ret = wait_event_interruptible(pmydev->rq, pmydev->curlen > 0);
			if(ret)
			{
				printk("Wake mutex_unlock by signal\n");
				return -ERESTARTSYS;
			}
			mutex_lock(&pmydev->mtx);
		}
	}

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
		mutex_unlock(&pmydev->mtx);
		printk("copy_to_user failed\n");
		return -1;
	}

	memcpy(pmydev->mydev_buf, pmydev->mydev_buf + size, pmydev->curlen - size);
	pmydev->curlen -= size;

	mutex_unlock(&pmydev->mtx);
	wake_up_interruptible(&pmydev->wq);

	printk("mychar_read is called!\n");
	return size;
}

ssize_t mychar_write(struct file *pfile, const char __user *puser, size_t count, loff_t *ppos)
{
	struct mychar_dev *pmydev = (struct mychar_dev*)pfile->private_data;
	int size = 0, ret = 0;

	mutex_lock(&pmydev->mtx);
	if(pmydev->curlen >= BUF_LEN)
	{
		if(pfile->f_flags & O_NONBLOCK)
		{
			mutex_unlock(&pmydev->mtx);
			printk("O_NONBLOCK Cannot Write Data!\n");
			return -1;
		}
		else
		{
			mutex_unlock(&pmydev->mtx);
			ret = wait_event_interruptible(pmydev->wq, pmydev->curlen < BUF_LEN);
			if(ret)
			{
				printk("Wake mutex_unlock by signal\n");
				return -ERESTARTSYS;
			}
			mutex_lock(&pmydev->mtx);
		}
	}

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
		mutex_unlock(&pmydev->mtx);
		printk("copy_from_user failed\n");
		return -1;
	}

	pmydev->curlen += size;

	mutex_unlock(&pmydev->mtx);
	wake_up_interruptible(&pmydev->rq);

	if(pmydev->pasync_obj != NULL)
		kill_fasync(&pmydev->pasync_obj, SIGIO, POLL_IN);

	printk("mychar_write is called!\n");
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
		mutex_lock(&pmydev->mtx);
#if linux_3_14
		ret = copy_to_user(pret, &pmydev->curlen, sizeof(int));
#else
		ret = raw_copy_to_user(pret, &pmydev->curlen, sizeof(int));
#endif
		mutex_unlock(&pmydev->mtx);
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

unsigned int mychar_poll(struct file *pfile, poll_table *ptb)
{
	struct mychar_dev *pmydev = (struct mychar_dev*)pfile->private_data;
	unsigned int mask = 0;

	poll_wait(pfile, &pmydev->rq, ptb);
	poll_wait(pfile, &pmydev->wq, ptb);

	mutex_lock(&pmydev->mtx);
	if(pmydev->curlen > 0)
		mask |= POLLIN | POLLRDNORM;
	if(pmydev->curlen < BUF_LEN)
		mask |= POLLOUT | POLLWRNORM;
	mutex_unlock(&pmydev->mtx);

	return mask;
}

int mychar_fasync(int fd, struct file *pfile, int mode)
{
	struct mychar_dev *pmydev = (struct mychar_dev*)pfile->private_data;
	return fasync_helper(fd, pfile, mode, &pmydev->pasync_obj);
}

struct file_operations myops = {
	.owner = THIS_MODULE,
	.open = mychar_open,
	.release = mychar_close,
	.read = mychar_read,
	.write = mychar_write,
	.unlocked_ioctl = mychar_ioctl,
	.poll = mychar_poll,
	.fasync = mychar_fasync,
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
	
	pgmydev = (struct mychar_dev*)kmalloc(sizeof(struct mychar_dev), GFP_KERNEL);
	if(!pgmydev)
	{
		unregister_chrdev_region(devno, mychar_num);
		printk("kmalloc for struct mychar_dev failed\n");
		return -1;
	}

	/*将设备对象添加进内核对应的数据结构里*/
	devno = MKDEV(major, minor+i);
	cdev_init(&pgmydev->mydev, &myops); // 指定操作函数集
	pgmydev->mydev.owner = THIS_MODULE;
	cdev_add(&pgmydev->mydev, devno, 1);

	init_waitqueue_head(&pgmydev->rq);
	init_waitqueue_head(&pgmydev->wq);

	mutex_init(&pgmydev->mtx);

	return 0;
}

void __exit mychar_exit(void)
{
	dev_t devno = MKDEV(major, minor);
	cdev_del(&pgmydev->mydev); // 删除设备对象
	unregister_chrdev_region(devno, mychar_num); // 注销设备号
	kfree(pgmydev);
	printk("mychar will exit\n");
}


MODULE_LICENSE("GPL");

module_init(mychar_init);
module_exit(mychar_exit);
