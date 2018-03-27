#include <stdio.h>
#include <stdlib.h>
#include <time.h>
long unsigned i, sizeGB = 1, N = sizeGB*1024lu*1024lu*1024lu;
unsigned t, y, x;
const unsigned Y = 8, X = N / Y;
 
int main( void )
{   t = clock();
    //unsigned char* arr = ( unsigned char* )malloc( N );
        //i = 0; while( i < N ) //1GiB array
        //{   arr[ i ] += arr[ i ];
            //i++;
        //};
        //t = clock() - t;
        //if ( t < 500 ) printf( "\tERROR!\n" );
        //else printf( "throughput arr1D: %02f[GBps]; elapsed: %u[periods]\n",  
                     //float( sizeGB ) / ( float( t ) / float( CLOCKS_PER_SEC ) ), t );
    //delete( arr );
    
    //unsigned char** arr2D = ( unsigned char** )malloc( Y * sizeof( unsigned char* ) );
    //i=0;while( i < Y )
    //{   arr2D[ i ] = ( unsigned char* )malloc( X );
		//i++;
	//};
		//t = clock();
        //i = 0; while( i < X ) //1GiB array in a 8B pieces
        //{   arr2D[ 0 ][ i ] += arr2D[ 0 ][ i ];
			//arr2D[ 1 ][ i ] += arr2D[ 1 ][ i ];
			//arr2D[ 2 ][ i ] += arr2D[ 2 ][ i ];
			//arr2D[ 3 ][ i ] += arr2D[ 3 ][ i ];
			//arr2D[ 4 ][ i ] += arr2D[ 4 ][ i ];
			//arr2D[ 5 ][ i ] += arr2D[ 5 ][ i ];
			//arr2D[ 6 ][ i ] += arr2D[ 6 ][ i ];
			//arr2D[ 7 ][ i ] += arr2D[ 7 ][ i ];
            //i += Y;
        //};
        //t = clock() - t;
        //if ( t < 500 ) printf( "\tERROR!\n" );
        //else printf( "throughput arr2D: %02f[GBps]; elapsed: %u[periods]\n",  
                     //float( sizeGB ) / ( float( t ) / float( CLOCKS_PER_SEC ) ), t );
    //i=0;while( i < Y )
    //{   delete( arr2D[ i ] );
		//i++;
	//};
    //delete( arr2D );
   
    return 0;
};//end of main()
