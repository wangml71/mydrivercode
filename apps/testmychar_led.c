#include "../platform/fs4412leds_driver.h"

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
		printf("The element is not enough\n");
		return 1;
	}
	fd = open(argv[1], O_WRONLY);
	if(fd < 0)
	{
		printf("open %s failed\n", argv[1]);
		return 2;
	}

	int lednum;
	for(lednum=2; lednum<=5; lednum++)
	{
		ioctl(fd, LED_IOCTL_ON, lednum);
		sleep(1);
		ioctl(fd, LED_IOCTL_OFF, lednum);
		sleep(1);
	}

	int T=10;
	while(T--)
	{
		for(lednum=2; lednum<=5; lednum++)
			ioctl(fd, LED_IOCTL_TOGGLE, lednum);
		sleep(1);
	}

	close(fd);
	fd = -1;

	return 0;
}
