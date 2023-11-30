#include <linux/module.h>
#include <linux/kernel.h>

int gxB = 20;
extern int gxC;

EXPORT_SYMBOL(gxB);

int __init moduleB_init(void)
{
	printk("In moduleB init gxB = %d\n", gxB);
	printk("In moduleB init gxC = %d\n", gxC);
	return 0;
}

void __exit moduleB_exit(void)
{
	printk("moduleB will exit\n");
}


MODULE_LICENSE("GPL");

module_init(moduleB_init);
module_exit(moduleB_exit);
