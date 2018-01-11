#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
int main(){
	char p[10];
	printf("Give me a path: \n");
	int n = scanf("%s",p);
	fflush(stdout);
        printf("%s",p);
	if (n != EOF) {
		printf("read: %s\n", p);
               	int slinked=symlink("nuevo.sym",p);
		if(slinked==0){
			int hlinked=link("nuevo.hard",p);
			if(hlinked==0)
				printf("done");
				//free(&p);
			else
				perror("link");
		}
		else
			perror("symlink");
           } else
		perror("scanf");
}
