#include <linux/init.h>
#include <linux/module.h>
#include <linux/fs.h>
#include <linux/miscdevice.h>
#include <linux/kernel.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/sched/signal.h>

MODULE_LICENSE("Dual BSD/GPL");

static ssize_t my_read(struct file* file, char __user* out, size_t size, loff_t* off) {
    int* buffer = kmalloc(sizeof(int) * 10000, GFP_KERNEL);
    int row = 0;
    struct task_struct* task;
    for_each_process(task) {
        buffer[row] = task->pid;
	buffer[row + 1] = task_ppid_nr(task);
	buffer[row + 2] = task_cpu(task);
	buffer[row + 3] = task->state;
	row = row + 4;
    }
    buffer[row] = -1;
    copy_to_user(out, buffer, sizeof(int) * 10000);
    kfree(buffer);
    return 0;
}

static struct file_operations my_fops = {
    .owner = THIS_MODULE,
    .read = my_read,
};

static struct miscdevice my_misc_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "process_list",
    .fops = &my_fops,
};

static int __init my_module_init(void) {
    int ret = misc_register(&my_misc_device);
    if(ret) {
        printk(KERN_ALERT "Fail to register the miscdevice!\n");
    } else {
        printk(KERN_INFO "Successfully register the miscdevice.\n");
    }
    return ret;
}

static void __exit my_module_exit(void) {
    misc_deregister(&my_misc_device);
    printk(KERN_INFO "Successfully unregister the miscdevice.\n");
}

module_init(my_module_init);
module_exit(my_module_exit);
