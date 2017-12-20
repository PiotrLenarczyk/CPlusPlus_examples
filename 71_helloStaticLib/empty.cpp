/*
 http://www.yolinux.com/TUTORIALS/LibraryArchives-StaticAndDynamic.html
 https://randu.org/tutorials/c/libraries.php
*/ 
#include <iostream>
#include <string>

using namespace std;
typedef uint32_t uint;
size_t i = 0;

//Library header file basicly:
int helloLib( void );
int helloPrint( char* arrIn, uint sizeArrIn );
int helloPrint( string arrIn );

int main( void )
{
	int res = helloLib();
	
	char buf[ 25 ] = "some input";
	helloPrint( buf, 25 );
	string a = buf;
	helloPrint( a );
	
	return 0;
}
