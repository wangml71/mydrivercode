#include<stdio.h>
#define _GNU_SOURCE
#include<unistd.h>
#include<sys/syscall.h>

#define __NR_hello 441

int main(int argc, const char *argv[])
{
	(void) syscall(__NR_hello, "hello syscall ...............");

	return 0;
}
