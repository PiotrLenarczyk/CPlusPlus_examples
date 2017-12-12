#include <iostream>
#include <string.h>

using namespace std;
typedef uint32_t uint;
size_t i = 0;

int main( void )
{
	string s = "start 1 2"; 
	char separators[] = "  \n"; 	//separator[0]=" "; [1]=" ";[2]="\n"
	uint sepN = 3;					//number of separators
	uint arrN = 100;				//max string size
	char t[ sepN ][ arrN ]; strcpy( t[ 0 ], s.c_str());
	char* cPtr = 0; 
	cPtr = strtok( t[ 0 ], separators );
	i = 0;
	while ( cPtr != NULL )
	{
		if ( i == 0 ) strcpy( t[ 0 ], cPtr );
		if ( i == 1 ) strcpy( t[ 1 ], cPtr );
		if ( i == 2 ) strcpy( t[ 2 ], cPtr );
		cPtr = strtok( NULL, separators );
		i++;
	};
	printf( "original : %s\nt[0] : %s\nt[1] : %s\nt[2] : %s\n", s.c_str(), t[ 0 ], t[ 1 ], t[ 2 ] );
	
	return 0;
}
