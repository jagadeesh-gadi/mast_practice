# include <signal.h>

#include<stdio.h>
void sighandler ( int signum )
{
printf ( "SIGINT received. Inside sighandler\n" ) ;
}
int main( )
{
signal ( SIGINT, ( void* ) sighandler ) ;
while ( 1 )
printf ( "Program Running\n" ) ;
return 0 ;
}