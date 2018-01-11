#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

int main(int args, char * argv[0]){
	struct addrinfo * res,*rp,hints;
	struct sockaddr  addr;
	char hbuf[NI_MAXHOST],sbuf[NI_MAXSERV];
	hints.ai_family=AF_INET6/*|AF_INET*/;
	hints.ai_protocol=0;
	hints.ai_socktype=0;
	hints.ai_flags=/*AI_NUMERICHOST|*/AI_ADDRCONFIG|AI_V4MAPPED|AI_ALL;
	int stat=getaddrinfo(argv[1],NULL,&hints,&res);
//	int stat=getaddrinfo(argv[1],NULL,NULL,&res);
	if (stat!=0){
		int errn=errno;
		printf("getaddrinfo: %s\n",strerror(errn));
		exit(EXIT_FAILURE);
	}
	socklen_t clen=sizeof(addr);
	for (rp = res; rp != NULL; rp = rp->ai_next){
		int s=getnameinfo(rp->ai_addr, rp->ai_addrlen, hbuf, NI_MAXHOST, sbuf,NI_MAXSERV,NI_NUMERICHOST);
		if (s==0)
 			printf("host=%s, serv=%s, socktype: %d\n", hbuf, sbuf,rp->ai_socktype);
		else{
			perror("getnameinfo");
			printf("%s\n",gai_strerror(s));
			exit(EXIT_FAILURE);
		}
	}
}
