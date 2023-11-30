#include <linux/module.h>
#include <linux/kernel.h>

int gxC = 19;

EXPORT_SYMBOL(gxC);

int __init moduleC_init(void)
{
	printk("In moduleC init gxC = %d\n", gxC);
	return 0;
}

void __exit moduleC_exit(void)
{
	printk("moduleC will exit\n");
}


MODULE_LICENSE("GPL");

module_init(moduleC_init);
module_exit(moduleC_exit);
