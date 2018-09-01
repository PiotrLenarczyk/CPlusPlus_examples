#include "tcclib.h"
#include <stdlib.h>
#include "libtcc.h"

#define DEF -1

void foo( void )
{	printf( "foo call\n" );
};

char* my_program =
	#include "externProg.c"
;

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

int main(int argc, char **argv)
{
    TCCState *s;
    int (*foobar_func)(int);
    void *mem;

    s = tcc_new();
    tcc_set_output_type(s, TCC_OUTPUT_MEMORY);
    tcc_compile_string(s, switchPtrs( my_program ));
    tcc_add_symbol(s, "foo", foo);

    mem = malloc(tcc_relocate(s, NULL));
    tcc_relocate(s, mem);

    foobar_func = tcc_get_symbol(s, "foobar");

    tcc_delete(s);

    printf("foobar returned: %d\n", foobar_func(32));

    free(mem);
    
	printf( "DEF : %i\n", DEF );
    return 0;
}
