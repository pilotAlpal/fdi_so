#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
int main (int args,char * argv[]){
	int pds_p_h[2];
	int pds_h_p[2];
	int stat=pipe(pds_p_h);
	if(stat==-1){
		perror("pipe");
		exit(EXIT_FAILURE);
	}
	stat=pipe(pds_h_p);
	if(stat==-1){
                perror("pipe");
                exit(EXIT_FAILURE);
        }
	pid_t pid=fork();
	if(pid<0){
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if(pid==0){//child
		int msgs=0;
		char *cbuff;
		while(msgs<10){
			ssize_t rea=read(pds_p_h[0],cbuff,sizeof(&cbuff));
			printf("%s\n",cbuff);
			sleep(1);
			ssize_t writ=write(pds_h_p[1],"l",1);
			msgs++;
		}
		ssize_t writ=write(pds_h_p[1],"q",1);
		exit(EXIT_SUCCESS);
	}
	else if (pid>0){//parent
		int stop=0;
		while(stop==0){
			char *buf;
			ssize_t readed=read(0, buf, sizeof(&buf));
			ssize_t written=write(pds_p_h[1],&buf,readed);
			readed=read(pds_p_h[0],buf,1);
			if (buf[0]=='q')
				stop=1;
		}
		exit(EXIT_SUCCESS);
	}

}
