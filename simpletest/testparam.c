#include <linux/module.h>
#include <linux/kernel.h>

int gx = 10;
char *gstr = "hello";
int garr[5] = {1,2,3,4,5};

module_param(gx, int, 0664);
module_param(gstr, charp, 0664);
module_param_array(garr, int, NULL, 0664);

int __init testparam_init(void)
{
	int i;
	printk("gx = %d\n", gx);
	printk("gstr = %s\n", gstr);
	for(i=0; i<5; i++)
		printk("%d ", garr[i]);
	printk("\n");
	return 0;
}

void __exit testparam_exit(void)
{
	printk("testparam will exit\n");
}


MODULE_LICENSE("GPL");

module_init(testparam_init);
module_exit(testparam_exit);

