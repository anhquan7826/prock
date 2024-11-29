#ifndef __PROC_K_PROCESS__
#define __PROC_K_PROCESS__

#include <linux/proc_fs.h>
#include <linux/module.h>
#include <asm/uaccess.h>

int prock_proc_open(struct inode *inode, struct file *filp);
ssize_t prock_proc_read(struct file *filp, char __user *buffer, size_t count, loff_t *offset);


#endif