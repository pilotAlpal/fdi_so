#include <sys/time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
int max(int a,int b){
	if(a>b) return a;
	return b;
}

void main(int args,char * argv[]){
	int en;
	char buf[256];
	char * fifo1="tuberia",* fifo2="beyoce";
	int fd1 = open(fifo1,O_RDWR|O_NONBLOCK),fd2=open(fifo2,O_RDWR|O_NONBLOCK);
	fd_set rfds;
	FD_ZERO(&rfds);
        FD_SET(fd1, &rfds);
        FD_SET(fd2, &rfds);
	struct timeval tv;
	tv.tv_sec = 15;
        tv.tv_usec = 0;
	int retval=select(max(fd1,fd2)+1, &rfds, NULL, NULL, &tv);
	if (retval==-1){
		en=errno;
		printf("select:\t%s\n",strerror(en));
		exit(EXIT_FAILURE);
	}
	else if(retval==0)
		printf("Time wait expired\n");
	else{
		int bs;
		if(FD_ISSET(fd1, &rfds)){
			bs=read(fd1,buf,256);
			printf("recieved:%s\n",buf);
		}
		else if(FD_ISSET(fd2, &rfds)){
			bs=read(fd2,buf,256);
			printf("%s wrote:\t",fifo2);
		}
		else{
			printf("select:Who is ready?\n");
			exit(EXIT_FAILURE);
		}
		buf[bs]='\0';
		printf("recieved:%s\n",buf);
	}
}
