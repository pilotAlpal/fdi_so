#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>


int main(int args,char * argv[]){
	int err;
	if (args !=2){
		printf("bad usage: ie ./dup /dev/ttyUSB0");
		return -1;
	}
	int fd = open(argv[1],O_RDONLY|O_NONBLOCK);
	if (fd==-1){
		err=errno;
		printf("open %s\n",strerror(err));
		return -1;
	}
	dup2(fd,1);
	while(1){}
}
