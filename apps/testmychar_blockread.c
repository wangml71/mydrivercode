#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

#include "../simpletest/mychar.h"


int main(int argc, const char *argv[])
{
	int fd = -1;
	int max = 0;
	int cur = 0;
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

	ioctl(fd, MYCHAR_IOCTL_GET_CURLEN, &cur);
	printf("cur len is %d\n", cur);

	char buf[BUFSIZ];
	bzero(buf, BUFSIZ);
	int ret = read(fd, buf, BUFSIZ);
	if(ret < 0)
		printf("Nothing to read\n");
	else
		printf("ret = %d buf = %s\n", ret, buf);

	close(fd);
	fd = -1;

	return 0;
}
