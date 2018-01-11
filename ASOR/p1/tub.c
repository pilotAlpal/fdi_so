#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

void main (int args, char **argv)
{
int fd[2];
pipe(fd);
pid_t pid = fork();
if(pid == -1)
	{}
else if (pid == 0)
	{
	close(fd[0]);
	dup2(fd[1], 1);
	execlp(argv[3], argv[3], argv[4], NULL);
	}
else
	{
	close(fd[1]);
	dup2(fd[0], 0);
	execlp(argv[1], argv[1], argv[2], NULL);

	}
}
