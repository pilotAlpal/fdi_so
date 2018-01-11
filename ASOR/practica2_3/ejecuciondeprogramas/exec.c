#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>


int main(int args,char * argv[]){
	pid_t pid=fork();
	if (pid==0){ //hijo
		//execv(argv[1],&argv[1]);
		execv("echo",&argv[1]);
	}
	else if (pid>0){//padre
		int stat;
		printf("Parent waiting child");
		wait(&stat);
		printf("Parent waked by child, exiting with code %d\n",stat);
		return stat;
	}
}
