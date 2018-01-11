#include <stdlib.h>
#include <stdio.h>
#include <string.h>
int main(int args,char * argv[]){
	char buff[256];
	strcpy(buff,argv[1]);
	for (int i=2;i<args;i++){
		strcat(buff," ");
		strcat(buff,argv[i]);
		//printf("Argumento i%d, valor %s\n",i,argv[i]);
	}
	int sys=system(buff);
	printf("El programa %s  termino con codigo %d\n",buff,sys);
	return sys;
}
