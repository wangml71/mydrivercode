#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/cdev.h>

#define DEVCOUNT 3
#define DEVNAME "myhello"

struct cdev *dev;
unsigned int major = 0;
unsigned int minor = 0;

int myhello_open (struct inode *inode, struct file *file)
{
    printk("%s:%s:%d\n", __FILE__, __func__, __LINE__);
    return 0;
}

ssize_t myhello_read (struct file *file, char __user *ubuf, size_t size, loff_t *offs)
{
    printk("%s:%s:%d\n", __FILE__, __func__, __LINE__);
    return 0;
}

ssize_t myhello_write (struct file *file, const char __user *ubuf, size_t size, loff_t *offs)
{
    printk("%s:%s:%d\n", __FILE__, __func__, __LINE__);
    return 0;
}

int myhello_close (struct inode *inode, struct file *file)
{
    printk("%s:%s:%d\n", __FILE__, __func__, __LINE__);
    return 0;
}

const struct file_operations fops = {
    .open = myhello_open,
    .read = myhello_read,
    .write = myhello_write,
    .release = myhello_close,
};



static int __init myhello_init(void)
{
    int ret = 0;
    dev_t dev_num;
    dev = cdev_alloc();
    if(dev == NULL)
    {
        printk("alloc memory failed!\n");
        ret = -ENOMEM;
        goto ERR_STEP1;
    }
    cdev_init(dev, &fops);

    ret = alloc_chrdev_region(&dev_num, 0, DEVCOUNT, DEVNAME);
    if(ret)
    {
        printk("alloc char device num failed!\n");
        goto ERR_STEP2;
    }

    major = MAJOR(dev_num);
    minor = MINOR(dev_num);
    printk("major = %d, minor = %d \n", major, minor);

    ret = cdev_add(dev, dev_num, DEVCOUNT);
    if(ret)
    {
        printk("add device failed!\n");
        goto ERR_STEP3;
    }

    return 0;
ERR_STEP3:
    unregister_chrdev_region(dev_num, DEVCOUNT);
ERR_STEP2:
ERR_STEP1:
    return ret;
}

static void __exit myhello_exit(void)
{
    cdev_del(dev);
    unregister_chrdev_region(MKDEV(major, minor), DEVCOUNT);
}

module_init(myhello_init);
module_exit(myhello_exit);
MODULE_LICENSE("GPL");
