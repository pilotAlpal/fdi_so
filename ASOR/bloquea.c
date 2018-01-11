#include <signal.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
void main(int args, char * argv[]){
	int errn;
	setenv("SLEEP_SECS","7",1);
	char * sleep_secs=getenv("SLEEP_SECS");
	if(sleep_secs==NULL){
		errn=errno;
		printf("getenv:\t%s\n",strerror(errn));
	}
	int sl_sc;
	printf("sleep secs:\t%s\n",sleep_secs);
	sscanf(sleep_secs,"%d",&sl_sc);
	sigset_t set;
	sigset_t pending;
	sigemptyset(&set);
	sigaddset(&set,SIGINT);
	sigaddset(&set,SIGTSTP);
	sigprocmask(SIG_BLOCK,&set,NULL);
	printf("going to sleep\n");
	sleep(sl_sc);
	sigpending(&pending);
	if(sigismember(&pending,SIGINT))
		printf("SIGINT\n");
	if(sigismember(&pending,SIGTSTP)){
		printf("SIGTSTP\n");
		sigemptyset(&set);
		sigaddset(&set,SIGINT);
		sigprocmask(SIG_BLOCK,&set,NULL);
	}
	printf("reanuda y muere\n");
}

