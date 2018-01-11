#include <sys/sysmacros.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <time.h>
#include <stdlib.h>

int main(){
	char path;
	struct stat buf;
//	printf("Where is the file?\n");
	//if (stat(&path,&buf)!=0){
	//parametrizar path en vez de leer de /home siempre
	if (stat("/home",&buf)==-1){
		perror("Stat :");
		exit(EXIT_FAILURE);
	}
	printf("Major number is: %u\n and minor: %u\n",major(buf.st_dev),minor(buf.st_dev));
	printf("Inode number is: %ld\n",buf.st_ino);
	printf("File type: %u\n",buf.st_mode);
	printf("Time of last modification: %s\n",ctime(&buf.st_mtime));
	printf("Time of last status change: %s\n",ctime(&buf.st_ctime));
	printf("stat done\n");
	return 0;
}
