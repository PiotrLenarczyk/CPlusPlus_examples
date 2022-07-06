#include <cstdio>
#include <cstdlib>
#include <cstring>

#define ARRSIZE	0x20

/* Function gets binary array size counting from its end until it reaches 
 * last non-empty byte value. It is different from strlen since all bytes  
 * are a valid values within binary array. Trailing bytes must end with 
 * known pattern.
 */
unsigned long long 
array_nonempty_size_pattern( void *in, unsigned long long size,
							 char trailing_bytes_value)
{
	char *arr_end;
	arr_end = (char*)in + size; //last one byte equals 0x0
	while(((*--arr_end) == trailing_bytes_value) && (arr_end >= in));

	return (arr_end + 1) - (char*)in; //pointer is decremented in a loop
};//array_nonempty_size

/* Function gets binary array size counting from its end until it reaches 
 * last non-empty byte value. It is different from strlen since 0x0 is 
 * a valid value within binary array.
 */
unsigned long long 
array_nonempty_size( void *in, unsigned long long size )
{
	
	return array_nonempty_size_pattern(in, size, 0x0); 
};//array_nonempty_size()

void populate_array( char *in, int size )
{
	srand( (unsigned long long)in );
	for ( int i = 0x0; i < size; i++ )
		in[ i ] = (unsigned char)rand();
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	
	char arr[ ARRSIZE ];
	int arr_size, data_size;
	arr_size = ARRSIZE;
	data_size = 0x0;
	
	memset( arr, 0x0, arr_size );
	populate_array( arr, data_size );
	printf( "array_nonempty_size : 0x%X\n", 
				(unsigned)array_nonempty_size( arr, arr_size ) );
	
	puts( "...done..." );
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
