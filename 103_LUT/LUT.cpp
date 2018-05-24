#include <limits.h>	//not needed - just for checking representation of char
#include <stdio.h> 
int arr[] = 	// 4B/elem
{	
	#include "consts.cpp" //this could be trivially replaced with getline()
};

char arrB[] = 	// 1B/elem
{	
	#include "consts.cpp"
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	printf( "%i : 0x%X\n",  arr[ 2 ], arr[ 2 ] );
	printf( "arr size : %lu\n", sizeof( arr ) );
	
	printf( "%i : 0x%X\n",  arrB[ 2 ], arrB[ 2 ] );
	printf( "arrB size : %lu\n", sizeof( arrB ) );
	printf("char poses higher information density at range of [%i,%i]\n", CHAR_MIN, CHAR_MAX );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
