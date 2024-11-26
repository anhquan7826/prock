#include "prock.h"
#include "prock_info.h"

MODULE_AUTHOR("Nguyen Anh Quan");
MODULE_DESCRIPTION("A module providing system info to user app.");
MODULE_LICENSE("GPL");

proc_k *prock = NULL;

struct file_operations fops = {
    .owner = THIS_MODULE
};

static int __init proc_k_init(void)
{
    printk(KERN_INFO "%s: initiating module...", DEV_NAME);
    int result = 0;
    dev_t dev_no;

    result = alloc_chrdev_region(&dev_no, 1, 1, DEV_NAME);
    if (result < 0)
    {
        goto err_alloc_chrdev_region;
    }
    int major = MAJOR(dev_no);
    int minor = MINOR(dev_no);
    printk(KERN_INFO "%s: allocated number: %d.%d", DEV_NAME, major, minor);

    prock = kmalloc(sizeof(proc_k), GFP_KERNEL);
    if (!prock)
    {
        result = -1;
        goto err_device_malloc;
    }
    memset(prock, 0, sizeof(proc_k));
    printk(KERN_INFO "%s: device allocated!", DEV_NAME);

    prock->cdev.owner = THIS_MODULE;
    sema_init(&prock->sem, 1);
    cdev_init(&prock->cdev, &fops);
    prock->dev_no = dev_no;

    result = cdev_add(&prock->cdev, prock->dev_no, 1);
    if (result < 0)
    {
        goto err_cdev_add;
    }
    printk(KERN_INFO "%s: device added!", DEV_NAME);

    struct class *class = class_create(DEV_NAME);
    if (!class)
    {
        result = -1;
        goto err_class_create;
    }
    printk(KERN_INFO "%s: device class created!", DEV_NAME);

    struct device *device = device_create(class, NULL, dev_no, NULL, DEV_NAME);
    if (!device)
    {
        result = -1;
        goto err_device_create;
    }
    printk(KERN_INFO "%s: device created!", DEV_NAME);

    prock->class = class;
    prock->device = device;

    printk(KERN_INFO "%s: module initiated!", DEV_NAME);

    return result;

    err_device_create:
        printk(KERN_ERR "%s: cannot add device!", DEV_NAME);
        return result;

    err_cdev_add:
        printk(KERN_ERR "%s: cannot add device!", DEV_NAME);
        return result;

    err_device_malloc:
        printk(KERN_ERR "%s: cannot allocate device!", DEV_NAME);
        return result;

    err_class_create:
        printk(KERN_ERR "%s: cannot create device class!", DEV_NAME);
        return result;

    err_alloc_chrdev_region:
        printk(KERN_ERR "%s: cannot allocate major number!", DEV_NAME);
        return result;
}

static void __exit proc_k_exit(void)
{
    printk(KERN_INFO "%s: module exiting...", DEV_NAME);
    device_del(prock->device);
    class_destroy(prock->class);
    unregister_chrdev_region(prock->dev_no, 1);
    cdev_del(&prock->cdev);
    kfree(prock);
    printk(KERN_INFO "%s: module exited!", DEV_NAME);
}

module_init(proc_k_init);
module_exit(proc_k_exit);