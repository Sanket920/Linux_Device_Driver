#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include"usrdefheader.h"
MODULE_LICENSE("GPL");
MODULE_AUTHOR("OMEN");
MODULE_DESCRIPTION("modprobe");

static int one=5;
static int two=15;

static int __init avgmod2_init(void)
{
	int sum;
	sum= addf(one,two);
	printk(KERN_ALERT "\navgmod2_init\nAddition of %d,%d is %d\nAverage %d\n",one,two,sum,(sum/2));
	return 0;
}

static void __exit avgmod2_exit(void)
{
	printk(KERN_ALERT "\navgmod2_exit\nProgram Complete\n");
}

module_init(avgmod2_init);
module_exit(avgmod2_exit);


