#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/select.h>
#include <sys/time.h>
#include <errno.h>

#include "../simpletest/mychar.h"


int main(int argc, const char *argv[])
{
	int fd = -1;
	int max = 0;
	int cur = 0;
	int ret = 0;
	fd_set rfds;
	char buf[BUFSIZ];

	if(argc < 2)
	{
		printf("The argument is too few\n");
		return 1;
	}

	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		printf("open %s failed!\n", argv[1]);
		return 2;
	}

	while(1)
	{
		FD_ZERO(&rfds);
		FD_SET(fd, &rfds);
		ret = select(fd+1, &rfds, NULL, NULL, NULL);
		if(ret < 0)
		{
			if(errno == EINTR)
				continue;
			else
			{
				perror("select");
				break;
			}
		}
		if(FD_ISSET(fd, &rfds))
		{
			ret = read(fd, buf, BUFSIZ);
			printf("ret = %d buf = %s\n", ret, buf);
		}
	}

	close(fd);
	fd = -1;

	return 0;
}
