#include <unistd.h>
#include <sys/select.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
int main(int args, char * argv[]){
	fd_set rfds;
        struct timeval tv;
        int selected;
	FD_ZERO(&rfds);
	int fd_tb1= open("/home/lucas/tuberia", O_NONBLOCK|O_RDWR);
	if (fd_tb1==-1){
		perror("open /home/lucas/tuberia");
		exit(EXIT_FAILURE);
	}
	int fd_tb2=open("tuberia2",O_RDWR|O_NONBLOCK);
	if (fd_tb2==-1){
                perror("open tuberia2");
                exit(EXIT_FAILURE);
        }
	printf("both pipes opened\n");
	FD_SET(fd_tb1,&rfds);
	FD_SET(fd_tb2,&rfds);
	tv.tv_sec = 5;
        tv.tv_usec = 0;
	char readbuf[256];
	selected = select(fd_tb1+1, &rfds, NULL, NULL, &tv);
	printf("%i\n",fd_tb1);
	printf("%i\n",fd_tb2);
	if (selected == -1)
               perror("select()");
        else if (selected){
 		printf("Data is available now.\n");
               /* FD_ISSET(0, &rfds) will be true. */
		int fdselected;
		if (FD_ISSET(fd_tb1,&rfds))
			fdselected=fd_tb1;
		else if (FD_ISSET(fd_tb2,&rfds))
			fdselected=fd_tb2;
		else{
			perror("who selected");
			exit(EXIT_FAILURE);
		}
 		ssize_t readed=read(fdselected, readbuf, sizeof(readbuf));
		printf("size of read buf %ld\n",readed);
		readbuf[readed]='\0';
		printf("%s",readbuf);
	}
	else
 		printf("No data within five seconds.\n");
        exit(EXIT_SUCCESS);
}
