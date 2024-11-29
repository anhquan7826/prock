#ifndef __PROC_K__
#define __PROC_K__

#include <linux/module.h>
#include <linux/cdev.h>
#include <linux/proc_fs.h>
#include <linux/fs.h>

struct prock {
    dev_t devno;
    struct cdev cdev;
    atomic_t dev_lock;
};

#endif