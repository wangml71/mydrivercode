#include <stdio.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <linux/input.h>

int main(int argc, const char *argv[])
{
	int fd = -1;
	struct input_event evt;
	if(argc < 2)
	{
		printf("Argument is not enough\n");
		return 1;
	}

	//open
	fd = open(argv[1], O_RDONLY);
	if(fd < 0)
	{
		perror("open");
		return 2;
	}

	while(1)
	{
		read(fd, &evt, sizeof(evt));
		if(evt.type == EV_KEY && evt.code == KEY_3)
		{
			if(evt.value) printf("KEY3 DOWN\n");
			else printf("KEY3 UP\n");
		}
	}

	//close
	close(fd);
	fd = -1;

	return 0;
}
