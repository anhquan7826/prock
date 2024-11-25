#ifndef __PROCK__
#define __PROCK__

#include <linux/semaphore.h>

typedef struct _proc_k {
    struct semaphore sem;
} proc_k;

#endif