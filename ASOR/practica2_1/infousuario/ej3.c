#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/utsname.h>
#include <stdlib.h>
int main(int args,char * argv){
	char buff[256];
	struct utsname reg;
	int stat=uname(&reg);
	char * home=getenv("HOME"); 
	stat=sprintf(buff,"real: %d\t effective: %d\t sys_name: %s\t node_name:%s\t home_path:%s",getuid(),geteuid(),reg.sysname,reg.nodename,home);
	printf("%s\n ",buff);
	return stat;
}
