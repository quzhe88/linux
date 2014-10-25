#include <linux/init.h>
#include <linux/module.h>
#include <linux/kernel.h>

static int __init hello_init(void);
static void __exit hello_exit(void);

static int __init hello_init(void)
{
	printk("hello world\n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk("hello exit\n");
}

module_init(hello_init);
module_exit(hello_exit);
MODULE_LICENSE("GPL");