#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/platform_device.h>

#define GPX1CON 0x11000C20
#define GPX1DAT 0x11000C24

#define GPX2CON 0x11000C40
#define GPX2DAT 0x11000C44

#define GPF3CON 0x114001E0
#define GPF3DAT 0x114001E4

void fs4412leds_device_release(struct device *pdev)
{
	printk("fs4412leds_device_release is called\n");
}

struct resource fs4412leds_device_res[] = 
{
	[0] = {.start = GPX1CON, .end = GPX1CON + 3, .name = "GPX1CON", .flags = IORESOURCE_MEM},
	[1] = {.start = GPX1DAT, .end = GPX1DAT + 1, .name = "GPX1DAT", .flags = IORESOURCE_MEM},
	[2] = {.start = GPX2CON, .end = GPX2CON + 3, .name = "GPX2CON", .flags = IORESOURCE_MEM},
	[3] = {.start = GPX2DAT, .end = GPX2DAT + 1, .name = "GPX2DAT", .flags = IORESOURCE_MEM},
	[4] = {.start = GPF3CON, .end = GPF3CON + 3, .name = "GPF3CON", .flags = IORESOURCE_MEM},
	[5] = {.start = GPF3DAT, .end = GPF3DAT + 1, .name = "GPF3DAT", .flags = IORESOURCE_MEM},
};

struct platform_device_id leds_id = {
	.name = "fs4412leds",
};

struct platform_device fs4412leds_device = 
{
	.name = "fs4412leds",
	.dev.release = fs4412leds_device_release,
	.resource = fs4412leds_device_res,
	.num_resources = ARRAY_SIZE(fs4412leds_device_res),
	
	.id_entry = &leds_id,
};

int __init fs4412leds_device_init(void)
{
	platform_device_register(&fs4412leds_device);
	return 0;
}

void __exit fs4412leds_device_exit(void)
{
	platform_device_unregister(&fs4412leds_device);
	printk("fs4412leds_device will exit\n");
}


MODULE_LICENSE("GPL");

module_init(fs4412leds_device_init);
module_exit(fs4412leds_device_exit);
