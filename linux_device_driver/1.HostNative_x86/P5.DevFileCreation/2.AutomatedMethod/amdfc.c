#include<linux/kernel.h>
#include<linux/init.h>
#include<linux/module.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/device.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("OMEN");
MODULE_DESCRIPTION("Linux Driver (Automatically Creating Device File)");

dev_t dev = 0;

static struct class *dev_class;


static int __init mod_init(void)
{
	/*--Allocating Major Number--*/
	if((alloc_chrdev_region(&dev,0,1, "Auto_dev"))<0)
	{
		pr_err("Cannot Allocate Major Number For Device\n");
		return -1;
	}
	pr_info("Major = %d Minor = %d \n",MAJOR(dev),MINOR(dev));




	/*--Creating Struct Class--*/
	if((dev_class = class_create(THIS_MODULE,"Auto_dev")) == NULL)
	{
		pr_err("Cannot Create The Struct Class For Device\n");
		goto r_class;
	}


	/*--Creating Device--*/
	if((device_create(dev_class,NULL,dev,NULL,"Auto_dev")) == NULL)
	{
		pr_err("Cannot Create The Device\n");
		goto r_device;
	}
	pr_info("Kernel Module Inserted Successfully...\n");
	return 0;


r_device:
	class_destroy(dev_class);

r_class:
	unregister_chrdev_region(dev,1);
	return -1;
}

static void __exit mod_exit(void)
{
	device_destroy(dev_class,dev);
	class_destroy(dev_class);
	unregister_chrdev_region(dev,1);
	pr_info("Kernel Module Removed Successfully...\n");
}

module_init(mod_init);
module_exit(mod_exit);
