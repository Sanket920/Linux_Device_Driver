#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Darky");
MODULE_DESCRIPTION("Simple Module _init|_exit Program");

static int __init hello_init(void)
{
	printk(KERN_ALERT "\nThis Is Module_init\nHello....\n");
	return 0;
}

static void __exit hello_exit(void)
{
	printk(KERN_ALERT "\nThis Is Module_exit\nGoodBye\n");
}

module_init(hello_init);
module_exit(hello_exit);

