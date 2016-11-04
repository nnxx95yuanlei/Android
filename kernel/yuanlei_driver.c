/* Copyright (c) 2012-2015, The Linux Foundation. All rights reserved.
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 and
 * only version 2 as published by the Free Software Foundation.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 */

#include <linux/of.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/module.h>
#include <linux/workqueue.h>
#include <linux/delay.h>
#include <linux/types.h>
#include <linux/list.h>
#include <linux/ioctl.h>
#include <linux/spinlock.h>
#include <linux/proc_fs.h>
#include <linux/atomic.h>
#include <linux/videodev2.h>
#include <linux/msm_ion.h>
#include <linux/iommu.h>
#include <linux/platform_device.h>
#include <linux/debugfs.h>

struct cdev* led_dev;




int led_open(struct inode *inode, struct file *filp)
{
    pr_err("yuanlei---22222222");
	return 0;
}

int led_close(struct inode *inode, struct file *filp)
{
    pr_err("yuanlei---33333333333");
	return 0;
}

ssize_t led_read(struct file *filp, char *buf, size_t len, loff_t *off)
{
    char read_line[256] = "hello, my name is yuanlei, i am come from kernel space";
    pr_err("yuanlei---1111111111");
    memcpy(buf,read_line,sizeof(read_line));    
	len = strlen(read_line);
    return 0;
}

ssize_t led_write(struct file *filp, const char *buf, size_t len, loff_t *off)
{
    pr_err("yuanlei---444444444444");
	return 0;
}








static struct file_operations led_fops = {
	.owner  = THIS_MODULE,
	.open   = led_open,
	//.poll   = led_poll,
	.release = led_close,
	.read = led_read,
	.write = led_write,
	//.ioctl   = led_ioctl,
#ifdef CONFIG_COMPAT
	//.compat_ioctl32 = led_ioctl2,
#endif
};

static int led_probe(struct platform_device *pdev)
{
    int ret,major,minor;
	dev_t devno;
	struct class *led_class;
	
    ret = alloc_chrdev_region(&devno, 0, 1, "yuanlei");
	major = MAJOR(devno); 
	minor = MINOR(devno); 
	led_dev = cdev_alloc();
	led_dev->ops = &led_fops;
	led_dev->owner = THIS_MODULE;
    cdev_add(led_dev, devno, 1);
	led_class = class_create(THIS_MODULE, "yuanlei_led");
	device_create(led_class, NULL,devno, NULL,"yuanlei_dev");
    return 0;
}



static const struct of_device_id led_dt_match[] = {
	{.compatible = "yuanlei,led"},
	{}
}

MODULE_DEVICE_TABLE(of, led_dt_match);

static struct platform_driver led_driver = {
	.probe = led_probe,
	.driver = {
		.name = "yuanlei",
		.owner = THIS_MODULE,
		.of_match_table = led_dt_match,
	},
};

static int __init led_driver_init(void)
{
	return platform_driver_register(&led_driver);
}

static void __exit led_driver_exit(void)
{
	platform_driver_unregister(&led_driver);
}



module_init(led_driver_init);
module_exit(led_driver_exit);
MODULE_DESCRIPTION("yuanlei own driver");
MODULE_LICENSE("GPL v2");

