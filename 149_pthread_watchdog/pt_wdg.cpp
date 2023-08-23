#include <cstdio> 
#include <pthread.h>
#include <unistd.h>


#define FUNC_CAST(s)	(void*(*)(void*))&s
int foo_completed = 0;
void* foo( void* in )
{
	foo_completed = false;
		puts( "\t..foo()..." );
		sleep(1);
	foo_completed = true;
	return NULL;
};//foo()


//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	
	int st;
	pthread_t t_async;
	st = pthread_create( &t_async, NULL, FUNC_CAST(foo), NULL );
		while( foo_completed != true )
		{
			puts( "foo() is executing - WDG functionality here" );
			usleep( 200 * 1000 );
		};
		if (foo_completed)
			puts( "\tfoo() completed!" );
	pthread_join( t_async, NULL );

	puts( "...program terminated..." );
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
