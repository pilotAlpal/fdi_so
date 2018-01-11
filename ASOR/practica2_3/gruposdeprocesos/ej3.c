#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <sys/wait.h>

int main(int args, char * argv[]){
	pid_t target;
	if(args==1)
		target=getpid();
	else if(args==2)
		target=atoi(argv[1]);
	else{
		perror("More than 2 arguments");
		exit(-1);
	}
	pid_t pid = fork();
	if (pid==0){//hijo
		pid_t sid=setsid();
		if (sid < 0) {
			perror( "No fue posible crear una nueva sesión");
			exit(-1);
		}
		printf("Session changed to %u\n",sid);
		if ((chdir("/tmp")) < 0) {
			perror("No fue posible cambiar el directorio de trabajo a /tmp\n");
			exit(-1);
		}
		printf("wdir changed to /tmp\n");
		printf("My pid is: %u, my parent's: %u, my session's id: %u and my grups's%u\n",getpid(),getppid(),sid,getgid());
		printf("Child exiting with code 0");
		exit(0);
	}
	else if(pid>0){
		int wstatus;
		wait(&wstatus);
		printf("Parent exiting with code %d\n",wstatus);
		exit(wstatus);
	}
}
