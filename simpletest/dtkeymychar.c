#include "dtkeymychar.h"

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
#include <linux/spinlock.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/of_fdt.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <asm/uaccess.h>

int major = 11;
int minor = 0;
int mychar_num = 1;

struct mychar_dev{
	struct cdev mydev;
	spinlock_t lock;
	int gpio;
	int irqno;
	struct keyvalue data;
	int newflag;
	wait_queue_head_t rq;
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

ssize_t mychar_read(struct file *pfile, char __user *puser, size_t count, loff_t *p_pos)
{
	struct mychar_dev *pmydev = (struct mychar_dev*)pfile->private_data;
	int ret = 0, size = 0;

	if(count < sizeof(struct keyvalue))
	{
		printk("expect read size is invalid\n");
		return -1;
	}
	
	spin_lock(&pmydev->lock);
	if(!pmydev->newflag)
	{
		if(pfile->f_flags & O_NONBLOCK)
		{
			spin_unlock(&pmydev->lock);
			printk("O_NONBLOCK No Data Read\n");
			return -1;
		}
		else
		{
			spin_unlock(&pmydev->lock);
			ret = wait_event_interruptible(pmydev->rq, pmydev->newflag == 1);
			if(ret)
			{
				printk("Wake up by signal\n");
				return -ERESTARTSYS;
			}
			spin_lock(&pmydev->lock);
		}
	}

	if(count > sizeof(struct keyvalue))
		size = sizeof(struct keyvalue);
	else
		size = count;
	
	ret = copy_to_user(puser, &pmydev->data, size);
	if(ret)
	{
		spin_unlock(&pmydev->lock);
		printk("copy_to_user failed\n");
		return -1;
	}

	pmydev->newflag = 0;

	spin_unlock(&pmydev->lock);

	return size;
}

unsigned int mychar_poll(struct file *pfile, poll_table *ptb)
{
	struct mychar_dev *pmydev = (struct mychar_dev*)pfile->private_data;
	unsigned int mask = 0;
	poll_wait(pfile, &pmydev->rq, ptb);
	spin_lock(&pmydev->lock);
	if(pmydev->newflag)
	{
		mask |= POLLIN | POLLRDNORM;
	}
	spin_unlock(&pmydev->lock);
	return mask;
}

struct file_operations myops = {
	.owner = THIS_MODULE,
	.open = mychar_open,
	.release = mychar_close,
	.read = mychar_read,
	.poll = mychar_poll,
};

irqreturn_t key2_irq_handle(int no, void *arg)
{
	struct mychar_dev *pmydev = (struct mychar_dev*)arg;
	int status = 0;
	int status1 = 0;
	int status2 = 0;
	status1 = gpio_get_value(pmydev->gpio);
	mdelay(1);
	status2 = gpio_get_value(pmydev->gpio);
	if(status1 != status2)
		return IRQ_NONE;
	
	status = status1;

	spin_lock(&pmydev->lock);
	if(status == pmydev->data.status)
	{
		spin_unlock(&pmydev->lock);
		return IRQ_NONE;
	}

	pmydev->data.code = KEY2;
	pmydev->data.status = status;
	pmydev->newflag = 1;
	spin_unlock(&pmydev->lock);

	wake_up(&pmydev->rq);

	return IRQ_HANDLED;
}

int __init mychar_init(void)
{
	int ret = 0;
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

	pgmydev = (struct mychar_dev*)kmalloc(sizeof(struct mychar_dev), GFP_KERNEL);

	/*将设备对象添加进内核对应的数据结构里*/
	devno = MKDEV(major, minor);
	cdev_init(&pgmydev->mydev, &myops); // 指定操作函数集
	pgmydev->mydev.owner = THIS_MODULE;
	cdev_add(&pgmydev->mydev, devno, 1);

	spin_lock_init(&pgmydev->lock);
	init_waitqueue_head(&pgmydev->rq);

	pnode = of_find_node_by_path("/fs4412-keys/key2_node");
	if(!pnode)
	{
		kfree(pgmydev);
		pgmydev = NULL;
		printk("find pnode failed\n");
		return -1;
	}
	pgmydev->gpio = of_get_named_gpio(pnode, "key2-gpio", 0);
	pgmydev->irqno = irq_of_parse_and_map(pnode, 0);

	ret = request_irq(pgmydev->irqno, key2_irq_handle, IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING, "fs4412key2", pgmydev);
	if(ret)
	{
		kfree(pgmydev);
		pgmydev = NULL;
		printk("request irq failed\n");
		return -1;
	}

	return 0;
}

void __exit mychar_exit(void)
{
	dev_t devno = MKDEV(major, minor);

	free_irq(pgmydev->irqno, pgmydev);
	
	cdev_del(&pgmydev->mydev); // 删除设备对象
	unregister_chrdev_region(devno, mychar_num); // 注销设备号
	
	kfree(pgmydev);
	pgmydev = NULL;
	
	printk("mychar will exit\n");
}


MODULE_LICENSE("GPL");

module_init(mychar_init);
module_exit(mychar_exit);
