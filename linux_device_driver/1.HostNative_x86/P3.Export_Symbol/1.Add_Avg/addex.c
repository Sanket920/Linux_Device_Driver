#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("OMEN");
MODULE_DESCRIPTION("Export Symbol Program For Avg");

int plus(int a,int b)
{
	return (a+b);
}

EXPORT_SYMBOL(plus);

static int __init mod_init(void)
{
	printk(KERN_ALERT "\nADD mod_init\n");
	return 0;
}

static void __exit mod_exit(void)
{
	printk(KERN_ALERT "\nADD mod_exit\n");
}

module_init(mod_init);
module_exit(mod_exit);
