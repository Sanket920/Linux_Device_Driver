#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/fs.h>
#include<linux/cdev.h>
#include<linux/device.h>
#include<linux/slab.h>
#include<linux/uaccess.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("OMEN");
MODULE_DESCRIPTION("Char Device Driver");

/*--Memory Size--------------------------------*/
#define mem_size 1024

dev_t dev = 0;

/*----Static Struct Class *dev class------------*/
static struct cdev char_cdev;
uint8_t *kernel_buffer;

/*----Function Prototypes-----------------------*/
static int __init char_driver_init(void);
static void __exit char_driver_exit(void);
static int char_open(struct inode *inode, struct file *file);
static int char_release(struct inode *inode, struct file *file);
static ssize_t char_read(struct file *filep, char __user *buf,size_t len, loff_t *off);
static ssize_t char_write(struct file *filep, const char *buf,size_t len, loff_t *off);


/*----File Operation Structure-------------------*/
static struct file_operations fops =
{
	.owner = THIS_MODULE,
	.read = char_read,
	.write = char_write,
	.open = char_open,
	.release = char_release,
};

/*----This Function Will Be Called When We Open Device File----*/
static int char_open(struct inode *inode, struct file *filep)
{
	pr_info("\nDevice File Opened...\n");
	return 0;
}


/*----This Function Will Be Called When We CLose THe Device File----*/
static int char_release(struct inode *inode, struct file *filep)
{
	pr_info("Device File CLosed...\n");
	return 0;
}


/*----This Fucntion Will Be Called When We Read The Device File----*/
static ssize_t char_read(struct file *filep, char __user *buf, size_t len, loff_t *off)
{
	/*--Copy The Data From The Kernel Space To User Space-->Copy To User--*/
	if(copy_to_user(buf, kernel_buffer, mem_size))
	{
		pr_err("Data Read: Error\n");
	}
	pr_info("Data Read: Done\n");
	return mem_size;
}


/*--------------This Function Will Be Called When We Write The Device File------------------*/
static ssize_t char_write(struct file *filep, const char __user *buf, size_t len, loff_t *off)
{
	/*--Copy The Data To Kernel Space From User Space-->Copy From User--*/
	if(copy_from_user(kernel_buffer, buf, len))
	{
		pr_err("Data Write:Error\n");
	}
	pr_info("Data Write: Done\n");
	return len;
}

/*----Module Init Function-----*/
static int __init char_driver_init(void)
{
	/*--Allocationg Major Number--*/
	if((alloc_chrdev_region(&dev, 0, 1, "CharDevice"))<0)
	{
		pr_info("Cannot Allocate Major Number\n");
		return -1;
	}
	pr_info("Major->%d Minor->%d\n",MAJOR(dev),MINOR(dev));


	/*--Creating cdev Structure--*/
	cdev_init(&char_cdev,&fops);


	/*--Adding Character Device To The System--*/
	if((cdev_add(&char_cdev,dev,1))<0)
	{
		pr_info("Cannot Add The Device To The System\n");
	}


	/*----Creating Physical Memory----*/
	if((kernel_buffer=kmalloc(mem_size, GFP_KERNEL)) == 0)
	{
		pr_info("Cannot Allocate Memory In Kernel\n");
	}
	strcpy(kernel_buffer, "Hello World");
	pr_info("Device Driver Insert...done\n");
	return 0;
}

/*----Module Exit Function----*/
static void __exit char_driver_exit(void)
{
	kfree(kernel_buffer);
	cdev_del(&char_cdev);
	unregister_chrdev_region(dev,1);
	pr_info("Device Driver Removed\n");
}

module_init(char_driver_init);
module_exit(char_driver_exit);
