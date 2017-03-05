#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/sched.h>
#include <linux/uaccess.h>
#include <linux/slab.h>
#include <linux/moduleparam.h>
#include <linux/miscdevice.h>
#include <linux/string.h>

MODULE_LICENSE("GPL");
MODULE_AUTHOR("River <feather12315@live.com>");
MODULE_DESCRIPTION("Traverse of PCB");
MODULE_VERSION("0.1");

struct info {
    pid_t pid;
    char comm[TASK_COMM_LEN]; 
};

struct buffer {
    wait_queue_head_t read_queue;
    struct mutex lock;
    int *data;
    int flag;
};

static struct buffer *buffer_alloc(void){
    struct buffer *buf = NULL;

    buf = kzalloc(sizeof(struct buffer), GFP_KERNEL);
    if(unlikely(!buf)){
        goto out;
    }

    buf->data = kzalloc(sizeof(int), GFP_KERNEL);
    if(unlikely(!buf->data))
        goto out_free;

    init_waitqueue_head(&buf->read_queue);

    mutex_init(&buf->lock);

out:
    return buf;
out_free:
    kfree(buf);
    return NULL;
}

static void buffer_free(struct buffer *buf){
    kfree(buf->data);
    kfree(buf);
}

static int traverse_open(struct inode *inode, struct file *file){
    struct buffer *buf;
    int err = 0;

    buf = buffer_alloc();
    if(unlikely(!buf)){
        err = -ENOMEM;
        goto out;
    }

    *(buf->data) = 0;
    buf->flag = 0;

    file->private_data = buf;

out:
    return err;
};

static ssize_t traverse_read(struct file *file, char __user *out,
        size_t size, loff_t *off){
    struct buffer *buf = file->private_data;
    struct task_struct *p;
    struct info *p_info = (struct info *)out;
    ssize_t result;
    int count = size / sizeof(struct info) - 1;
    int i;

    if(mutex_lock_interruptible(&buf->lock)){
        result = -ERESTARTSYS;
        goto out;
    }

    if(buf->flag && *(buf->data) > 0)
        count = count > *(buf->data) ? *(buf->data) : count;

    for(i=0, p=&init_task; i < count && (p = next_task(p)) != &init_task; i++){
        p_info[i].pid = p->pid;
        strcpy(p_info[i].comm, p->comm); 
    }

    p_info[i].pid = -1;
    wake_up_interruptible(&buf->read_queue);

    result = i;
    mutex_unlock(&buf->lock);

out:
    return result;
}

static ssize_t traverse_write(struct file *file, const char __user *in,
        size_t size, loff_t *off){
    struct buffer *buf = file->private_data;
    ssize_t result;

    if(mutex_lock_interruptible(&buf->lock)){
        result = -ERESTARTSYS;
        goto out;
    }

    if(copy_from_user(buf->data, in, size)){
        result = -EFAULT;
        goto out_unlock;
    }

    if(unlikely(!buf->data)){
        result = -EFAULT;
        goto out_unlock;
    }

    buf->flag = 1;

    wake_up_interruptible(&buf->read_queue);

    result = size;
out_unlock:
    mutex_unlock(&buf->lock);
out:
    return result;
}

static int traverse_close(struct inode *inode, struct file *file){
    struct buffer *buf = file->private_data;

    buffer_free(buf);

    return 0;
}

static struct file_operations traverse_fops = {
    .owner = THIS_MODULE,
    .open = traverse_open,
    .read = traverse_read,
    .write = traverse_write,
    .release = traverse_close,
    .llseek = noop_llseek
};

static struct miscdevice traverse_misc_device = {
    .minor = MISC_DYNAMIC_MINOR,
    .name = "traverse",
    .fops = &traverse_fops
};

static int __init traverse_init(void){
    misc_register(&traverse_misc_device);

    printk(KERN_INFO "traverse device has been registered.\n");
    return 0;
}

static void __exit traverse_exit(void){
    misc_deregister(&traverse_misc_device);

    printk(KERN_INFO "traverse device has been unregistered.\n");
}

module_init(traverse_init);
module_exit(traverse_exit);
