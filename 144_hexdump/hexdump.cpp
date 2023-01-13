#include <cstdio> 
#include <cstdlib>
#define _hexdump_data( s, n )										\
{																	\
	unsigned hexdump_line, hexdump_size, hexdump_rest, *p = 0, 		\
			 pval, hexdump_psize;									\
	unsigned char *c;												\
	hexdump_psize = (unsigned)sizeof( unsigned );					\
	hexdump_size = n / hexdump_psize;								\
	hexdump_rest = n - (hexdump_size * hexdump_psize);				\
	p = (unsigned*)s;												\
	for ( int i = 0; i < hexdump_size; i++ )						\
	{																\
		hexdump_line = i * hexdump_psize;							\
		c = ( unsigned char* )p;									\
		printf( "[%08u]\t", hexdump_line );							\
		printf( "{0x%02X, 0x%02X, 0x%02X, 0x%02X}\t", 				\
				(*p >>  0) & 0xFF,									\
				(*p >>  8) & 0xFF,									\
				(*p >> 16) & 0xFF,									\
				(*p >> 24) & 0xFF );								\
		printf( "0x%08X\t(%u)\t\"", *p, *p );						\
		for ( int ic = 0; ic < hexdump_psize; ic++ )				\
			if( (c[ic] < 0x20) || (c[ic] > 0x7E) )					\
				printf( "." );										\
			else 													\
				printf( "%c", c[ic] );								\
		printf( "\"\n" );											\
		p++;														\
	};																\
	if ( hexdump_rest != 0 )										\
	{																\
		if ( hexdump_size == 0 )									\
			hexdump_line = 0;										\
		else 														\
			hexdump_line += hexdump_psize;							\
		c = ( unsigned char* )p;									\
		printf( "[%08u]\t{", hexdump_line );						\
		for ( int i = 0; i < hexdump_rest; i++ )					\
		{															\
			printf( "0x%02X", (*p >> (i * 8)) & 0xFF );				\
			if ( i != (hexdump_rest - 1) )							\
				printf( ", " );										\
			else 													\
			{														\
				for ( int space = 0; 								\
						space < (hexdump_psize-hexdump_rest); 		\
						space++ )									\
					printf( "      " );								\
				printf( "}\t" );									\
			};														\
			pval |= ( (*p >> (i * 8)) & 0xFF ) << (i * 8);			\
		};															\
		switch( hexdump_rest )										\
		{															\
			case 1:													\
				printf( "      0x%02X\t", pval );					\
				break;												\
			case 2:													\
				printf( "    0x%04X\t", pval );						\
				break;												\
			case 3:													\
				printf( "  0x%06X\t", pval );						\
				break;												\
		};															\
		printf( "(%u)\t\"", pval );									\
		for ( int ic = 0; ic < hexdump_rest; ic++ )					\
			if( (c[ic] < 0x20) || (c[ic] > 0x7E) )					\
				printf( "." );										\
			else 													\
				printf( "%c", c[ic] );								\
		printf( "\"\n" );											\
	};																\
};
#define hexdump_data( s )		printf( "hexdump( %s ):\n", #s );	\
								_hexdump_data( s, sizeof( s ) );
#define hexdump_dataN( s, n )	printf( "hexdump( %s )[%u]:\n", 	\
										#s, n );					\
								_hexdump_data( s, n );
#define hexdump_data_n( s, n )	hexdump_dataN( s, n );
#define hexdump( hex_filename, size )								\
{																	\
	FILE *hexfile_pFile;											\
	unsigned hexfile_psize, hexfile_pread;							\
	unsigned char *buf = 0;											\
	hexfile_pFile = fopen( hex_filename, "rb" );					\
	if ( hexfile_pFile == NULL )									\
		goto hexdump_terminate;										\
	hexfile_psize = size;											\
	buf = (unsigned char*)malloc( hexfile_psize );					\
		hexfile_pread = fread( buf, 1, hexfile_psize, 				\
								hexfile_pFile );					\
		printf( "hexdump( \"%s\" )[%u]:\n", hex_filename, size );	\
		_hexdump_data( buf, hexfile_psize );						\
	free( buf );													\
	fclose( hexfile_pFile );										\
hexdump_terminate:													\
	hexfile_pFile = NULL;											\
};
#define hexdump_full( fullhex_filename )							\
{																	\
	FILE *fullhex_pFile;											\
	unsigned fullhexfile_psize; 									\
	fullhex_pFile = fopen( fullhex_filename, "rb" );				\
	if ( fullhex_pFile != NULL )									\
	{																\
		fseek( fullhex_pFile, 0, SEEK_END );						\
		fullhexfile_psize = ftell( fullhex_pFile );					\
		rewind( fullhex_pFile );									\
		hexdump( fullhex_filename, fullhexfile_psize );				\
		fclose( fullhex_pFile );									\
	};																\
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( int argc, char* argv[] )
{	
	unsigned char in[] = { 0x00, 0x11, 0x22, 0x33, 0x44, 0x55, 0x66, 0x77, 0x88 };
	hexdump_data( in );
	puts("");
	
	hexdump_data_n( in, 3 );
	puts("");
	
	printf( "Self-program hexdump \"%s\":\n", argv[0] );
	hexdump( argv[ 0 ], 11 );
	puts("");
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
