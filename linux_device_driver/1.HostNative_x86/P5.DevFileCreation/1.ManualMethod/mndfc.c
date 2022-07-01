#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("OMEN");
MODULE_DESCRIPTION("Linux Driver(Mannually Creating Device File)");

dev_t dev = 0;


static int __init mod_init(void)
{
	/*--Allocating Major Number--*/
	if((alloc_chrdev_region(&dev,0,1,"CharDevice1"))<0)
	{
		pr_err("Cannot Allocate Major Number For Device\n");
		return -1;
	}
	pr_info("Kernel Module Inserted Successfully...\n");
	return 0;
}

static void __exit mod_exit(void)
{
	unregister_chrdev_region(dev,1);
	pr_info("Kernel Module Removed Successfully...\n");
}

module_init(mod_init);
module_exit(mod_exit);
