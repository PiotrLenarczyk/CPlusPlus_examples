#include <stdio.h>
#include <string.h>
#define WRITE_MODE
#include "variables.h"


int main( void )
{   
	constInit_variable( int, global_iPtr, 0x44332211 );
	constInit_rawPtr( funcNamePtr, "foo" );
	

	//print_list();  
	save_list();
	 
	return 0;
};

