#include <iostream>
#include <string>
#include <unistd.h>

using namespace std;
typedef uint32_t uint;
size_t i = 0;

int main( int argc, char *argv[] )
{
	string optOptSrc = "x:";
	int progOptions; int flagOptions = 0;
	while ( ( progOptions = getopt( argc, argv, optOptSrc.c_str() ) ) != -1 )
	{	flagOptions = 1;
		switch ( progOptions )
		{	case 'x':
				printf( "char[] option argument: %s\n", optarg );
				printf( "x option value: %i\n", atoi( optarg ) );
				break;
			case '?':
				if ( optopt == 'x' )
					fprintf( stderr, "Option -%c needs value!\n", optopt );
				else
					fprintf( stderr, "Unknown option -%c!\n", optopt );
				break;
			default:
				fprintf( stderr, "ERROR: other getopt!\n" );
				break;
		};
	}; if ( flagOptions == 0 ) fprintf( stderr, "Program started without arguments.\n" );

	puts( "" );
	return 0;
};
