#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>
#include <stdlib.h>


void	test(void)
{
	char *argv2[] = {"cat", NULL};
	char *argv1[] = {"ls", NULL};

	int fd[2];
	int status;

	pid_t	pid;
	pid_t	pid2;

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		close(fd[0]);
		dup2(fd[1], 1);
		close(fd[1]);
		sleep(10);
		execve("/bin/ls", argv1, NULL);
	}
	else if (pid > 0)
	{
		pid2 = fork();
		if (pid2 == 0)
		{
			close(fd[1]);
			dup2(fd[0], 0);
			close(fd[0]);
			sleep(10);
			execve("/bin/cat", argv2, NULL);
		}
		else if (pid2 > 0)
		{
			sleep(10);
			close(fd[0]);
			close(fd[1]);
			waitpid(pid, &status, 0);
			waitpid(pid2, &status, 0);
		}
	}
}

void	test2(char **envp)
{
//	char *argv2[] = {"cat", NULL};
//	char *argv1[] = {"ls", NULL};
//	char *argv3[] = {"grep", NULL};
//	char *argv4[] = {"sort", "-r", NULL};
	char *argv1[] = {"env", NULL};
	char *argv2[] = {"echo", NULL};
	char *argv3[] = {"export", NULL};

//	int fd[5][2];
	int fd[2];
	int	old[2];
	int status;

	int i = 0;
	
	pid_t	pid[3];

	while (i < 3)
	{
//		pipe(fd[i]);
		pipe(fd);
		pid[i] = fork();
		if (pid[i] == 0)
		{
			if (i + 1 < 3)
			{
			//	close(fd[i][0]);
			//	dup2(fd[i][1], 1);
			//	close(fd[i][1]);
				dup2(fd[1], 1);
				close(fd[1]);
				close(fd[0]);
			}
			if (i > 0)
			{
			//	close(fd[i - 1][1]);
			//	dup2(fd[i - 1][0], 0);
			//	close(fd[i - 1][0]);
				dup2(old[0], 0);
				close(old[1]);
				close(old[0]);
			}
			if (i == 0)
			//	execve("/bin/cat", argv2, NULL);
				execve("/usr/bin/env", argv1, envp);
			else if (i == 1)
			//	execve("/bin/cat", argv2, NULL);
				execve("/bin/echo", argv2, envp);
			else if (i == 2)
				execve("/usr/bin/env", argv1, envp);
			//	execve("/bin/ls", argv1, NULL);
		/*	else if (i == 3)
				execve("/usr/bin/grep", argv3, NULL);
			else if (i == 4)
			//	execve("/usr/bin/sort", argv4, NULL);
				execve("/bin/echo", argv2, NULL);
				*/
			exit(1);
		}
		else if (pid[i] > 0)
		{
			if (i > 0)
			{
				close(old[0]);
				close(old[1]);
			}
		}
		old[0] = fd[0];
		old[1] = fd[1];
		i++;
	}
	close(old[0]);
	close(old[1]);
	i = 0;
	while (i < 3)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
}

int main(int argc, char *argv[], char *envp[])
{
//	test();
	test2(envp);
	return (0);
}
