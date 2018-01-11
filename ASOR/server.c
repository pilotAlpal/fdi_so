#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
void main(int args,char * argv[]){
  struct addrinfo hints,*res;
  struct sockaddr_storage cli;
  char host[NI_MAXHOST],serv[NI_MAXSERV];
  char buf[81];

  hints.ai_flags=AI_PASSIVE;
  hints.ai_family=AF_UNSPEC;
  hints.ai_socktype=SOCK_STREAM;
  hints.ai_protocol=0;

  getaddrinfo(argv[1],argv[2],&hints,&res);
  int sd = socket(res->ai_family, res->ai_socktype, 0);
  bind(sd,(struct sockaddr *)res->ai_addr,res->ai_addrlen);

  freeaddrinfo(res);

  listen(sd, 5);
  while (1) {
    socklen_t clen = sizeof(cli);
    int cli_sd = accept(sd,(struct sockaddr *)&cli,&clen);
    getnameinfo((struct sockaddr *) &cli, clen, host,
    NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST);
    printf("%s %s\n", host, serv);
    int c = recv(cli_sd, buf, 80, 0);
    int i=0;
    char * aux;
    aux=strtok(buf," ");
    while(aux!=NULL){
      i++;
      aux=strtok(NULL," ");
    }
    char *cmd[i+1];
    i=0;
    cmd[i]=strtok(buf," ");
    while(aux!=NULL){
      i++;
      cmd[i]=strtok(NULL," ");
    }
    cmd[i+1] = NULL;
    dup2(cli_sd,STDOUT_FILENO);
    /*buf[c] = '\0';
    send(cli_sd, buf, c, 0);*/
    execvp(cmd[0],cmd);
    close(cli_sd);
  }
close(sd);
}
