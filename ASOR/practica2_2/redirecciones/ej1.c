#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
int main(int args, char* argv []){
	int fd=open(argv[1],O_RDWR|O_CREAT|O_TRUNC,700);
	if (fd==-1){
		perror("open");
		exit(-1);
	}
	dup2(fd,1);
	printf("Donde lo imprimo?");
	return 0;
}
