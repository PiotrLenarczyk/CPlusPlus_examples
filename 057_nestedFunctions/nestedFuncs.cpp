#include <stdio.h>

//heap functions pointers
float firstFun( float &fIn );
float secondFun( float &fIn );

int main( void )
{
	float a = 1.0f;
	return printf( "a = %f\n", firstFun( a ) );
}

float firstFun( float &fIn )  { fIn++; return secondFun( fIn ); };
float secondFun( float &fIn ) { fIn++; return fIn; };
