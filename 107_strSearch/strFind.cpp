unsigned char* bytePtr = 0x0;
unsigned long *p = 0x0, s = 0x0, tmp = 0x0;  

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//argv[ 1 ] = data pointer 	as unsigned long string literal
//argv[ 2 ] = pattern 		as unsigned long string literal
//return positive 4B offset from argv[ 1 ] - only 4GiB search scope!
int main( int argc, char* argv[] )
{	if ( sizeof( p ) != 0x8L ) return -1; //64b OS only
	bytePtr = ( unsigned char* )( &argv[ 1 ][ 0 ] ); //pointer
	while( *bytePtr != 0x0 )
		tmp = tmp * 10L + ( *bytePtr++ - 0x30L );
	p = ( unsigned long* )tmp;
	
	bytePtr = ( unsigned char* )( &argv[ 2 ][ 0 ] ); //pattern
	while( *bytePtr != 0x0 )
		s = s * 10L + ( *bytePtr++ - 0x30L );
	
	//while( *p++ != s ); //uncomment for conscious usage
	tmp = ( unsigned long )p - tmp;
	if ( tmp > 0xFFFFFFFFL ) return 0x0; 
	return ( int )tmp;	
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
