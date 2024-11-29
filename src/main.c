#include "module_t.h"
#include "ops.h"
#include "constants.h"

static struct prock *module = NULL;

static struct class *class = NULL;

static struct device *device = NULL;

static const struct file_operations operations = {
    .owner = THIS_MODULE,
    .open = open,
    .release = release,
    .unlocked_ioctl = ioctl
};

static int __init_module(void)
{
    int result = 0;

    pr_info("%s: initiating module...", DEV_NAME);
    pr_info("%s: allocating module...", DEV_NAME);
    module = kmalloc(sizeof(struct prock), GFP_KERNEL);
    if (!module) goto r_alloc_module;
    memset(module, 0, sizeof(struct prock));

    pr_info("%s: allocation chrdev region...", DEV_NAME);
    result = alloc_chrdev_region(&module->devno, 1, 1, DEV_NAME);
    if (result) goto r_alloc_chrdev_region;

    pr_info("%s: adding character device", DEV_NAME);
    cdev_init(&module->cdev, &operations);
    module->cdev.owner = THIS_MODULE;
    result = cdev_add(&module->cdev, module->devno, 1);
    if (result) goto r_cdev_add;

    return result;

    r_cdev_add:
        pr_info("%s: cannot add character device", DEV_NAME);
        cdev_del(&module->cdev);

    r_alloc_chrdev_region:
        pr_info("%s: cannot allocate chrdev region", DEV_NAME);
        unregister_chrdev_region(module->devno, 1);

    r_alloc_module:
        pr_info("%s: cannot allocate module", DEV_NAME);
        kfree(module);

    return -EAGAIN;
}

static int __init_device(void)
{
    int result = 0;

    pr_info("%s: creating class...", DEV_NAME);
    class = class_create(DEV_NAME);
    if (IS_ERR(class)) goto r_class_create;

    pr_info("%s: creating device...", DEV_NAME);
    device = device_create(class, NULL, module->devno, NULL, DEV_NAME);
    if (IS_ERR(device)) goto r_device_create;

    return result;

    r_device_create:
        result = PTR_ERR(device);
        pr_info("%s: cannot create device (error %d)", DEV_NAME, result);
        device_del(device);

    r_class_create:
        result = PTR_ERR(class);
        pr_err("%s: cannot create class (error %d)", DEV_NAME, result);    
        class_destroy(class);

    return result;
}

static int __init prock_init(void)
{   
    int result = 0;
    result = __init_module();
    if (result) {
        return -EAGAIN;
    }
    result = __init_device();
    if (result) {
        return -EAGAIN;
    }
    return 0;
}

static void __exit prock_exit(void)
{
    cdev_del(&module->cdev);
    device_del(device);
    class_destroy(class);
    unregister_chrdev_region(module->devno, 1);
    kfree(module);
    pr_info("%s: Module exited.", DEV_NAME);
}

MODULE_AUTHOR("Nguyen Anh Quan");
MODULE_DESCRIPTION("A module providing system info to user app.");
MODULE_LICENSE("GPL");

module_init(prock_init);
module_exit(prock_exit);