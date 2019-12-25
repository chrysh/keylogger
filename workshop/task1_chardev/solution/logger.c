#include <linux/cdev.h>
#include <linux/uaccess.h>
#include <linux/fs.h>

#include "keylogger.h"

#define LOGGER_MAJOR 200
#define LOGGER_MINOR 1

static struct class *logger_class;
static struct cdev logger_cdev;
static dev_t devno = MKDEV(LOGGER_MAJOR, LOGGER_MINOR);

static int logger_open(struct inode *ino, struct file *file)
{
	printk("%s", __func__);
	return 0;
}

static int logger_close(struct inode *ino, struct file *file)
{
	printk("%s", __func__);
	return 0;
}

static ssize_t logger_write(struct file *file, const  char *buf,
			    size_t count, loff_t *offset)
{
	printk("%s", __func__);
	return count;
}

static ssize_t logger_read(struct file *file, char *buf, size_t count,
		       loff_t *offset)
{
	printk("%s", __func__);
	return count;
}

static struct file_operations logger_fops = {
	.owner		= THIS_MODULE,
	.read		= logger_read,
	.write		= logger_write,
	.open		= logger_open,
	.release	= logger_close,
};

int init_logger(void)
{
	int ret = 0;
	static struct device *ldev;

	DBG("%s", __func__);
	ret = alloc_chrdev_region(&devno, LOGGER_MAJOR, 1, "keylogger");
	if (ret < 0) {
		printk("Major number allocation failed");
		return ret;
	}

	logger_class = class_create(THIS_MODULE, "keylogger");	// To create device node in /dev

	if(IS_ERR(logger_class)) {
		printk("Err class");
		goto err_class;
	}

	cdev_init(&logger_cdev, &logger_fops);
	ret = cdev_add(&logger_cdev, devno, 1);
	if (ret < 0) {
		printk("Unable to add cdev");
		goto err_chardev;
	}

	ldev = device_create(logger_class, NULL, devno, NULL, "keylogger%d", 0);

	if (IS_ERR(ldev)) {
		printk("Err dev");
		goto err_dev;
	}

	printk("init logger successfull");

	return 0;

err_dev:
	cdev_del(&logger_cdev);
err_chardev:
	class_destroy(logger_class);
err_class:
	unregister_chrdev_region(devno, 1);
	return ret;
}

void remove_logger(void)
{
	DBG("%s", __func__);
	device_destroy(logger_class, devno);
	cdev_del(&logger_cdev);
	class_destroy(logger_class);
	unregister_chrdev_region(devno, 1);
}
