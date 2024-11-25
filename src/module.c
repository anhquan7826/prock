#include <linux/module.h>

#include "module.h"

void hello(void) {
    printk(KERN_INFO "Hello, world!");
}