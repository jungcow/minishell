#include <stdio.h>
#include <sys/stat.h>
#include <unistd.h>

int main(void)
{
	struct stat buf;
	char	*path;

	path = "../../README.md";
	printf("%d\n", stat(path, &buf));
	printf("size = %lld\n", buf.st_size);
	printf("type: %o\n", (unsigned int)buf.st_mode & 0xF000);
	printf("permission: %o\n", (unsigned int)buf.st_mode);
	printf("permission: %o\n", ((unsigned int)buf.st_mode & 0777) / 0100);
	return (0);
}
