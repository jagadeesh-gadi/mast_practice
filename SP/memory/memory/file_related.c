// memory mapping using the file related thing 
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <time.h>

int main(){

int fd;
struct stat s ;
fd =open("data.txt",O_RDONLY);
if(fd ==-1){
    perror("open");
    return 1;
}
if(fstat(fd,&s)==-1){
    perror("fstat");
    close(fd);
    return 1;
}
printf("file size ::%ld\n",s.st_size);
printf("Inode number ::%ld\n",s.st_ino);
printf("perimmisions ::%o\n",s.st_mode & 0777);
printf("Owner UID ::%u\n",s.st_uid);
printf("Owner GID ::%u\n",s.st_gid);
printf("Device ID ::%ld\n",s.st_dev);
printf("last modification ::%d\n",s.st_mode);
printf("Last access time   : %s",
           ctime(&s.st_atime));

    printf("Last modification  : %s",
           ctime(&s.st_mtime));

    printf("Metadata change    : %s",
           ctime(&s.st_ctime));

    printf("File creation time  : ");
    #if defined(__linux__)
    // Linux stat structure does not expose st_birthtime
    // portably through the standard struct stat interface.
    printf("Not available through standard struct stat\n");
    #endif
// printf("%d\n",);
// printf("%d\n",);
// printf("%d\n",);'
 close(fd);
 return 0;
}
