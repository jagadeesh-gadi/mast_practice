#include<stdio.h>
#include<string.h>
void test (){
    char buf[8];
    stpcpy(buf,"this string is too long");
    printf("%s\n",buf);
}
int main(){
 test();
 return 0;   
}