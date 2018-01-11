#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>

void main(int args,char * argv[]){
	int pipeD[2],en;
	int stat=pipe(pipeD);
	if (stat==-1){
		en=errno;
		printf("pipe:\t%s\n",strerror(en));
		exit(EXIT_FAILURE);
	}
	pid_t pid=fork();
	if (pid<0){
		en=errno;
		printf("fork\t%s\n",strerror(en));
		exit(EXIT_FAILURE);
	}
	else if(pid==0){//child
		close(pipeD[1]);
		dup2(pipeD[0],0);
		execlp(argv[3],argv[3],argv[4],(char *)NULL);
	}
	else{//parent
		close(pipeD[0]);
		dup2(pipeD[1],1);
		execlp(argv[1],argv[1],argv[2],(char *)NULL);
	}
}

