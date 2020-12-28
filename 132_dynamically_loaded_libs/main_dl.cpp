//dynamically linked cosine function, and calculation of cos(2)

#include <stdlib.h>
#include <stdio.h>
#include <dlfcn.h>

int main( int argc, char *argv[] ) 
{
	void *handle;
	double (*cosine)(double);
	char *error;

	handle = dlopen( "/lib/x86_64-linux-gnu/libm.so.6", RTLD_LAZY );
	if( !handle )
	{	fputs( dlerror(), stderr );
		exit( 1 );
	};
	
	//cast function pointer, and load function cos
	cosine = (double(*)(double))dlsym( handle, "cos" );
	if ( (error = dlerror()), error != NULL )
	{	fputs( error, stderr );
		exit( 1 );
	};

	//get returned function value
	printf( "Calculated, dynamically linked cos(2) : %f\n", 
			(*cosine)(2.0f) ) ;

	dlclose( handle );
	return 0x0;
};

