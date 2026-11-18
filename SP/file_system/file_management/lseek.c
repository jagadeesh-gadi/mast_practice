#include<stdio.h>
#include<unistd.h>
#include<fcntl.h>
int main(){
int fd;
char buf[100];
fd=open("data.txt",O_RDONLY);
if(fd<0)
{
perror("failed");
return 1;
}
lseek(fd,6,SEEK_SET);
read(fd,buf,4);
printf("SEEK_SET :%s \n",buf);

lseek(fd,2,SEEK_CUR);
read(fd,buf,4);
printf("SEEK_CUR :%s\n",buf);

lseek(fd,-4,SEEK_END);
read(fd,buf,4);
printf("SEEK_END :%s\n",buf);
	close(fd);
	return 0;

}
