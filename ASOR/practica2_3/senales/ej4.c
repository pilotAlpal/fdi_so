#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
static volatile int cSTP=0;
static volatile int cINT=0;

void handler(int signal){
	if(signal==SIGTSTP)
		cSTP++;
	else if(signal==SIGINT)
		cINT++;
}


int main(int args, char * argv[]){
	struct sigaction act;
	act.sa_handler=handler;
	act.sa_flags=0;
	sigaction(SIGTSTP,&act,NULL);
	sigaction(SIGINT,&act,NULL);
	while((cINT+cSTP)<10){}
	printf("SIGINT was recieved: %d times, and SIGTSTP: %d times\n",cINT,cSTP);
	exit(0);
}
