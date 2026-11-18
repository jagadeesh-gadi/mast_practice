#include<stdio.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
int main(){

	int p1[2],p2[2];
	int num,result;
	pid_t pid;
	pipe(p1);//parent to child
	pipe(p2);//child to parent 

	pid =fork();

	if(pid >0)//parent process
	{
         close(p1[0]);//close the pipe 1 read process
         close(p2[1]);//close the pipe 2 write process
	 
	 printf("parent :enter n number : ");
	 scanf("%d",&num);

	 write(p1[1],&num,sizeof(num)); //send number to child
	 close(p1[1]);
	 read(p2[0],&result,sizeof(result));
	 printf("parent square received :: %d\n",result);
	 close(p1[0]);
	 wait(NULL);
	}
	else if(pid==0) {
       close(p1[1]);
       close(p2[0]);
       read(p1[0],&num,sizeof(num));
       result = num*num;
       printf("child :: received number :: %d\n",num);
       write(p2[1],&result,sizeof(result));
       close(p1[0]);
       close(p2[1]);
       exit(0);
 
	}
return 0;




}

