#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>


int main(int args,char *argv[]){
	struct addrinfo hints, *res;
	struct sockaddr_storage cli;
	char host[NI_MAXHOST], serv[NI_MAXSERV];
	char buf[81];
	hints.ai_flags = AI_PASSIVE;
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = 0;
	getaddrinfo(argv[1], argv[2], &hints, &res);
	int sd = socket(res‐>ai_family, res‐>ai_socktype, 0);
	bind(sd, (struct sockaddr *) res‐>ai_addr, res‐>ai_addrlen);
	freeaddrinfo(res);
	while (1) {
		socklen_t clen = sizeof(cli);
		int c = recvfrom(sd,buf,80,0,(struct sockaddr *) &cli, &clen);
		buf[c] = '\0';
		sendto(sd, buf, c, 0, (struct sockaddr *) &cli, clen);
	}
	close(sd);
}

