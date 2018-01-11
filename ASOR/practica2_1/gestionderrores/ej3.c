#include <string.h>
#include <stdio.h>
int main (int args,char * argv[]){
	const int MAX_ERRORES = 255;
	for (int i=0;i<MAX_ERRORES;i++){
		printf("El error numero %d es: %s\n",i,strerror(i));
	}
}
