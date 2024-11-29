#include "process.h"

int prock_proc_open(struct inode *inode, struct file *filp)
{
    return 0;
}

ssize_t prock_proc_read(struct file *filp, char __user *buffer, size_t count, loff_t *offset)
{
    const char *hello = "Hello, world!";
    size_t size = strlen(hello);
    if (copy_to_user(buffer, hello, size)) {
        return -ENOMEM;
    };
    return 0;
}