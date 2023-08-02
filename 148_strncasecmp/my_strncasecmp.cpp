#include <cstdio> 
#include <cstring>
#include <cstdlib>


int my_strncasecmp( const char *in1, const char *in2, size_t size )
{
	int st = -1;
	char *s1 = (char*)malloc(size);
	char *s2 = (char*)malloc(size);
		strncpy(s1, in1, size);
		strncpy(s2, in2, size);
		for( int i=0; i<size; i++ )
		{
			if( (s1[i] > 0x40) && (s1[i] < 0x5B) )
				s1[i] += 0x20;
			if( (s2[i] > 0x40) && (s2[i] < 0x5B) )
				s2[i] += 0x20;
		};
		st = strncmp( s1, s2, size );
	free(s1);
	free(s2);
	return st;
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	
	char a[] = "ABc";
	char b[] = "abc";
	int size = strlen(a);
	int st = my_strncasecmp( a, b, size );
	printf( "strncasecmp(\"%s\", \"%s\", %i) : 0x%X\n", a, b, size, strncasecmp(a,b,size) );
	printf( "my_strncasecmp(\"%s\", \"%s\", %i) : 0x%X\n", a, b, size, st );
	
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
