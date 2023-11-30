#ifndef MYCHAR_H
#define MYCHAR_H

#include <asm/ioctl.h>

#define linux_3_14 1
#define MY_CHAR_MAGIC 'k'
#define LED_IOCTL_ON _IOR(MY_CHAR_MAGIC, 1, int)
#define LED_IOCTL_OFF _IOR(MY_CHAR_MAGIC, 2, int)
#define LED_IOCTL_TOGGLE _IOR(MY_CHAR_MAGIC, 3, int)

#endif
