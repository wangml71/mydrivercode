#ifndef DT_KEY_MYCHAR_H
#define DT_KEY_MYCHAR_H

enum KEYNODE{
	KEY2 = 1002,
	KEY3,
	KEY4,
};

enum KEY_STATUS{
	KEY_DOWN = 0,
	KEY_UP,
};

struct keyvalue{
	int code;
	int status;
};


#endif
