#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>


int main(int args, char * argv[]){
	int pipefd[2];
	int stat=pipe(pipefd);
	if (stat==-1) {
              	perror("pipe");
        	exit(EXIT_FAILURE);
	}
	pid_t pid=fork();
	if (pid<0){
		perror("fork");
        	exit(EXIT_FAILURE);
	}
	else if(pid>0){//parent
		close(pipefd[0]);
		dup2(1,pipefd[1]);
		execv(argv[1], &argv[1]);
		close(pipefd[1]);
	}
	else if (pid==0){//child
		close(pipefd[1]);
		dup2(0,pipefd[1]);
		execv(argv[1], &argv[1]);
		close(pipefd[0]);
	}
}
