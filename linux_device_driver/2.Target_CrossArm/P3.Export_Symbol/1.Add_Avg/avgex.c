#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include"usrdefheader.h"

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Darky");
MODULE_DESCRIPTION("Using modprobe");

static int one=6;
static int two=24;

static int __init avg_init(void)
{
	int addition;
	addition = plus(one,two);
	printk(KERN_ALERT "\navg mod_init\nAddition: %d\nAverage: %d\n",addition,(addition/2));
	return 0;
}

static void __exit avg_exit(void)
{
	printk(KERN_ALERT "\navg mod_exit\nAddition & Average Complete\n");
}

module_init(avg_init);
module_exit(avg_exit);
