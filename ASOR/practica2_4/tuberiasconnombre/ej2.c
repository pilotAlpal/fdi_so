#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>

int main(int args, char * argv[]){
	int fd=open("/home/lucas/tuberia",O_WRONLY);
	if(fd==-1){
		perror("open");
		exit(EXIT_FAILURE );
	}
	ssize_t written= write(fd,argv[1], sizeof(argv[1]));
	int clo=close(fd);
	if(clo==-1){
		perror("close");
		exit(EXIT_FAILURE);
	}
	return clo;
}
