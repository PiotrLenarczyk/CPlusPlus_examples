/*
	https://docs.opencv.org/master/db/df5/tutorial_linux_gcc_cmake.html
 */ 
#include <stdio.h>
#include <string.h>
#include <opencv2/opencv.hpp>
typedef uint32_t uint;
typedef unsigned char byte;
using namespace std;
using namespace cv;

uint N;

int main( int argc, char* argv[] )
{    if ( argc != 2 )
    {   printf("usage: DisplayImage.out <Image_Path>\n");
        return -1;
    };
    Mat image;
    image = imread( argv[ 1 ], 1 );
    if ( !image.data )
    {   printf( "No image data \n" );
        return -1;
    };
//	show loaded image
    //namedWindow( "Display Image", WINDOW_AUTOSIZE );
    //imshow( "Display Image", image );
    //waitKey( 0 );
    
    printf( "Mat.isContinuous() : %i", image.isContinuous() );
    if ( image.isContinuous() != 1 )
		return 0;
	N = image.total() * image.elemSize();
	printf( "image.size: %i[B]\n", N );
	printf( "image %i[rows] * %i[cols] * %i[layers]\n", image.rows, image.cols, N / ( image.rows * image.cols ) );
	

    
    byte* byteImage = ( byte* )malloc( N );
		memcpy( byteImage, image.data, N );
//some stuff ...
	image.release();	//free Mat image
    delete( byteImage );	//free byteImage

    return 0;
}
