#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>


void main(int args,char * argv[]){
	struct addrinfo hints,*res,*rp;
	struct sockaddr_storage s_addr;
	hints.ai_family = AF_UNSPEC;    /* Allow IPv4 or IPv6 */
//        hints.ai_flags = AI_PASSIVE;    /* For wildcard IP address */
//        hints.ai_protocol = 0;          /* Any protocol */
	char host_name[NI_MAXHOST],serv_name[NI_MAXSERV];
	printf("Requesting directions for %s\n",argv[1]);
	int stat = getaddrinfo(argv[1], NULL ,NULL,&res);
	for (rp = res; rp != NULL; rp = rp->ai_next){
		stat=getnameinfo(rp->ai_addr,rp->ai_addrlen,host_name,NI_MAXHOST,serv_name, NI_MAXSERV, NI_NUMERICHOST);
		printf("host:%s\ttype:%i\tfamily:%i\n",host_name,rp->ai_socktype,rp->ai_family);
	}
	freeaddrinfo(res);
	exit(EXIT_SUCCESS);
}
