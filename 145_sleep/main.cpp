#include <cstdio> 

#ifdef _WIN32
	#include <windows.h>
	#define sleep( t )	Sleep( t );
#else
	#include <unistd.h>
	#define sleep( t )	usleep((unsigned)t * 1000);
#endif

void foo( void )
{
	puts( "first message" ); 
	sleep( 2000 );
	puts( "second - delayed message" );
};//foo()

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	foo();
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
