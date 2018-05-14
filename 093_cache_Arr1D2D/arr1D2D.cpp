#include <stdio.h>
#include <stdlib.h>
#include <time.h>
typedef long unsigned uint64;
long unsigned i, sizeGB = 1, N = sizeGB*1024lu*1024lu*1024lu;
unsigned t, y, x;
const unsigned Y = 8, X = N / Y;
const unsigned X2 = 8, Y2 = N / Y;

int main( void )
{   
////	X = N; it is size-optimal
    //unsigned char* arr = ( unsigned char* )malloc( N ); 
		//t = clock();
        //i = 0; while( i < N ) //1GiB array
        //{   arr[ i ] += arr[ i ];
            //i++;
        //};
        //t = clock() - t;
        //if ( t < 500 ) printf( "\tERROR!\n" );
        //else printf( "throughput arr1D: %02f[GBps]; elapsed: %u[periods]\n",  
                     //float( sizeGB ) / ( float( t ) / float( CLOCKS_PER_SEC ) ), t );
    //delete( arr );
    
////	64b memory accesses
    //unsigned char* arr = ( unsigned char* )malloc( N ); 
    //uint64 dummy64;
		//t = clock();
        //i = 0; while( i < N ) //1GiB array
        //{   dummy64 = *( uint64* )&arr[ i ];
			//dummy64 += dummy64;
			//*( uint64* )&arr[ i ] = dummy64;
            //i += 8;
        //};
        //t = clock() - t;
        //if ( t < 500 ) printf( "\tERROR!\n" );
        //else printf( "throughput arr1D: %02f[GBps]; elapsed: %u[periods]\n",  
                     //float( sizeGB ) / ( float( t ) / float( CLOCKS_PER_SEC ) ), t );
    //delete( arr );
   
//////	YX access; Y = 8; it is size less optimal, but better use of cache
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
        //else printf( "throughput arr2D YX: %02f[GBps]; elapsed: %u[periods]\n",  
                     //float( sizeGB ) / ( float( t ) / float( CLOCKS_PER_SEC ) ), t );
    //i=0;while( i < Y )
    //{   delete( arr2D[ i ] );
		//i++;
	//};
    //delete( arr2D );
    
////	XY access; X2 = 8; //it is not used RAM size optimal - worse information density, than YX access
    //unsigned char** arr2DXY = ( unsigned char** )malloc( Y2 * sizeof( unsigned char* ) );
    //i=0;while( i < Y2 )
    //{   arr2DXY[ i ] = ( unsigned char* )malloc( X2 );
		//i++;
	//};
		//t = clock();
        //i = 0; while( i < Y2 ) //1GiB array in a 8B pieces
        //{   arr2DXY[ i ][ 0 ] += arr2DXY[ i ][ 0 ];
			//arr2DXY[ i ][ 1 ] += arr2DXY[ i ][ 1 ];
			//arr2DXY[ i ][ 2 ] += arr2DXY[ i ][ 2 ];
			//arr2DXY[ i ][ 3 ] += arr2DXY[ i ][ 3 ];
			//arr2DXY[ i ][ 4 ] += arr2DXY[ i ][ 4 ];
			//arr2DXY[ i ][ 5 ] += arr2DXY[ i ][ 5 ];
			//arr2DXY[ i ][ 6 ] += arr2DXY[ i ][ 6 ];
			//arr2DXY[ i ][ 7 ] += arr2DXY[ i ][ 7 ];
            //i += X2;
        //};
        //t = clock() - t;
        //if ( t < 500 ) printf( "\tERROR!\n" );
        //else printf( "throughput arr2D XY: %02f[GBps]; elapsed: %u[periods]\n",  
                     //float( sizeGB ) / ( float( t ) / float( CLOCKS_PER_SEC ) ), t );
    //i=0;while( i < Y2 )
    //{   delete( arr2DXY[ i ] );
		//i++;
	//};
    //delete( arr2DXY );
    
    return 0;
};//end of main()
