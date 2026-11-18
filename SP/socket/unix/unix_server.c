#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<sys/un.h>
int main(){

	int server_fd,client_fd;
	struct sockaddr_un addr;
	char buffer[100];

	server_fd = socket(AF_UNIX,SOCK_STREAM,0);
           
	//configure server address
	memset(&addr,0,sizeof(addr));
	addr.sun_family = AF_UNIX;
	strcpy (addr.sun_path,"/tmp/socket");
        
	//unlink remove old socket 
	unlink("/tmp/socket");
   
	//bind socket
	bind(server_fd,(struct sockaddr*)&addr,sizeof(addr));
   
	//listen from client
	listen(server_fd,5);

	printf("server is waiting for client......\n");

	//accept client connections
	client_fd = accept(server_fd,NULL,NULL);


	printf("client connect\n");
	
	while(1){
        //recive client message
	memset(buffer,0,sizeof(buffer));

	int n = recv(client_fd,buffer,sizeof(buffer)-1,0);
	
	if(n<=0)
		break;

	printf("client :: %s\n",buffer);
	if(strcmp(buffer,"exit")==0)
		break;

	//get server message
	printf("server :: ");

	fgets(buffer,sizeof(buffer),stdin);
	buffer[strcspn(buffer,"\n")]='\0';

	//send server message
	send(client_fd,buffer,strlen(buffer),0);

	if(strcmp(buffer,"exit")==0)
		break;

	}

	close(client_fd);
	close(server_fd);
	unlink("/tmp/socket");
	printf("chart ended\n");
    
return 0;
}
