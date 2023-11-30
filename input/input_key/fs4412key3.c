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
#include <linux/input.h>
#include <linux/spinlock.h>
#include <linux/gpio.h>
#include <linux/of_gpio.h>
#include <linux/of_irq.h>
#include <linux/of_fdt.h>
#include <linux/interrupt.h>
#include <linux/delay.h>
#include <asm/uaccess.h>

struct fs4412_key_dev{
	struct input_dev *pdev;
	int gpio;
	int irqno;
};

struct fs4412_key_dev *pgmydev;

irqreturn_t key3_irq_handle(int no, void *arg)
{
	struct fs4412_key_dev *pmydev = (struct fs4412_key_dev*)arg;
	int status = 0;
	int status1 = 0;
	int status2 = 0;
	status1 = gpio_get_value(pmydev->gpio);
	mdelay(1);
	status2 = gpio_get_value(pmydev->gpio);
	if(status1 != status2)
		return IRQ_NONE;
	
	status = status1;

	if(status)
		input_event(pmydev->pdev, EV_KEY, KEY_3, 0);
	else
		input_event(pmydev->pdev, EV_KEY, KEY_3, 1);

	input_sync(pmydev->pdev);

	return IRQ_HANDLED;
}

int __init fs4412_key_init(void)
{
	int ret = 0;
	struct device_node *pnode = NULL;

	pgmydev = (struct fs4412_key_dev*)kmalloc(sizeof(struct fs4412_key_dev), GFP_KERNEL);

	pnode = of_find_node_by_path("/fs4412-keys/key3_node");
	if(!pnode)
	{
		kfree(pgmydev);
		pgmydev = NULL;
		printk("find pnode failed\n");
		return -1;
	}
	pgmydev->gpio = of_get_named_gpio(pnode, "key3-gpio", 0);
	pgmydev->irqno = irq_of_parse_and_map(pnode, 0);
	pgmydev->pdev = input_allocate_device();

	set_bit(EV_KEY, pgmydev->pdev->evbit);
	set_bit(KEY_3, pgmydev->pdev->keybit);

	ret = input_register_device(pgmydev->pdev);
	if(ret)
	{
		input_free_device(pgmydev->pdev);
		kfree(pgmydev);
		pgmydev = NULL;
		printk("request input device failed\n");
		return -1;
	}

	ret = request_irq(pgmydev->irqno, key3_irq_handle, IRQF_TRIGGER_FALLING | IRQF_TRIGGER_RISING, "fs4412key3", pgmydev);
	if(ret)
	{
		input_unregister_device(pgmydev->pdev);
		input_free_device(pgmydev->pdev);
		kfree(pgmydev);
		pgmydev = NULL;
		printk("request irq failed\n");
		return -1;
	}

	return 0;
}

void __exit fs4412_key_exit(void)
{
	free_irq(pgmydev->irqno, pgmydev);
	
	input_unregister_device(pgmydev->pdev);
	input_free_device(pgmydev->pdev);
	
	kfree(pgmydev);
	pgmydev = NULL;
	
	printk("fs4412_key will exit\n");
}

MODULE_LICENSE("GPL");

module_init(fs4412_key_init);
module_exit(fs4412_key_exit);
