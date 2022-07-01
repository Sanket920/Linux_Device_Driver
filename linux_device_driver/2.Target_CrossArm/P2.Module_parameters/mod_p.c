#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Darky");
MODULE_DESCRIPTION("Simple Program For Module Parameter");

static char *charvar = "ModuleParaMeter";

module_param(charvar,charp,S_IRUGO);

static int __init param_init(void)
{
	printk(KERN_ALERT "\nmodule_init\nThe Value of charvar: %s\n",charvar);
	return 0;
}

static void __exit param_exit(void)
{
	printk(KERN_ALERT "\nmodule_exit\nThank You\n");
}

module_init(param_init);
module_exit(param_exit);
