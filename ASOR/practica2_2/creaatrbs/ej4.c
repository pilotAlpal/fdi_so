#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>



int main(){
	mode_t new_mask,oldmask;
	printf("Enter new umask :");
   	scanf("%u", &new_mask);
	oldmask=umask(new_mask);
	printf("Umask changed from %u\n to %u\n",oldmask,new_mask);
	char str1[15];mode_t mode;
	printf("Enter file name: ");
   	scanf("%s", str1);
	printf("Enter file mode: ");
	open(str1,O_RDWR|O_CREAT,465);
   	scanf("%u", &mode);
	printf("File %s created with mode %u\n", str1,mode);
}
