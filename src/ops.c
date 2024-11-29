#include <linux/module.h>
#include <linux/cdev.h>

#include "ops.h"
#include "constants.h"
#include "module_t.h"

int open(struct inode *inode, struct file *file)
{
    struct prock *module = container_of(inode->i_cdev, struct prock, cdev);
    if (!atomic_inc_and_test(&module->dev_lock))
    {
        pr_err("%s: cannot open, device is busy!", DEV_NAME);
        return -EINVAL;
    }
    return 0;
}

int release(struct inode *inode, struct file *file)
{
    struct prock *module = container_of(inode->i_cdev, struct prock, cdev);
    if (!atomic_dec_and_test(&module->dev_lock))
    {
        pr_err("%s: cannot open, device is busy!", DEV_NAME);
    }
    return 0;
}

long ioctl(struct file *file, unsigned int command, unsigned long argument)
{
    return 0;
}
