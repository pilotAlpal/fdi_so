#include <time.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <stdio.h>
int main(int args,char * argv[]){
	time_t tim=time(NULL);
	if(tim==(time_t)-1){
		int errn=errno;
		printf("time: %s\n",strerror(errn));
		exit(EXIT_FAILURE);
	}
	printf("Human readable time %s\n",ctime(&tim));
	exit(EXIT_SUCCESS);
}
