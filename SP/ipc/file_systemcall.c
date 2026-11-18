#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
int main()


{
	int n;
	int fd;
	char buf [100]="HELLO jagadeesh";

	fd =open("data.txt",O_CREAT | O_WRONLY | O_RDONLY| O_TRUNC,0777);
	if(fd==-1){
        perror("open");
	return -1;
         
	}
	//n = read(fd,buf,sizeof(buf));
        write(fd,buf,sizeof(buf)-1);
	printf("data success\n");
	printf("message :%s \n",buf);
	close(fd);
	return 0;

}
