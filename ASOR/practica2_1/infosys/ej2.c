#include <sys/utsname.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>

int main(int args,char * argv[]){
	struct utsname buf;
	int stat=uname(&buf);
	if(stat==-1){
		int errn=errno;
		printf("uname: %s\n",strerror(errn));
		exit(EXIT_FAILURE);
	}
	printf("Sys name: %s\tnode name: %s\trelease: %s\tversion: %s\tmachine:%s",buf.sysname,buf.nodename,buf.release,buf.version,buf.machine);
	exit(EXIT_SUCCESS);
}
