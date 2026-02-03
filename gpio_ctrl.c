// SPDX-License-Identifier: GPL-2.0
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/gpio.h>
#include <linux/interrupt.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include <linux/uaccess.h>
#include <linux/jiffies.h>
#include <linux/workqueue.h>

#define DEVICE_NAME "gpio_ctrl"

/* -------------------------------------------------
 * GPIO numbers (as per your platform)
 * ------------------------------------------------- */
#define LED_GPIO     533
#define BUTTON_GPIO  532

/* -------------------------------------------------
 * Character device variables
 * ------------------------------------------------- */
static dev_t dev;
static struct cdev gpio_cdev;
static struct class *gpio_class;

/* -------------------------------------------------
 * GPIO / IRQ related variables
 * ------------------------------------------------- */
static int irq_number;
static bool button_pressed_flag = false;
static int press_count = 0;
static bool led_state = false;

/* Wait queue for blocking read / poll */
static wait_queue_head_t wait_queue;

/* -------------------------------------------------
 * Debounce configuration
 * ------------------------------------------------- */
#define DEBOUNCE_DELAY_MS 50

/* Delayed work structure for debounce handling */
static struct delayed_work debounce_work;

/* =================================================
 * File operations
 * ================================================= */

static int gpio_open(struct inode *inode, struct file *file)
{
    return 0;
}

static int gpio_release(struct inode *inode, struct file *file)
{
    return 0;
}

/*
 * read()
 * Blocks until button press happens
 * Returns press_count to user space
 */
static ssize_t gpio_read(struct file *file,
                         char __user *buf,
                         size_t len,
                         loff_t *offset)
{
    char kbuf[16];
    int ret;

    /* Sleep until button_pressed_flag becomes true */
    if (!button_pressed_flag) {
        ret = wait_event_interruptible(wait_queue,
                                       button_pressed_flag);
        if (ret)
            return ret;
    }

    /* Copy press count to user */
    snprintf(kbuf, sizeof(kbuf), "%d\n", press_count);
    button_pressed_flag = false;

    if (copy_to_user(buf, kbuf, strlen(kbuf)))
        return -EFAULT;

    return strlen(kbuf);
}

/*
 * write()
 * User writes 0 or 1 to control LED
 */
static ssize_t gpio_write(struct file *file,
                          const char __user *buf,
                          size_t len,
                          loff_t *offset)
{
    char kbuf[8];
    int value;

    if (len > sizeof(kbuf) - 1)
        len = sizeof(kbuf) - 1;

    if (copy_from_user(kbuf, buf, len))
        return -EFAULT;

    kbuf[len] = '\0';

    if (kstrtoint(kbuf, 0, &value))
        return -EINVAL;

    if (value != 0 && value != 1)
        return -EINVAL;

    gpio_set_value(LED_GPIO, value);
    led_state = value;

    return len;
}

/*
 * poll()
 * Allows select()/poll() from user space
 */
static unsigned int gpio_poll(struct file *file,
                              poll_table *wait)
{
    unsigned int mask = 0;

    poll_wait(file, &wait_queue, wait);

    if (button_pressed_flag)
        mask |= POLLIN | POLLRDNORM;

    return mask;
}

/* File operations structure */
static struct file_operations fops = {
    .owner   = THIS_MODULE,
    .open    = gpio_open,
    .release = gpio_release,
    .read    = gpio_read,
    .write   = gpio_write,
    .poll    = gpio_poll,
};

/* =================================================
 * Debounce work function
 * Runs after debounce delay
 * ================================================= */
static void debounce_work_func(struct work_struct *work)
{
    bool state;

    /* Read button GPIO after debounce time */
    state = gpio_get_value(BUTTON_GPIO);

    if (state) {
        /* Valid button press */
        led_state = !led_state;
        gpio_set_value(LED_GPIO, led_state);

        press_count++;
        button_pressed_flag = true;

        /* Wake up readers / pollers */
        wake_up_interruptible(&wait_queue);

        pr_info("gpio_ctrl: Button pressed, LED=%d, count=%d\n",
                led_state, press_count);
    }

    /* Re-enable interrupt after debounce */
    enable_irq(irq_number);
}

/* =================================================
 * ISR (Interrupt Service Routine)
 * ================================================= */
static irqreturn_t button_isr(int irq, void *dev_id)
{
    /* Disable IRQ immediately to avoid bounce */
    disable_irq_nosync(irq_number);

    /* Schedule debounce work */
    schedule_delayed_work(&debounce_work,
                          msecs_to_jiffies(DEBOUNCE_DELAY_MS));

    return IRQ_HANDLED;
}

/* =================================================
 * Module Init
 * ================================================= */
static int __init gpio_init(void)
{
    int ret;

    pr_info("gpio_ctrl: Initializing\n");

    /* Allocate character device number */
    ret = alloc_chrdev_region(&dev, 0, 1, DEVICE_NAME);
    if (ret)
        return ret;

    /* Initialize and add cdev */
    cdev_init(&gpio_cdev, &fops);
    gpio_cdev.owner = THIS_MODULE;
    ret = cdev_add(&gpio_cdev, dev, 1);
    if (ret)
        goto err_cdev;

    /* Create class and device node */
    gpio_class = class_create(DEVICE_NAME);
    if (IS_ERR(gpio_class)) {
        ret = PTR_ERR(gpio_class);
        goto err_class;
    }

    device_create(gpio_class, NULL, dev, NULL, DEVICE_NAME);

    /* Request LED GPIO */
    ret = gpio_request(LED_GPIO, "LED_GPIO");
    if (ret)
        goto err_gpio;

    gpio_direction_output(LED_GPIO, 0);

    /* Request Button GPIO */
    ret = gpio_request(BUTTON_GPIO, "BUTTON_GPIO");
    if (ret)
        goto err_led;

    gpio_direction_input(BUTTON_GPIO);

    /* Initialize debounce work */
    INIT_DELAYED_WORK(&debounce_work, debounce_work_func);

    /* Request IRQ for button (RISING edge) */
    irq_number = gpio_to_irq(BUTTON_GPIO);
    ret = request_irq(irq_number,
                      button_isr,
                      IRQF_TRIGGER_RISING,
                      "gpio_button_irq",
                      NULL);
    if (ret)
        goto err_button;

    /* Initialize wait queue */
    init_waitqueue_head(&wait_queue);

    pr_info("gpio_ctrl: Module loaded successfully\n");
    return 0;

err_button:
    gpio_free(BUTTON_GPIO);
err_led:
    gpio_free(LED_GPIO);
err_gpio:
    device_destroy(gpio_class, dev);
    class_destroy(gpio_class);
err_class:
    cdev_del(&gpio_cdev);
err_cdev:
    unregister_chrdev_region(dev, 1);
    return ret;
}

/* =================================================
 * Module Exit
 * ================================================= */
static void __exit gpio_exit(void)
{
    cancel_delayed_work_sync(&debounce_work);
    free_irq(irq_number, NULL);

    gpio_free(BUTTON_GPIO);
    gpio_free(LED_GPIO);

    device_destroy(gpio_class, dev);
    class_destroy(gpio_class);

    cdev_del(&gpio_cdev);
    unregister_chrdev_region(dev, 1);

    pr_info("gpio_ctrl: Module unloaded\n");
}

module_init(gpio_init);
module_exit(gpio_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Srikanth Reddy");
MODULE_DESCRIPTION("GPIO Driver with Single-Edge Strict Debounce and Toggle LED");
