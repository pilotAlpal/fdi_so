#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

void main(int args,char * argv[]){
	struct addrinfo hints, *res;
	struct sockaddr_storage cli;
	char host[NI_MAXHOST],serv[NI_MAXSERV];
	char buff[81];
	int errn;
	hints.ai_flags=AI_PASSIVE;
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_protocol=0;

	int stat=getaddrinfo(argv[1],argv[2],&hints,&res);
	if(stat!=0){
		errn=errno;
		printf("getaddrinfo: %s\n",strerror(errn));
		freeaddrinfo(res);
		exit(EXIT_FAILURE);
	}
	int sd=socket(res->ai_family,res->ai_socktype,0);
	if(sd==-1){
		errn=errno;
		printf("socket: %s\n",strerror(errn));
		freeaddrinfo(res);
		exit(EXIT_FAILURE);
	}
	stat=bind(sd,(struct sockaddr *) res->ai_addr,res->ai_addrlen);
	if (stat!=0){
		errn=errno;
		printf("bind: %s\n",strerror(errn));
		freeaddrinfo(res);
		exit(EXIT_FAILURE);		
	}
	freeaddrinfo(res);
	stat=listen(sd,5);
	if (stat!=0){
                errn=errno;
                printf("listen: %s\n",strerror(errn));
                exit(EXIT_FAILURE);             
        }
	listen(sd,5);
	printf("listening\n");
	int finished=0;
	while(!finished){
		socklen_t clen=sizeof(cli);
		int cli_sd =  accept(sd,(struct sockaddr *) &cli,&clen);
		if (cli_sd==-1){
                	errn=errno;
                	printf("accept: %s\n",strerror(errn));
                	exit(EXIT_FAILURE);             
        	}
		stat=getnameinfo((struct sockaddr *) &cli,clen,host,NI_MAXHOST,serv,NI_MAXSERV,NI_NUMERICHOST);
		if (stat!=0){
                	errn=errno;
                	printf("getnameinfo: %s\n",strerror(errn));
                	exit(EXIT_FAILURE);             
        	}
		printf("host: %s, port: %s\n",host,serv);
		int stop=0;
		while(!stop){
			int c = recv(cli_sd,buff,80,0);
			if (c==0)
				stop=1;
			if(!stop){
				buff[c]='\0';
				printf("recieved: %s\n",buff);
				send(cli_sd,buff,c,80);
			}
			else
				printf("Client aborted\n");
		}
		close(cli_sd);
		printf("host: %s, port: %s gone\n",host,serv);
		finished=1;
	}
	close(sd);
}
