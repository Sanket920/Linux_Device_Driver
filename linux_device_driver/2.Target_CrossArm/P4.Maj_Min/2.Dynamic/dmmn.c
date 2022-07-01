#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/kernel.h>
#include<linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Darky");
MODULE_DESCRIPTION("Dynamic Adding Major Minor->kernel");

dev_t dev= 0;
static int __init mod_init(void)
{
	if((alloc_chrdev_region(&dev,0,1,"charDynamic")) <0)
	{
		printk(KERN_INFO "\nCannot Allocate Major Number for charDynamic Device\n");
		return -1;
	}
	printk(KERN_INFO "Major = %d Minor = %d\n",MAJOR(dev),MINOR(dev));
	printk(KERN_INFO "Kernel Module Inserted Successfully...");

	return 0;
}

static void __exit mod_exit(void)
{
	unregister_chrdev_region(dev,1);
	printk(KERN_INFO "\nKernel Module Removed Successfully\n");
}

module_init(mod_init);
module_exit(mod_exit);


