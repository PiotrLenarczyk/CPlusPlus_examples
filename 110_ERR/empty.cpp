#include <cstdlib> 
#include <cstdarg>
#define CAST( destPtr ) ( destPtr )( const void* )
using namespace std;
typedef __uint32_t u32;
typedef unsigned char byte;
typedef unsigned char u8;
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
};

int sstrlen( char* buf )
{	int n = 0x0;
	while( *buf++ )
		n++;
	return n;
};

char *fBuffPtr, *fBuffConv;
char* ftoa( float* fPtr, int precision )
{	float f = *fPtr;
	int l, mul = 0x1;
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
	unsigned aa=12;
	l = ( f - (float)( l ) ) * ( float )mul;
	fBuffConv = convert( l, 10 );
	while ( *fBuffPtr++ = *fBuffConv++ );
	return &buffer[ 0 ];
};

void itoa_half( char *buf, u32 val, u8 precision ) //max fixed 5 digits
{   u32 f1_10000 = ( 1 << 28 ) / 10000;
    u32 tmp = val * (( f1_10000 + 1 ) - ( val / 4 ));
    for( u8 i = 0; i < precision; i++ )
    {   int digit = ( int )( tmp >> 28 );
        buf[ i ] = '0' + ( char ) digit;
        tmp = ( tmp & 0x0fffffff ) * 10;
    };
};
void itoa( char *buf, u32 val )
{   itoa_half( &buf[ 0 ], val / 100000, 5 ); //high part
    itoa_half( &buf[ 5 ], val % 100000, 5 ); //low part
};
#define F_CONV_BUFSIZE 0x20
char convBuf[ F_CONV_BUFSIZE ]; 
void sprintf( char* buf, char *c, ... )	//float must be passed via pointer!!!
{  	float f;
	char* tmpPtr = convBuf;
	u32 l, rem;
	int iTmp;
	iTmp=0x0;
    va_list lst;
    va_start( lst, c );
    while( *c != '\0' )
    { 	if( *c != '%' )
        {   *buf++ = *c;
            c++;
            continue;        };
        c++;if( *c == '\0' )break;
		switch( *c )
		{	default: break;
			case 'c': 
				*buf++ = ( char )va_arg( lst, int );
				break;
			case 'f': //fixed float format %5.2f instead costly -> std::sprintf(buf, "%5.2f", floatValue)
				f = *va_arg( lst, float* );
				tmpPtr = ftoa( &f, 2 );
				//__BKPT
				while( *buf++ = *tmpPtr++ );
				break;
			case 'u':
				itoa( tmpPtr, ( u32 )va_arg( lst, u32 ) );
				while( *buf++ = *tmpPtr++ );
				tmpPtr = convBuf;
				for ( u8 i = 0x0; i < F_CONV_BUFSIZE; i++ ) convBuf[ i ] = 0x0;
				break;
			case 'd':
			case 'i':
				iTmp = ( int )va_arg( lst, int );
				if ( iTmp < 0 ) { *buf++ = '-';iTmp = -iTmp; };
				itoa( tmpPtr, iTmp );
				while( *buf++ = *tmpPtr++ );
				tmpPtr = convBuf;
				for ( u8 i = 0x0; i < F_CONV_BUFSIZE; i++ ) convBuf[ i ] = 0x0;
				break;
			case 'X':
				l = ( u32 )va_arg( lst, u32 );
				*buf++ = ( l >> 0 ) & 0xFF;
				*buf++ = ( l >> 8 ) & 0xFF;
				*buf++ = ( l >> 16 ) & 0xFF;
				*buf++ = ( l >> 24 ) & 0xFF;
				break;
		}; //switch (*c)
		c++;
    };//while(*c)
    *buf = '\0';
    va_end( lst );
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	char arr[ 0x100 ], *aPtr;
	itoa( arr, 154 );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
