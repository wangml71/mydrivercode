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

	fd = open(argv[1], O_WRONLY | O_NONBLOCK);
	if(fd < 0)
	{
		printf("open %s failed!\n", argv[1]);
		return 2;
	}

	char buf[BUFSIZ] = "hello char!";
	//int ret = write(fd, buf, BUFSIZ);
	//printf("first write ret = %d\n",ret);

	ioctl(fd, MYCHAR_IOCTL_GET_MAXLEN, &max);
	printf("max len is %d\n", max);

	int ret = write(fd, buf, strlen(buf));
	printf("second write ret = %d\n",ret);
	close(fd);
/*
	fd = open(argv[1], O_RDONLY | O_NONBLOCK);
	if(fd < 0)
	{
		printf("open %s failed!\n", argv[1]);
		return 2;
	}

	ioctl(fd, MYCHAR_IOCTL_GET_CURLEN, &cur);
	printf("cur len is %d\n", cur);

	char buf[BUFSIZ];
	bzero(buf, BUFSIZ);
	int ret = read(fd, buf, cur);
	if(ret < 0)
		printf("Nothing to read\n");
	else
		printf("ret = %d buf = %s\n", ret, buf);
*/
	close(fd);
	fd = -1;

	return 0;
}
