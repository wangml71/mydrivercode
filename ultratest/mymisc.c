#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>

int mymisc_open(struct inode *inode, struct file *file)
{
    printk("%s:%s:%d\n", __FILE__, __func__, __LINE__);
    return 0;
}
ssize_t mymisc_read(struct file *file, char __user *buf, size_t size, loff_t *offs)
{
    printk("%s:%s:%d\n", __FILE__, __func__, __LINE__);
    return 0;
}
ssize_t mymisc_write(struct file *file, const char __user *buf, size_t size, loff_t *offs)
{
    printk("%s:%s:%d\n", __FILE__, __func__, __LINE__);
    return 0;
}
int mymisc_close(struct inode *inode, struct file *file)
{
    printk("%s:%s:%d\n", __FILE__, __func__, __LINE__);
    return 0;
}

const struct file_operations fops = {
    .owner = THIS_MODULE,
    .open = mymisc_open,
    .read = mymisc_read,
    .write = mymisc_write,
    .release = mymisc_close,
};

struct miscdevice mymisc = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "mymisc",
    .fops = &fops,
};

static int __init mymisc_init(void)
{
    return misc_register(&mymisc);
}

static void __exit mymisc_exit(void)
{
    misc_deregister(&mymisc);
}

module_init(mymisc_init);
module_exit(mymisc_exit);
MODULE_LICENSE("GPL");
