#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "../simpletest/dtkeymychar.h"


int main(int argc, const char *argv[])
{
	int fd = -1;
	size_t size = 0;
	struct keyvalue keydata;

	if(argc < 2)
	{
		printf("The argument is too few\n");
		return 1;
	}
/*
	fd = open(argv[1], O_WRONLY);
	if(fd < 0)
	{
		printf("open %s failed!\n", argv[1]);
		return 2;
	}

	char buf[BUFSIZ] = "hello char!";

	ioctl(fd, MYCHAR_IOCTL_GET_MAXLEN, &max);
	printf("max len is %d\n", max);

	write(fd, buf, strlen(buf));
	close(fd);
*/
	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		printf("open %s failed!\n", argv[1]);
		return 2;
	}

	while((size = read(fd, &keydata, sizeof(keydata))) == sizeof(keydata))
	{
		if(keydata.status == KEY_DOWN)
		{
			printf("key3 is down\n");
		}
		else
		{
			printf("key3 is up\n");
		}
	}

	close(fd);
	fd = -1;

	return 0;
}
