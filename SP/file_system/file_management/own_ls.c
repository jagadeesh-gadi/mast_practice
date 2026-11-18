//creating the own ls command using the c program 
#include<stdio.h>
#include<dirent.h>
int main(){

	DIR *dir;
	struct dirent *entry;
	
	dir =opendir(".");

	if(dir == NULL){
		perror("error");
		return 1;
	}

	while((entry =readdir(dir))!=NULL){
         printf("%ld \t %s \t\n",entry->d_ino,entry->d_name);
	 
        // printf("INODE  : %ld \n",entry->d_ino);

		
	}

return 0;
}
