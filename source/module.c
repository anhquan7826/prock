#include <linux/init.h>
#include <linux/module.h>

#include "module.h"

MODULE_AUTHOR("Nguyen Anh Quan")
MODULE_DESCRIPTION("A module providing system info to user app.")
MODULE_LICENSE("GPL")

struct file_operations proc_k_fops = {
    .owner = THIS_MODULE,
};

static int __init proc_k_init(void)
{
    printk(KERN_INFO "proc_k: initiating module...");

    printk(KERN_INFO "proc_k: module initiated!");
}

static int __exit proc_k_exit(void)
{
    printk(KERN_INFO "proc_k: module exiting...");
    
    printk(KERN_INFO "proc_k: module exited!");
}

module_init(proc_k_init);
module_exit(proc_k_exit);