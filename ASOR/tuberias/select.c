#include <sys/types.h>
#include <sys/stat.h>
#include <sys/select.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
void main(int args,char  * argv[]){
	char nam_t1[]="tuberia1";
	char nam_t2[]="tuberia";
	char buf[80];
	int sread;
	int fd1=open(nam_t1,O_RDWR|O_NONBLOCK);
	int fd2=open(nam_t2,O_RDWR|O_NONBLOCK);
	fd_set rfds;
        struct timeval tv;
        int retval;
	FD_ZERO(&rfds);
        FD_SET(fd1, &rfds);
        FD_SET(fd2, &rfds);
	tv.tv_sec = 15;
        tv.tv_usec = 0;
	retval = select(fd2+1, &rfds, NULL, NULL, &tv);
	if(retval==0)
		printf("15 s timeval expired");
	else{
		if(FD_ISSET(fd1, &rfds)){
			printf("%s suffered changes\n",nam_t1);
			sread=read(fd1,buf,80);
			buf[sread]='\0';
			printf("%s",buf);
		}
		else if(FD_ISSET(fd2, &rfds)){
			printf("%s suffered changes\n",nam_t2);
			sread=read(fd2,buf,80);
			buf[sread]='\0';
			printf("%s",buf);
		}

	}


}
