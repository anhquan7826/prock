#ifndef __PROC_K_OPS__
#define __PROC_K_OPS__

#include <linux/module.h>
#include <linux/fs.h>

int open(struct inode *inode, struct file *file);

int release(struct inode *inode, struct file *file);

long ioctl(struct file *file, unsigned int command, unsigned long argument);

#endif