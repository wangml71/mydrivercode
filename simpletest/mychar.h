#ifndef MYCHAR_H
#define MYCHAR_H

#include <asm/ioctl.h>

#define linux_3_14 1
#define BUF_LEN 100
#define MY_CHAR_MAGIC 'k'
#define MYCHAR_IOCTL_GET_MAXLEN _IOR(MY_CHAR_MAGIC, 1, int*)
#define MYCHAR_IOCTL_GET_CURLEN _IOR(MY_CHAR_MAGIC, 2, int*)

#endif
