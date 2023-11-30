#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/ioctl.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>

int main(int argc, const char *argv[])
{
	int fd = -1;
	if(argc < 2)
	{
		printf("The argument is too few\n");
		return 1;
	}

	fd = open(argv[1], O_RDWR);
	if(fd < 0)
	{
		printf("open %s failed!\n", argv[1]);
		return 2;
	}

	while(1);

	close(fd);
	fd = -1;

	return 0;
}
