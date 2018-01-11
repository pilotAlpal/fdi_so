#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void main (int args, char **argv){

sigset_t set,set2;
sigset_t pending;

sigemptyset(&set);
sigaddset(&set, SIGINT);
sigaddset(&set, SIGTSTP);
sigprocmask(SIG_BLOCK, &set, &set2);
sleep(10);
sigpending(&pending);
if(sigismember(&pending, SIGINT)){
	printf("SIGINT\n");

}		
if(sigismember(&pending, SIGTSTP)){
	printf("SIGTSTP\n");
	sigprocmask(SIG_SETMASK, &set2, NULL);
	sleep(10);
	printf("after ctrl z");
}		

}
