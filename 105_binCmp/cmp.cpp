unsigned char* inA = 0;
unsigned char* inB = 0;
int main( int argc, char* argv[] )
{	inA = ( unsigned char* )&argv[ 1 ][ 0 ];
	inB = ( unsigned char* )&argv[ 2 ][ 0 ];
	while( *++inA != *++inB )
		;
	if ( *inA == '\0' ) return 0; //array end
	--inA;--inB;
	if ( *inA < *inB ) return -1;
	if ( *inA > *inB ) return 2;
	return 0;
};
