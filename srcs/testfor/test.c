#include <stdio.h>
#include <sys/wait.h>
#include <unistd.h>
#include <stdlib.h>

#define READ 0
#define WRITE 1

void	test(void)
{
	char *arg1[] = {"ls", NULL};
	char *arg3[] = {"cat", NULL};
	char *arg2[] = {"grep", "test", NULL};
	int i;
	int fd[3][2];
	pid_t pid[3];
	int status;


	i = 0;
	while (i < 3)
		pipe(fd[i]);
	while (i < 3)
	{
		pid[i] = fork();
		if (pid[i] < 0)
		{
			printf("pid error\n");
			return ;
		}
		else if (pid[i] == 0)
		{
			if (i != 0)
			{
				close(fd[i - 1][1]);
				dup2(fd[i - 1][0], 0);
				close(fd[i - 1][0]);
			}
			if (i < 2)
			{
				close(fd[i][0]);
				dup2(fd[i][1], 1);
				close(fd[i][1]);
			}
			if (i == 0)
				execve("/bin/ls", arg1, NULL);
			else if (i== 1)
				execve("/usr/bin/grep", arg2, NULL);
			else if (i == 2)
				execve("/bin/cat", arg3, NULL);
			exit(1);
		}
		else
		{
			waitpid(pid[i], &status, 0);
		}
		i++;
	}
}

int main(void)
{
	test();
	return (0);
}
