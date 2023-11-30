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
#include <signal.h>

#include "../simpletest/mychar.h"

int fd = -1;
char buf[BUFSIZ];
void sigio_handler(int signo);

int main(int argc, const char *argv[])
{
	int ret = 0;
	int flg = 0;

	if(argc < 2)
	{
		printf("The argument is too few\n");
		return 1;
	}
	
	signal(SIGIO, sigio_handler);

	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		printf("open %s failed!\n", argv[1]);
		return 2;
	}

	fcntl(fd, F_SETOWN, getpid());
	flg = fcntl(fd, F_GETFL);
	fcntl(fd, F_SETFL, flg|FASYNC);
	
	while(1);

	close(fd);
	fd = -1;

	return 0;
}

void sigio_handler(int signo)
{
	int ret = read(fd, buf, BUFSIZ);
	printf("ret = %d, buf = %s\n", ret, buf);
}
