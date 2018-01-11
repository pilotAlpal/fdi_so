#include <fcntl.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
void main(int args,char * argv[]){
	int en=0;
	char * fname = "tuberia";
	int fd= open(fname,O_WRONLY);
	if(fd==-1){
		en=errno;
		printf("open:\t%s\n",strerror(en));
		exit(EXIT_FAILURE);
	}
	int w=write(fd,argv[1],strlen(argv[1]));
	if(w==-1){
		en=errno;
		printf("write:\t%s\n",strerror(en));
		exit(EXIT_FAILURE);
	}
	exit(EXIT_SUCCESS);
}

