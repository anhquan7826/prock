#ifndef __PROC_K__
#define __PROC_K__

#include <linux/semaphore.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/cdev.h>

typedef struct _proc_k {
    dev_t dev_no;
    struct semaphore sem;
    struct class *class;
    struct device *device;
    struct cdev cdev;
} proc_k;

#endif