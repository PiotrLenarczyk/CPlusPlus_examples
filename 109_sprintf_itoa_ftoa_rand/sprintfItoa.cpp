#include <cstdarg>
#define CAST( destPtr ) ( destPtr )( const void* )
typedef unsigned uint;
typedef unsigned char byte;
uint i = 0x0;

char Representation[] 
#ifndef __cplusplus
	__attribute__((section(".text")))
#endif
						= "0123456789ABCDEF";
char buffer[50], *bufferPtr;
char *convert(unsigned int num, unsigned int base) 
{ 	bufferPtr = &buffer[49]; 
	*bufferPtr = '\0'; 
	do 
	{ 	*--bufferPtr = Representation[num%base]; 
		num /= base; 
	}while(num != 0); 
	return bufferPtr; 
};

unsigned strlen( char* buf )
{	unsigned n = 0x0;
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
	l = ( f - (float)( l ) ) * ( float )mul;
	fBuffConv = convert( l, 10 );
	while ( *fBuffPtr++ = *fBuffConv++ );
	*fBuffPtr = '\0';
	return &buffer[ 0 ];
};
char* cPtr, *rPtr;
char* itoa( int val, char *str, int base  )
{	if ( val < 0x0 )
	{	*str++ = '-';
		val = -val;
	};
	cPtr = convert( val, base );
	rPtr = cPtr;
	while( *str++ = *cPtr++ );
	return rPtr;
};

void sprintf( char* buf, char *c, ... )	//float must be passed via pointer!!!
{  	float f;
	char* tmpPtr;
	unsigned l, fPrecision = 0x2;
	int iTmp;
	iTmp=0x0;
    va_list lst;
    va_start( lst, c );
    while( *c != '\0' )
    { 	if( *c != '%' )
        {   *buf++ = *c++;
            if ( *c == '\0' ) *buf = '\0';
            continue;
        };
        c++;if( *c == '\0' ) { *buf = '\0'; break; };
format:
		switch( *c )
		{	default: 
				buf++;
				break;
			case 's':
				tmpPtr = va_arg( lst, char* );
				while( *buf++ = *tmpPtr++ );
				break;
			case 'c': 
				*buf++ = ( char )va_arg( lst, int );
				break;
			case '.':
				fPrecision = *++c - '0';
				c++;
				goto format;
				break;
			case 'f':
				tmpPtr = ftoa( *va_arg( lst, float* ), fPrecision );//only float pointer
				while( *buf++ = *tmpPtr++ );
				fPrecision = 0x2;
				break;
			case 'p':
			case 'u':
				tmpPtr = convert( va_arg( lst, unsigned ), 10 );
				while( *buf++ = *tmpPtr++ );
				break;
			case 'd':
			case 'i':
				iTmp = ( int )va_arg( lst, int );
				if ( iTmp < 0 ) { *buf++ = '-';iTmp = -iTmp; };
				tmpPtr = convert( iTmp, 10 );
				while( *buf++ = *tmpPtr++ );
				break;
			case 'x':
			case 'X':
				tmpPtr = convert( va_arg( lst, unsigned ), 16 );
				while( *buf++ = *tmpPtr++ );
				break;
		}; //switch (*c)
		buf--;
		c++;
    };//while(*c!=0x0)
    *++buf = 0x0;
    va_end( lst );
};

int seed;
void srand( int setSeed )
{	seed = setSeed;
};

#define RAND_A 1103515245		//glibc
#define	RAND_C 12345			//glibc
#define RAND_M ( 0x1 << 0x1F )	//glibc
int rand( void )	//linear congruential generator
{	return seed = ( (RAND_A * seed) + RAND_C ) % RAND_M;
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	

	char buf[ 0x32 ], itoaBuf[ 0x32 ], *iPtr;
	float a = 14.1f;
	unsigned b = a;
	char *kPtr = itoa( 67, buf, 16 );
	iPtr = itoaBuf;
	while( *iPtr++ = *kPtr++ )
	sprintf( buf, " aa " );
	sprintf( &buf[ strlen( buf ) ], "%s%s", "string", " second" );
	sprintf( &buf[ strlen( buf ) ], "tekst:%i:%u:%s[%.4f]%c end!%", -1, 0x211, "string ", &a, 'H' );
	
	srand( 0x11223344 );
	i = rand();
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
