#include <unistd.h>
#include <fcntl.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void main(int args,char * argv[]){
	int hp[2],ph[2];
	char pa_buf[2],ch_buf[80];
	pipe(hp);
	pipe(ph);
	pid_t pid=fork();
	if(pid==0){//child
		int n_rec=0;
		while(n_rec<10){
			int by_re=read(ph[0],ch_buf,80);
			ch_buf[by_re]='\0';
			printf("Child:%d Bytes recieved from parent.\n",by_re);
			printf("Child:Msg:\t%s\n",ch_buf);
			printf("Child:\tRemaining:%i\n",10-n_rec);
			if(n_rec<9)
				write(hp[1],"l",1);
			else write(hp[1],"q",1);
			n_rec++;
		}
	}
	else{//parent
		int exit=0;
		while(!exit){
			char input[80];
			scanf("%s",input);
			write(ph[1],input,strlen(input));
			printf("Parent:Message: <<%s>> sent to child\n",input);
			printf("Parent:Waiting for confirmation\n");
			read(hp[0],pa_buf,2);
			printf("Parent:confirmation recieved from child %s\n",pa_buf);
			if(pa_buf[0]=='q')
				exit=1;
		}
	}
}
