#include <sched.h>
#include <unistd.h>
#include <stdio.h>
void main(int args,char * argv[]){
	pid_t pid=getpid();
	int policy=sched_getscheduler(0);
	printf("Process : %d\t,policy:%d\n",pid,policy);
	int max_p=sched_get_priority_max(policy);
	int min_p=sched_get_priority_min(policy);
	printf("The maximum priority for policy %d is %i, and the minumum is %i\n",policy,max_p,min_p);
	while(1){}
}
