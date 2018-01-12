#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <string.h>
#include <stdio.h>
#include <unistd.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdlib.h>

/*
This file intends to read a serial's port interface (such as minicom) using sys/select.

It causes a EAGAIN error with the O_NONBLOCK flag, and reads local
(keyboard) echo without it. 

May be fixed with other flags, or try with dup or dup2.

*/


int main(int args, char * argv[]){
	fd_set rfds;
	struct timeval tv;
	if(args != 2){
		printf("Usage: ./dupSerial serialDevice (ie: ./dupSerial /dev/ttyUSB0\n");
		return -1;
	}
	int err,fd;
	fd=open(argv[1],O_RDWR|O_NONBLOCK);
	if (fd==-1){
		err=errno;
		printf("open %s\n",strerror(err));
		return -1;
	}
	FD_SET(fd,&rfds);
	tv.tv_sec = 5;
        tv.tv_usec = 0;
	int selected = select(fd+1, &rfds, NULL, NULL, &tv);
	if (selected == -1){
		err=errno;
		printf("select %s\n",strerror(err));
		return -1;
	}
        else if (selected){
 		printf("Data is available now.\n");
               /* FD_ISSET(0, &rfds) will be true. */
		if (FD_ISSET(fd,&rfds)){
			char readbuf[80];
			ssize_t readed=read(fd, readbuf, sizeof(readbuf));
			if (readed==-1){
				err=errno;
				printf("read %s\n",strerror(err));
				return -1;
			}
			printf("size of read buf %ld\n",readed);
			readbuf[readed]='\0';
			printf("%s",readbuf);
		}
	}
	return 0;
}
