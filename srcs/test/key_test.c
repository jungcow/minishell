#include <stdio.h>
#include <unistd.h>

int main(void)
{
	int key;

	while (1)
	{
		read(0, &key, sizeof(key));
		printf("%d\n", key);
	}
	return (0);
}
