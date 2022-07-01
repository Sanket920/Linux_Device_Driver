#include<linux/init.h>
#include<linux/module.h>
#include<linux/kernel.h>
#include<linux/kdev_t.h>
#include<linux/fs.h>
#include<linux/uaccess.h>
#include<linux/cdev.h>
#include<linux/types.h>
#include<linux/completion.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("OMEN");
MODULE_DESCRIPTION("Linux Ddriver[Synchronization Using Completion]");

/*Declaration*/
dev_t dev_dr;
struct cdev *my_dev;
struct completion my_completion;
unsigned int op_result;
int op_done_flag = 0;

static int my_open(struct inode *inode, struct file *file);
static int my_release(struct inode *inode, struct file *file);

static ssize_t my_write(struct file *file, const char __user *ubuff, size_t count, loff_t *off);
static ssize_t my_read(struct file *file,char __user *ubuff, size_t count, loff_t *off);


static int my_operation(char *ubuff);

struct file_operations fops =
{
	.owner = THIS_MODULE,
	.open = my_open,
	.write = my_write,
	.read = my_read,
	.release = my_release,
};

/*Definition*/
static int my_open(struct inode *inode, struct file *file)
{
	printk("Open Functionality..\n");
	return 0;
}

static ssize_t my_write(struct file *file,const char __user *ubuff, size_t count, loff_t *off)
{
	printk("In Write Functionality");
	int ret_val;
	if(op_done_flag != 0)
	{
		wait_for_completion(&my_completion);
		ret_val = my_operation(ubuff);

	          if(ret_val == 0)
                	{
	                     op_done_flag = 1;
		             return count;
	                }
	           else
	                     return -1;
	}
	else
	{
		ret_val = my_operation(ubuff);
		if(ret_val == 0)
		{
			op_done_flag = 1;
			return count;
		}
		else
			return -1;
	}
}


static ssize_t my_read(struct file *file,char __user *ubuff, size_t count, loff_t *off)
{
	printk("In Read Functionality..\n");
	int result = copy_to_user((char *)ubuff, &op_result,sizeof(op_result));
	if(result == 0)
	{
		printk("Success In Reading Data From Kernel To User.\n");
		printk("In Read Section The Result Is: %d\n",op_result);
		complete(&my_completion);
		op_done_flag =0;

		return count;
	}
	else
	{
		pr_err("Error In Reading Data From Kernel To User.\n");
		return -1;
	}
}


static int my_release(struct inode *inode,struct file *file)
{
	printk("Exit Functionality");
	return 0;
}



static int my_operation(char *ubuff)
{
	int kbuff[2],result,num1,num2;
	result = copy_from_user((char *)kbuff,(char *)ubuff,sizeof(kbuff));
	if(result == 0)
	{
		printk("Success In Writing Data From User To Kernel.\n");
		num1 = kbuff[0];
		num2 = kbuff[1];

		op_result = num1 + num2;
		printk("Result In Write Section Of The Driver: %d\n",op_result);
		return 0;
	}
	else
	{
		printk("Error In Writing From User To Kernel\n");
		return -1;
	}
}

/*Module _init*/
static int my_completion_init(void)
{
	printk("Initialization Function.\n");
	if(alloc_chrdev_region(&dev_dr,0,3,"CompletionDr")<0)
	{
		pr_err("Major Number Not Allocated.\n");
		return -1;
	}
	pr_info("Major: %d Minor: %d\n",MAJOR(dev_dr),MINOR(dev_dr));
	my_dev = cdev_alloc();
	my_dev->ops = &fops;

	if(cdev_add(my_dev,dev_dr,3) <0)
	{
		pr_err("Error Registering Device With File Operation.\n");
		return -1;
	}

	init_completion(&my_completion);
	return 0;
}


/*Mod _exit*/
static void my_completion_exit(void)
{
	printk("In Exit Section\n");
	
	cdev_del(my_dev);
	printk("Success In Deactivate\n");

	unregister_chrdev_region(dev_dr,3);
	printk("Success In Deregister\n");
}


module_init(my_completion_init);
module_exit(my_completion_exit);
