#include <sys/types.h>
#include <sys/time.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <sys/select.h>

void main(int args,char * argv[]){
	struct addrinfo hints ,*res;
	struct sockaddr_storage cli;
	char host[NI_MAXHOST],serv[NI_MAXSERV],buf[81];
	hints.ai_flags=AI_PASSIVE;
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_STREAM;
	hints.ai_protocol=0;

        struct timeval tv;
        tv.tv_sec = 10;
        tv.tv_usec = 0;

	fd_set rfds;



	getaddrinfo(argv[1],argv[2],&hints,&res);
	int sd=socket(res->ai_family, res->ai_socktype, 0);
	bind(sd,(struct sockaddr *) res->ai_addr,res->ai_addrlen);
	freeaddrinfo(res);
	listen(sd,5);
	socklen_t clen=sizeof(cli);
	int cli_sd=accept(sd,(struct sockaddr*) &cli,&clen);

	FD_ZERO(&rfds);
      	FD_SET(0, &rfds);
       	FD_SET(cli_sd, &rfds);



	getnameinfo((struct sockaddr *) &cli,clen,host,NI_MAXHOST,serv,NI_MAXSERV,NI_NUMERICHOST);
	printf("%s %s\n",host,serv);
	int retval;
	while(1){
		retval = select(cli_sd+1, &rfds, NULL, NULL, &tv);
		
		if (FD_ISSET(0, &rfds)){
			printf("standard\n");
			fflush(0);
			FD_CLR(0,&rfds);
		}
		else if (FD_ISSET(cli_sd, &rfds)){
			int c=recv(cli_sd,buf,80,0);
			buf[c]='\0';
			printf("client:\t%s\n",buf);
		}

		else if(&rfds==NULL){
			printf("timeout expired\n");
		}
		FD_ZERO(&rfds);
        	FD_SET(0, &rfds);
        	FD_SET(cli_sd, &rfds);
		retval=0;
	}


}
