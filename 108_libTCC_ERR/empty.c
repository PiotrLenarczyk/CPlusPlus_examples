//https://stackoverflow.com/questions/10586003/try-catch-statements-in-c
//https://blog.mister-muffin.de/2011/10/22/discovering-tcc/
//#include "tcclib.h"
#include <stdlib.h>
#include <stdio.h>
#include "libtcc.h"
#include <unistd.h>	//sleep
#include <setjmp.h> //try/catch

#define DEF -1

void foo( void )
{	printf( "foo call\n" );
};

//char* my_prog =
	//#include "externProg.c"	//externProg.c : /y7/R"( /*program body here*/ )"
//;

#define PROG_SIZE 0x20000
char cstArr[ PROG_SIZE ];
char* switchPtrs( char* progArr )
{	char* in = progArr;
	char* cstPtr = cstArr;
	while( *in != 0 )
		*cstPtr++ = *in++;
	*cstPtr = 0;
	return cstArr;
}

int previousFileChecksum;
int readFile(char *fileName) 
{   FILE *file = fopen(fileName, "r");
    char *code;
    size_t n = 0;
    int c, currentChecksum = 0x0;

    if (file == NULL) return 0x0; //could not open file
    fseek(file, 0, SEEK_END);
    long f_size = ftell(file);
    fseek(file, 0, SEEK_SET);
    code = malloc(f_size);

    while ((c = fgetc(file)) != EOF)
    {	code[n++] = (char)c;
		currentChecksum += c;
    }

    code[ n ] = '\0';
    switchPtrs( code );
    free( code );
    fclose( file );
	return currentChecksum;
}

void cof( char* fileName );
static jmp_buf s_jumpBuffer;

void Example() { 
  if (setjmp(s_jumpBuffer)) {
    // The longjmp was executed and returned control here
    printf("Exception happened here\n");
  } else {
    // Normal code execution starts here
    Test();
  }
}

void Test() {
  // Rough equivalent of `throw`
  longjmp(s_jumpBuffer, 42);
}

int main(int argc, char **argv)
{	if ( argc == 1 ) return 0;
	
	while( 1 )
	{	
		if ( previousFileChecksum != readFile( argv[ argc - 1 ] ) )
		{	system( "clear" );
			
			cof( cstArr );
			previousFileChecksum = readFile( argv[ argc - 1 ] );
			//sleep( 1 );
			
		};
	};
};

void cof( char* fileName )
{	
    TCCState *s;
    int (*foobar_func)(int);
    void *mem;

    s = tcc_new();
    tcc_set_output_type(s, TCC_OUTPUT_MEMORY);
    tcc_compile_string(s, cstArr);
    tcc_add_symbol(s, "foo", foo);

    mem = malloc(tcc_relocate(s, NULL));
    tcc_relocate(s, mem);

    foobar_func = tcc_get_symbol(s, "foobar");

    tcc_delete(s);

    printf("foobar returned: %d\n", foobar_func(32));

    free(mem);
};
