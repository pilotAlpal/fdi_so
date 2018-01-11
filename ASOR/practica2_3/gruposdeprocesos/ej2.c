#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
int main(int args, char * argv[]){
	pid_t pid=getpid();
	pid_t ppid=getppid();
	printf("My pid is: %u, and my parent's: %u\n",pid,ppid);
	gid_t gid=getgid();
	gid_t egid=getegid();
	printf("My group's id is: %u, and my parent's: %u\n",gid,egid);
	pid_t sid=getsid(pid);
	printf("My session's id is:%d\n",sid);
	uid_t euid=geteuid();
	uid_t uid=getuid();
	printf("My effective usser id is: %u, and real is : %u",euid,uid);
	return 0;
}
