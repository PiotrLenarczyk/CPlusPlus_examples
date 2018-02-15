#include <iostream>

using namespace std;
typedef uint8_t u8;
typedef uint32_t uint;
size_t i = 0;

struct
{
	u8 someFlag:1;
	u8 someFlag2:1;
	u8 someFlag3:1;
} bitFieldStruct;

int main( void )
{
	bitFieldStruct.someFlag = 1;
	cout << "bitFieldStruct.someFlag: " << ( uint )bitFieldStruct.someFlag << endl;
	cout << "&bitFieldStruct.someFlag: " << &bitFieldStruct << endl;
	
	return 0;
}
