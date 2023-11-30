#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>

int main(int argc, const char *argv[])
{
	int sec = 0;
	int fd = -1;
	if(argc < 2)
	{
		printf("The argument is too few\n");
		return 1;
	}
	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		perror("open");
		return 2;
	}

	while(sec<=10)
	{
		read(fd, &sec, sizeof(sec));
		printf("sec = %d\n", sec);
		sleep(1);
	}

	close(fd);
	fd = -1;
	return 0;
}
