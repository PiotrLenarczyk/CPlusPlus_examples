//https://pastebin.com/n4yDjBde
//most capable are function pointers: void *(func*)(void*);
#include <cstdio> 
#include <cstdint>
#include <cstring>

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
void foo( void )
{	printf( "void (foo)(void)\n" );
};

int bar( int in )
{	printf( "int (bar)(int in = %i)\n", in );
	return ++in;
};

float baz( int i, float f )
{	printf( "float (baz)(int i = %i, float f = %f):\n", i, (double)f );
	f += 1.0f;
	return f;
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
enum: int{ FUNCS_NO = 0x3, FUNC_INPUT_BASE = 0x10 };
//one input function types, zero/one return
enum: int{ ONE_FUNC_INPUT_BASE = 0x10, foo_t, bar_t };	
//two input function types, zero/one return
enum: int{ TWO_FUNC_INPUT_BASE = 0x20, baz_t }; 			

template <class Dest, class Source>
inline Dest bit_cast(Source const &source) 
{   Dest dest;
    std::memcpy(&dest, &source, sizeof(dest));
    return dest;
};

//one input, any argument functions
#define func( fptr, fargs ) 									\
			_func( (void*)(intptr_t)&fptr, (void*)fargs )
void* _func( void *fptr, void *fargs ) 
{	int func_type = 
		((fptr == (void*)(intptr_t)&foo) * foo_t) + 
		((fptr == (void*)(intptr_t)&bar) * bar_t);
	switch( func_type )
	{	default:
			break;
		case foo_t:
			(*foo)();
			break;
		case bar_t:
			return (void*)(unsigned long long)
					(*bar)( (int)(intptr_t)fargs );
			break;
	};
};

//two input, any argument functions
#define func2( fptr, fargs1, fargs2 ) 								\
			_func2(  (void*)(intptr_t)&fptr, 						\
					bit_cast<void*>(fargs1), 						\
					bit_cast<void*>(fargs2) )
void* _func2( void *fptr, void *fargs1, void *fargs2 )
{	int func_type = 
		((fptr == (void*)(intptr_t)&baz) * baz_t);
	switch( func_type )
	{	default: 
			break;
		case baz_t:
			float f = (*baz)( (int)(intptr_t)fargs1, 
							bit_cast<float>(fargs2 ) );
			return bit_cast<void*>(f );
			break;
	};
};

void get_func_ptr( char* name, void *ptr, int *inputs )
{	int namesize = strlen( name );
	int func_type = 
		((strcmp( name, "foo" ) == 0) * foo_t) + 
		((strcmp( name, "bar" ) == 0) * bar_t) + 
		((strcmp( name, "baz" ) == 0) * baz_t);
printf( "func_type : %i\n", func_type );
	*inputs = func_type / FUNC_INPUT_BASE;
	switch( func_type )
	{	default:
			break;
		case foo_t:
			*(unsigned long long*)ptr = 
				(unsigned long long)(intptr_t)&foo;
			break;
		case bar_t:
			*(unsigned long long*)ptr = 
				(unsigned long long)(intptr_t)&bar;
			break;
		case baz_t:
			*(unsigned long long*)ptr = 
				(unsigned long long)(intptr_t)&baz;
			break;
	};
};

//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
int main( void )
{	func( foo, 0 );
	func( bar, 19 );
	func2( baz,	19,	1.11f );
	
	//some obvious printing
	puts( "====" );
	printf( "\tbar() returned : %i\n", 
				(int)(intptr_t)func( bar, 19 ) );
	printf( "\tbaz() returned : %f\n", 
				(double)bit_cast<float>(func2( 		
						baz,
						19,
						1.11f )));
	
	//name-based func call
	puts( "====" );
	unsigned long long ptr;
	int inputs_capable;
	get_func_ptr( (char*)"baz", &ptr, &inputs_capable );
	printf( "&baz(inputs = %i) : 0x%08llX\n", inputs_capable, ptr );
	printf( "&baz : 0x%08llX\n", (unsigned long long)&baz );
	return 0;
};//end of main()
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
