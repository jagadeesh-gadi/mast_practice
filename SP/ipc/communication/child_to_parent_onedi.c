#include<unistd.h>
#include<stdio.h>
#include<sys/wait.h>
#include<stdlib.h>

int main()
{
int fd[2],n;
pipe(fd);

pid_t pid;
if(pipe(fd)==-1){
perror("pipe");
return -1;
}

pid = fork();
if(pid<0)
{
perror("fork");
return 1;
}
else if(pid>0)
{
	//parent process
close(fd[0]);
printf("parent :: enter a number :: ");
scanf("%d",&n);
write(fd[1],&n,sizeof(n));
close(fd[1]);
wait(NULL);

}
else{
//child process
	close(fd[1]);
	read(fd[0],&n,sizeof(n));
	printf("child process :: recived number :%d \n",n);
	close(fd[0]);
	exit(0);
 
}
return 0;




}
