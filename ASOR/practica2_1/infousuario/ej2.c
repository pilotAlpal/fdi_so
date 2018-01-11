#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
int main(int args,char * argv){
	char buff[256];
	int stat=sprintf(buff,"real: %d\teffectiva: %d",getuid(),geteuid());
	printf("%s\n",buff);
	return stat;
}
