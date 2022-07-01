#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("OMEN");
MODULE_DESCRIPTION("Export Symbol Assignment Program");

int addf(int a, int b)
{
	return (a+b);
}
EXPORT_SYMBOL_GPL(addf);


static int __init addmod1_init(void)
{
	printk(KERN_ALERT "\naddmod1_init\n");
	return 0;
}

static void __exit addmod1_exit(void)
{
	printk(KERN_ALERT "\naddmod1_exit\n");
}

module_init(addmod1_init);
module_exit(addmod1_exit);
