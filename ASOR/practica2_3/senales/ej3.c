#include <signal.h>
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
int main(int args,char * argv[]){
	printf("Setting $SLEEP_SECS to %s\n",argv[1]);
	char  buf[256];
	strcpy(buf,"SLEEP_SECS=");
	strcat(buf,argv[1]);
	putenv(buf);
	sigset_t set;
	sigset_t pending;
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	sigaddset(&set,SIGTSTP);
	sigprocmask(SIG_BLOCK,&set,NULL);
	int sleep_secs=atoi(getenv("SLEEP_SECS"));
	sleep(sleep_secs);
	sigpending(&pending);
	if(sigismember(&pending,SIGINT))
		printf("SIGINT recieved");
	if(sigismember(&pending,SIGTSTP)){
		printf("SIGSTP recieved");
		printf("Unlocking SIGSTP, proccess will die");
		sigdelset(&set,SIGTSTP);
	}
}
