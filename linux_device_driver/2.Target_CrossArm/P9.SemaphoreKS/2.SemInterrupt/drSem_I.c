#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/semaphore.h>
#include<linux/cdev.h>
#include<linux/types.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Darky");
MODULE_DESCRIPTION("Kernel Synchronization Using SemaPhore[Interrupt]");


/*Declaration*/
dev_t dev_dr;

struct cdev *my_dev;
struct semaphore my_sem;

unsigned int op_result;

static int my_open(struct inode *inode,struct file *file);
static int my_release(struct inode *inode, struct file *file);

static ssize_t my_write(struct file *file,const char __user *ubuff, size_t count, loff_t *off);
static ssize_t my_read(struct file *file, char __user *ubuff,size_t count, loff_t *off);

struct file_operations fops=
{
	.owner = THIS_MODULE,
	.open = my_open,
	.write = my_write,
	.read = my_read,
	.release = my_release,
};


/*Defintion*/
/**/
static int my_open(struct inode *inode,struct file *file)
{
	printk("Open Functionality\n");
	return 0;
}

/**/
static ssize_t my_write(struct file *file,const char __user *ubuff, size_t count, loff_t *off)
{
	down_interruptible(&my_sem);
	printk("In Write Function\n");

	int kbuff[2];
	int result, num1, num2;

	result = copy_from_user((char *)kbuff,(char *)ubuff,sizeof(kbuff));
	if(result == 0)
	{
		printk("Success In Writing Data From User To Kernel.\n");
		num1 = kbuff[0];
		num2 = kbuff[1];

		op_result = num1 + num2;
		printk("Result In Write Section Of Driver: %d\n",op_result);
		return count;
	}
	else
	{
		pr_err("Error In Writing Data From User To Kernel.\n");
		return -1;
	}
}


static ssize_t my_read(struct file *file,char __user *ubuff,size_t count, loff_t *off)
{
	printk("In Read Function\n");
	int result = copy_to_user((char *)ubuff,&op_result,sizeof(op_result));
	if(result == 0)
	{
		printk("Success In Reading Data From Kernel To User.\n");
		printk("In Read Section The Result is: %d\n",op_result);
		up(&my_sem);
		return count;
	}
	else
	{
		pr_err("Error In Reading Data From Kernel To User\n");
		return -1;
	}
}


/**/
static int my_release(struct inode *inode,struct file *file)
{
	printk("In Exit Function");
	return 0;
}

/*Module _Init*/
static int my_sem_init(void)
{
	printk("Initialization Function\n");
	if(alloc_chrdev_region(&dev_dr,0,3,"SemIntDriver") <0)
	{
		pr_err("Major Number Not Allocated\n");
		return -1;
	}
	pr_info("Major = %d, Minor = %d\n",MAJOR(dev_dr),MINOR(dev_dr));

	my_dev = cdev_alloc();
	my_dev->ops = &fops;


	if(cdev_add(my_dev,dev_dr,3)<0)
	{
		pr_err("Error Registering Device With File OPeration.\n");
		return -1;
	}

	sema_init(&my_sem,1);
	return 0;
}


/*Module _exit*/
static void my_sem_exit(void)
{
	printk("In _exit Function\n");
	cdev_del(my_dev);
	printk("Success In Deactivate\n");

	unregister_chrdev_region(dev_dr,3);
	printk("Success In Deregister\n");
}


module_init(my_sem_init);
module_exit(my_sem_exit);


