#include <cstdio> 
#include <cstdlib>
using namespace std;


//======================================================================
#define VARNAME				"i"
#define	BUCKETS_NO			0x3
#define MIN 				0x0
#define	MAX 				0x100
#define	ALL_BUCKETS_NO		( BUCKETS_NO + 1 )
#define BUCKETS_MAX			0x100
//even buckets switch generation
void generateSwitchBuckets( const void *const varName,	
							unsigned min,
							unsigned max
						  )
{	if ( BUCKETS_NO >= BUCKETS_MAX )	return;
	unsigned val[ ALL_BUCKETS_NO ];
	for ( int i = 0x0; i < ALL_BUCKETS_NO; i++ )
		val[ i ] = min + ( i * ( (max - min) / BUCKETS_NO ) );
	printf( "\nswitch( %s )\n{", (unsigned char *)varName );
	printf( "\tdefault:\n\t\t//====\n\t\tbreak;\n" );
	for( int i = 0x0; i < BUCKETS_NO; i++ )
	{	printf( "\tcase 0x%X ... 0x%X:\n\t\t//====\n\t\tbreak;\n",
				val[ i ],
				val[ i + 1 ] 
			  );
	};
	printf( "};\n" );
};

//======================================================================
#define rangesCount	0x3
typedef struct
{	unsigned start[ rangesCount ];
	unsigned end[ rangesCount ];
} Ranges_TypeDef;

//non-even buckets generation
void generateSwitchRange( const void *const varName, Ranges_TypeDef* ranges )
{	printf( "\nswitch( %s )\n{", (unsigned char *)varName );
	printf( "\tdefault:\n\t\t//====\n\t\tbreak;\n" );
	for( int i = 0x0; i < rangesCount; i++ )
	{	printf( "\tcase 0x%X ... 0x%X:\n\t\t//====\n\t\tbreak;\n",
				ranges->start[ i ],
				ranges->end[ i ] 
			  );
	};
	printf( "};\n" );
};

void randomize( Ranges_TypeDef *in )
{	for( int i = 0x0; i < rangesCount; i++ ) 
	{	in->start[ i ] 	= 0x100*i + rand() % 0x10;
		in->end[ i ] 	= (0x10 + 0x100*i + rand() % 0x10)%(0x100*(i+1));
		if( in->start[ i ] > in->end[ i ] )	//check whether start < end
		{	in->end[ i ] ^= in->start[ i ];	//XOR swap
			in->start[ i ] ^= in->end[ i ];
			in->end[ i ] ^= in->start[ i ];
		};
	};
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	generateSwitchBuckets( 	VARNAME,
							MIN,
							MAX
							);	


	Ranges_TypeDef ranges; randomize( &ranges );
	generateSwitchRange( "i", &ranges );
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%


