#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
int main(int args,char * argv[]){
	int errn;
	int status = open(argv[1],O_CREAT,S_IRUSR|S_IXUSR|S_IRGRP);
	if(status==-1){
		errn=errno;
		printf("open: %s\n",strerror(errn));
		exit(EXIT_FAILURE);
	}
	printf("File %s created with 540 permisions\n",argv[1]);
	exit(EXIT_SUCCESS);
	
}
