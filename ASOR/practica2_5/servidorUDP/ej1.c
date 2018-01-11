#include <time.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netdb.h>
int  main(int args,char *argv[]){
	struct addrinfo hints,*res;
	struct sockaddr_storage cli;
	char buff[81],host[NI_MAXHOST],serv[NI_MAXSERV];
	hints.ai_flags= AI_PASSIVE;
	hints.ai_family=AF_UNSPEC;
	hints.ai_socktype=SOCK_DGRAM;
	hints.ai_protocol=0;
	getaddrinfo(argv[1],argv[2],&hints,&res);
	int sd=socket(res->ai_family,res->ai_socktype,0);
	bind(sd,(struct sockaddr *) res->ai_addr,res->ai_addrlen);
	freeaddrinfo(res);
	int quit=0;
	printf("start listening");
	while(!quit){
		socklen_t clen=sizeof(cli);
		int c = recvfrom(sd,buff,1,0,(struct sockaddr *) &cli,&clen);
		if (c==-1){
			perror("recvfrom");
			exit(EXIT_FAILURE);
		}
		c=getnameinfo((struct sockaddr *) &cli,clen,host,NI_MAXHOST,serv,NI_MAXSERV,NI_NUMERICHOST);
		if (c){
			perror("getnameinfo");
			exit(EXIT_FAILURE);			
		}
		printf("host:%s port:%s msg:%s\n",host,serv,buff);
		if(buff[0]=='t'){
			//struct tm *gmtime(const time_t *timep);
			printf("time requested");
			time_t tiemp=time(NULL);
			struct tm * stm = gmtime(&tiemp);
			sprintf(buff,"H:%d M:%d S:%d\n",stm->tm_hour,stm->tm_min,stm->tm_sec);
			c=14;
		}
		else if (buff[0]=='d'){
			printf("date requested");
			time_t tiemp=time(NULL);
			struct tm * stm = gmtime(&tiemp);
			sprintf(buff,"Year:%d Month:%d Day:%d\n",stm->tm_year,stm->tm_mon,stm->tm_mday);
			c=23;
		}
		else if (buff[0]=='q'){
			printf("quit requested");
			strcpy(buff,"Goodbye");
			c=7;
			quit=1;
		}
//		clen = sizeof(buff);
		buff[clen]='\0';
		printf("%s\n",buff);
		printf("%d clen\n",clen);
		sendto(sd, buff, c, 0, (struct sockaddr *) &cli, clen);
	}
	close(sd);
}
