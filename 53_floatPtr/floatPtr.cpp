#include <iostream>
#include <typeinfo> 

using namespace std;
typedef unsigned uint;

size_t i = 0;
const uint N = 1000000;
void functionNewDeleteHandler();

int main( void )
{
	functionNewDeleteHandler();
	
	return 0;
}

void functionNewDeleteHandler()
{
	float *f32Ptr;
	*f32Ptr = 0.0f;
	printf( "float pointer = %f\n", *f32Ptr );
	
	float f32Arr[ N ];
	for ( auto& x : f32Arr )
		x = 1.0f;
	printf( "float array [ N - 1 ] = %f\n", f32Arr[ N - 1 ] );
}
