#include <sched.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
int main(int args,char * argv[]){
	pid_t target;
	if (args==1)
		target=getpid();
	else if (args==2)
		target =atoi(argv[1]);
	else {
		perror("More than 2 args");
		exit(-1);
	}
	int politica=sched_getscheduler(target);
	printf("La politica es : %d\n",politica);
	int prioMax=sched_get_priority_max(politica);
	printf("La prioridad maxima para dicha politica es: %d\n",prioMax);
	int prioMin=sched_get_priority_min(politica);
        printf("La prioridad minima para dicha politica es: %d\n",prioMin);

}
