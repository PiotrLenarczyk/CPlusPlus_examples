#include <cstdio> 
#define CAST( destPtr ) ( destPtr )( const void* )
using namespace std;
typedef __uint32_t uint;
typedef unsigned char byte;
uint i = 0x0;

char Representation[]= "0123456789ABCDEF";
char buffer[50], *bufferPtr;
char *convert(unsigned int num, int base) 
{ 	bufferPtr = &buffer[49]; 
	*bufferPtr = '\0'; 
	do 
	{ 	*--bufferPtr = Representation[num%base]; 
		num /= base; 
	}while(num != 0); 
	return bufferPtr; 
}

int sstrlen( char* buf )
{	int n = 0x0;
	while( *buf++ )
		n++;
	return n;
};

char *fBuffPtr, *fBuffConv;
char* ftoa( float f, int precision )
{	int l, mul = 0x1;
	while( precision-- )
		mul *= 0xA;
	fBuffPtr = &buffer[ 0 ];
	l = ( int )f;
	if ( l < 0 )
	{	*fBuffPtr++ = '-';
		l = -l;
		f = -f;
	};
	fBuffConv = convert( l, 10 );
	while ( *fBuffPtr++ = *fBuffConv++ ); fBuffPtr--;
	*fBuffPtr++ = '.';
	l = ( f - float( l ) ) * ( float )mul;
	fBuffConv = convert( l, 10 );
	while ( *fBuffPtr++ = *fBuffConv++ );
	return &buffer[ 0 ];
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	char * tmp = ftoa( -11.42f, 3 );
	printf( "%s\n", tmp );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
