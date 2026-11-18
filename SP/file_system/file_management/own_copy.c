//create an own copy command for us 
#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(int argc , char *argv[]){
int n, fd1,fd2;
char buf[100];
if(argc !=3)
{
	printf("usage :: ./mycp souce destination\n");
	return 1;
}
fd1 =open(argv[1],O_RDONLY);
if(fd1<0){
	perror("souce open ");
	return 1;
}

fd2 =open(argv[2],O_WRONLY | O_CREAT|O_TRUNC,0644);
if(fd2<0){
	perror("destintion failed");
	return 1;
}

while((n = read(fd1, buf, sizeof(buf))) > 0){
	write(fd2,buf,n);
}
printf("files copies sussesfully\n");
close(fd1);
close(fd2);
return 0;
}
