#include <fcntl.h>
#include <unistd.h>
#include <stdio.h>

int main(void)
{
	int fd = open("/dev/tty", RD_ONLY);
	printf("fd: %d\n", fd);
	
