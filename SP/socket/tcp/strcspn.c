#include<stdio.h>
#include<string.h>

int main(){

char str [] ="hello\n";

int n =strcspn(str,"\n");

printf("position :: %d\n",n);

printf("string :%s\n",str);
printf("string :%s\n",str);
str[n] = '\0';

printf("string :%s\n",str);


return 0;
}

