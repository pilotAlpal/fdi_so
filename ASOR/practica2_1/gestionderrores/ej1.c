#include <sys/types.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int args,char * argv[]){
	int status = setuid(0);
	if (status==-1){
		int errn=errno;
		perror("setuid");
		printf("%s\n",strerror(errn));
		exit(EXIT_FAILURE);
	}
	printf("setuid finished with no errors");
	exit(EXIT_SUCCESS);
}
