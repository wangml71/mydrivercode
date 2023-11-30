#include <linux/module.h>
#include <linux/kernel.h>

extern int gxB;

int __init moduleA_init(void)
{
	printk("In moduleA init gxB = %d\n", gxB);
	return 0;
}

void __exit moduleA_exit(void)
{
	printk("moduleA will exit\n");
}


MODULE_LICENSE("GPL");

module_init(moduleA_init);
module_exit(moduleA_exit);
