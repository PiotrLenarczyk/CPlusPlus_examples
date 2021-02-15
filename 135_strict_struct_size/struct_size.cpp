#include <cstdio> 
using namespace std;
#define printSize(x)		printf( #x" : 0x%08X\t(%iB)\n", 		\
								sizeof(x), sizeof(x)  );
								

#pragma pack(push, 1)
typedef struct
{
	char c1;
	short s1;
}SomeStruct_TypeDef;
#pragma pop

#pragma pack(push, 2)
typedef struct
{
	char c1;
	short s1;
}TheSameStruct_TypeDef;
#pragma pop

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	printSize( SomeStruct_TypeDef );
	printSize( TheSameStruct_TypeDef );
	
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
