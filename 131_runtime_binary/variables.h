/*
 * Header for handling binary files variables, or strings. 
 * Makes analyzed variables as pointers to editable structs.
 */
#include <stdio.h>
#include <stdlib.h>
#if !(defined WRITE_MODE) && !(defined READ_MODE)
	error //select mode!
#endif

#define VAR_COUNT_MAX		64
#define NAMEBUFSIZE			0x10
#define USED_VARIABLES_TYPE	unsigned char
#define DATASAVED_SIZE		0x4
typedef struct 
{	//pointer to data; on write mode must be zeroed at save; 
	//	on read mode holds modificator
	unsigned char 	*data;		
	unsigned char 	dataSaved[DATASAVED_SIZE]; 	//4B recommended
	unsigned char 	typeSize;
	unsigned short 	dataSize;
	unsigned int 	offset;
	char 			type[ NAMEBUFSIZE ];
	char 			name[ NAMEBUFSIZE ];
}Variable_TypeDef;

#ifdef READ_MODE //memory - costly, separated from WRITE_MODE
typedef struct
{	USED_VARIABLES_TYPE usedVariables;
	Variable_TypeDef var[ VAR_COUNT_MAX ];
}VariableArr_TypeDef;
VariableArr_TypeDef varArr;
#endif

#ifdef WRITE_MODE //memory - costly, separated from READ_MODE
typedef struct
{	USED_VARIABLES_TYPE usedVariables;
	char varName[ VAR_COUNT_MAX ][ NAMEBUFSIZE ];
	Variable_TypeDef *varPtr[ VAR_COUNT_MAX ];
}VariablesNameArr_TypeDef;
VariablesNameArr_TypeDef varNameArr;
#endif

#define concat(a,b)				a ## b
#define concat3(a,b,c)			a ## b ## c
#define concat4(a,b,c,d)		a ## b ## c ## d
#define concat5(a,b,c,d,e)		a ## b ## c ## d ## e
#define xStr(xs)				str(xs)
#define str(s)					#s
#define prints( s )		printf( "%s : \"%s\"\n", #s, s );
#define printi( i )		printf( "%s : 0x%08X\n", #i, i );
#define CP( a_ptr, b_ptr )		{ char *aPtr, *bPtr; 				\
	aPtr=(char*)a_ptr; bPtr=(char*)b_ptr; 							\
	while( *bPtr )*aPtr++ = *bPtr++; };
#define CP_NULL( a_ptr, b_ptr )	{ char *aPtr, *bPtr; 				\
	aPtr=(char*)a_ptr; bPtr=(char*)b_ptr;							\
	while( *bPtr ){*aPtr++ = *bPtr++;} *aPtr = 0x0;};
#define APPEND( a_ptr, b_ptr ) 	{ char *aPtr, *bPtr; 				\
	aPtr=(char*)(a_ptr + strlen( a_ptr )); bPtr=(char*)b_ptr;		\
	while( *bPtr ){*aPtr++ = *bPtr++;} *aPtr = 0x0;};

char *cPtr; 
char cPrintArr[ 0x5 ]; //fixed size (copying via int pointer)

//======================================================================
//	STRING HANDLING
//======================================================================
#define make_rawPtr( curr_varType, curr_ptrName, currElems )		\
	unsigned char concat( buf_, curr_ptrName )						\
					[sizeof(curr_varType) * currElems];				\
	for ( int i = 0x0; i < sizeof(curr_varType) * currElems; i++ )	\
		concat( buf_, curr_ptrName )[ i ] = 0;						\
	curr_varType *curr_ptrName;										\
	curr_ptrName = (curr_varType*)concat( buf_, curr_ptrName );		\
	Variable_TypeDef concat( var_, curr_ptrName );					\
	cPtr = (unsigned char*)xStr(concat( var_, curr_ptrName ) );		\
	for ( int i = 0x0; i < 											\
		sizeof(xStr(concat( var_, curr_ptrName ))); i++ )			\
		varNameArr.varName[ varNameArr.usedVariables ][ i ] = 		\
			*cPtr++;												\
	varNameArr.varPtr[ varNameArr.usedVariables ] = 				\
		&concat( var_, curr_ptrName );								\
	varNameArr.usedVariables++;										\
	concat( var_, curr_ptrName ).data = 							\
		(unsigned char*) concat( buf_, curr_ptrName );				\
	for( int i=0; i < DATASAVED_SIZE; i++ )							\
		concat( var_, curr_ptrName ).dataSaved[ i ] = 0x0;			\
	concat( var_, curr_ptrName ).typeSize = 						\
		sizeof( curr_varType );										\
	concat( var_, curr_ptrName ).dataSize = 						\
		sizeof( curr_varType ) * currElems;							\
	concat( var_, curr_ptrName ).offset = 0x0;						\
	cPtr = (unsigned char*)str(curr_varType);						\
	for ( int i = 0x0; i < sizeof(str(curr_varType)); i++ )			\
		concat( var_, curr_ptrName ).type[ i ] = *cPtr++;			\
	cPtr = (unsigned char*)str(curr_ptrName);						\
	for ( int i = 0x0; i < sizeof(str(curr_ptrName)); i++ )			\
		concat( var_, curr_ptrName ).name[ i ] = *cPtr++;						
	
#define print_string( curr_varType, curr_ptrName, currElems )		\
	printf( "data[hex 4B] : 0x%08X",								\
		*(int*)concat( var_, curr_ptrName ).data );					\
	*(int*)cPrintArr = *(int*)concat( var_, curr_ptrName ).data;	\
	cPrintArr[ 0x4 ] = 0x0;											\
	printf( "\t(\"%s\")\n", cPrintArr );							\
	printf( "typeSize : %i\n", 										\
		concat( var_, curr_ptrName ).typeSize );					\
	printf( "dataSize : %i\n", 										\
		concat( var_, curr_ptrName ).dataSize );					\
	printf( "offset : %i\n", 										\
		concat( var_, curr_ptrName ).offset );						\
	printf( "type : \"%s\"\n", 										\
		concat( var_, curr_ptrName ).type );						\
	printf( "name : \"%s\"\n\n", 									\
		concat( var_, curr_ptrName ).name );

#define make_variablePtr( curr_varType, curr_ptrName )				\
	make_rawPtr( curr_varType, curr_ptrName, 0x1 );
	
#define print_variable( curr_varType, curr_ptrName )				\
	print_string( curr_varType, curr_ptrName, 0x1 );
	
#define constInit_variable( varType, namePtr, val )					\
	make_variablePtr( varType, namePtr );							\
	*(namePtr) = val;

#define constInit_rawPtr( namePtr, arrPtr_null )					\
	make_rawPtr( unsigned char, namePtr, sizeof(arrPtr_null) - 1 );	\
	CP( namePtr, arrPtr_null );
	
#define init_rawPtr( namePtr, arrPtr_null, size )					\
	make_rawPtr( unsigned char, namePtr, size );					\
	CP( namePtr, arrPtr_null );

//======================================================================
//	BINARY FILE OUTPUT
//======================================================================
#define MODE_SILENT		0x2
#define MODE_VERBOSE	0x4
void print_var( Variable_TypeDef* inArrPtr )
{	printf( "var \"%s\":\n", 					inArrPtr->name );
	printf( "\t.dataPtr : \t0x%08X\n", 			*(char*)&inArrPtr->data );
#ifdef WRITE_MODE
	printf( "\t.data[%i] : \t0x%08X\n", 		inArrPtr->dataSize,
												*(int*)inArrPtr->data );
#endif
	printf( "\t.dataSaved[%i] : 0x%02X", DATASAVED_SIZE, 
		(unsigned)inArrPtr->dataSaved[0] );
	for( int i=1;i<DATASAVED_SIZE;i++ )
	{	printf( "%02X", (unsigned)inArrPtr->dataSaved[i] );
	}; printf( " (\"%s\")\n", inArrPtr->dataSaved );
	printf( "\t.typeSize : \t0x%02X\n", 		inArrPtr->typeSize );
	printf( "\t.dataSize : \t0x%04X\n", 		inArrPtr->dataSize );
	printf( "\t.offset : \t0x%08X\n", 			inArrPtr->offset );
	printf( "\t.type : \t\"%s\"\n", 			inArrPtr->type );
	printf( "\t.name : \t\"%s\"\n", 			inArrPtr->name );
};

#define DEFAULT_VAR_FILENAME	"variables.bin" 
#ifdef WRITE_MODE
void save_list( void )
{	FILE* pFile; 
	if ( varNameArr.usedVariables > VAR_COUNT_MAX )
	{	printf( "Error - to many variables to be saved!\n" );
		while(1);
	};
		
	pFile = fopen( DEFAULT_VAR_FILENAME, "wb" ); 
	fwrite( &varNameArr.usedVariables, sizeof(char), 
			sizeof( USED_VARIABLES_TYPE ), pFile);
	for( int i = 0x0; i < (varNameArr.usedVariables); i++ )
	{	for( int d=0; d < DATASAVED_SIZE; d++ )
			varNameArr.varPtr[ i ]->dataSaved[ d ] = 0x0;
		//byte by byte dataSaved copy
		for( int d=0; (d < varNameArr.varPtr[i]->dataSize) &&
					  (d < DATASAVED_SIZE); d++ )
			*(char*)( varNameArr.varPtr[i]->dataSaved + d ) = 
				*(char*)( varNameArr.varPtr[i]->data + d );
		
		varNameArr.varPtr[ i ]->data = 0x0;
		fwrite( varNameArr.varPtr[ i ], sizeof(char), 
			sizeof( Variable_TypeDef ), pFile );
	};
	fclose( pFile );
};



void print_list( void )
{	for ( int i = 0x0; i < varNameArr.usedVariables; i++ )
		print_var( (Variable_TypeDef *)varNameArr.varPtr[i] );
};
#endif //WRITE_MODE

#ifdef READ_MODE
FILE * pFile;
char* fileBufPtr;
long open_file( char* binaryFilename )
{	int lSize;
	pFile = fopen ( binaryFilename , "rb" );
	if (pFile==NULL) 
	{	printf("File \"%s\" do not exist!\n", binaryFilename); 
		exit(1);
	};
	fseek (pFile , 0 , SEEK_END);
	lSize = ftell (pFile);
	rewind (pFile);
	
	fileBufPtr = (char*)malloc( lSize );
	// copy the input file into the buffer:
	fread (fileBufPtr,1,lSize,pFile);
	
	return lSize;
};

void close_file( void )
{	free( fileBufPtr );
	fclose( pFile );
	pFile = NULL;
};

char* get_file_str_ptr( void )
{	return fileBufPtr;
};

void read_variables( char* varFileName, int mode )
{	int read_variables;
	FILE *varFile;
	char* varBufPtr;
	int lSize;
	
	varFile = fopen ( varFileName , "rb" );
	
	if (varFile==NULL) 
	{	printf("File \"%s\" do not exist!\n", varFileName); 
		exit(1);
	};	
	fseek (varFile , 0 , SEEK_END);
	lSize = ftell (varFile);
	rewind (varFile);
	
	varBufPtr = (char*)malloc( lSize );
	// copy the input file into the buffer:
	fread (varBufPtr,1,lSize,varFile);
	
		read_variables = *(USED_VARIABLES_TYPE*)varBufPtr;
		varArr.usedVariables = read_variables;
		
		switch ( mode )
		{	default:
			case MODE_SILENT:
				break;
			case MODE_VERBOSE:
				printf( "Uploaded %i variables.\n", read_variables );
				printf( "Single variable size : %i[B]\n",
					(int)sizeof( Variable_TypeDef ) );
				break;
		};
		for ( int i = 0x0; i < read_variables; i++ ) 
		{	//size already read, (ptr + 1)
			for ( int b = 0x0; b < sizeof(Variable_TypeDef); b++ )
				*((char*)(&varArr.var[i]) + b ) = *(char*)
					(varBufPtr + 1 + b + 
						(i * sizeof( Variable_TypeDef )));
			switch ( mode )
			{	default:
				case MODE_SILENT:
					break;
				case MODE_VERBOSE:
					print_var( &varArr.var[ i ] );
					break;
			};
		};
		
		
	free( varBufPtr );
	fclose( varFile );
};
#endif //READ_MODE

//======================================================================
//	FIND VARIABLES IN INPUT BINARY FILE
//======================================================================
#ifdef READ_MODE

#define NOT_FOUND		-1 
#define FIND_RESULTS_NO	0x8
#define FILESIZE_UNINITIALIZED 0
//search file for any value, any length string pattern
int file_size = FILESIZE_UNINITIALIZED;
//could include 0x0 searched byte value
int file_strstr_offset( char *patternPtr, int str_size, int offset ) 
{	char *file_strPtr, *strPtr;
	file_strPtr = get_file_str_ptr() + offset;
	strPtr = patternPtr;
	
	if 	( str_size == sizeof(int) )	
		goto find_via_4B;	//register size
	else					
		goto find_via_1B;
//====
find_via_4B:
	//find directly register size pattern 
	while(  (++offset < file_size) &&
			(*(int*)(file_strPtr++) != *(int*)strPtr) ); 	
	if ( offset < file_size )
		offset--; 						//correct offset word increment
	goto find_return;

//====
find_via_1B:
	//if ( str_size < sizeof(int) )
	{	
	partial_match_continue_1B:
		while(  (++offset < file_size) &&
				(*file_strPtr++ != *strPtr) ); 	//find first byte
		if ( offset >= file_size )				//no matches
			goto find_return;
		strPtr++;								//first byte found
				
		for ( int i=1; (i < str_size) && (offset++ < file_size); i++ )
		{	if ( *file_strPtr++ == *strPtr++ )
			{	continue;					//going through full match
			}else    //reset searched pattern ptr as pattern begginning
			{	strPtr = patternPtr; 			
				goto partial_match_continue_1B;	
			};
		};
		offset -= str_size;
		goto find_return;
	};
	
//====
find_return:
	if (offset < file_size )
		return offset; //return begginning pattern offset
	else
		return NOT_FOUND;
};

int file_strstr( char *strPtr, int pattern_size )
{	return file_strstr_offset( strPtr, pattern_size, 0x0 );
};

int file_strstr_results_array( char* strPtr, int patternSize, 
								int *results, int max_no_results )
{	int i;
	for ( i = 0x0; i < max_no_results; i++ ) results[ i ] = NOT_FOUND;

	results[ i=0 ] = file_strstr( strPtr, patternSize );
	if ( results[ 0 ] == NOT_FOUND )
		return i;
	for ( i = 0x1; i < max_no_results; i++ )
	{	results[ i ] = file_strstr_offset( strPtr, patternSize, 
										results[i - 1] + patternSize );
		if ( results[ i ] != NOT_FOUND )
			continue;
		else 
			return i;
	};
};

int find_variables( int mode ) 
{	char *pattern, c;
	int patternSize;
	int found[ FIND_RESULTS_NO ]; 
	int matches;
	for ( int v = 0x0; v < varArr.usedVariables; v++ )
	{	pattern  = (char*)&varArr.var[ v ].dataSaved;
		patternSize = varArr.var[ v ].dataSize;
		memset( found, -1, sizeof(found) );
		matches = file_strstr_results_array( pattern, patternSize, 
											found, FIND_RESULTS_NO );
		switch( mode )
		{	default:
			case MODE_SILENT:
				break;
			case MODE_VERBOSE:
				if ( matches > 0x1 ) c='s';
				printf( "pattern 0x%X (\"%s\") .size %i[B]"
							" found %i time%c:\n", *(int*)pattern, 
							pattern, patternSize, matches, c );
				for ( int i = 0x0; i < FIND_RESULTS_NO; i++ )
				{	if(found[i] == NOT_FOUND) break;
					printf( "offset[%i] : 0x%02X\n", i, found[ i ] );
				};
				break;
		};
		//only first found offset it saved into variable struct
		if (matches >= 0x1)
			varArr.var[ v ].offset = found[ 0 ];
	};
	return matches;
};
#endif //READ_MODE
