#include<stdio.h>
#include<unistd.h>
#include<string.h>

int main(){

	int fd[2];
	pipe(fd);

	printf("read fd =%d\n",fd[0]);
         printf("write fd =%d\n",fd[1]);
return 0;
}
