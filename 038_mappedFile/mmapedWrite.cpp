#include <sys/mman.h>
#include <sys/stat.h>
#include <stdlib.h>
#include <iostream>
#include <string>
#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

#define FILE_SIZE 256 //BYTES

using namespace std;

int main( int argc, char *argv[] )
{
    int fileDescriptor;
    void *fileMemory;
    srand( 15 );
    
    if ( argc < 2 ) { cerr << "ERROR: Lack of filename\n"; return -1; }
    fileDescriptor = open( argv[ 1 ], O_RDWR | O_CREAT, S_IRUSR | S_IWUSR );
    lseek( fileDescriptor, FILE_SIZE + 1, SEEK_SET );
    write( fileDescriptor, "", 1 );
    lseek( fileDescriptor, 0, SEEK_SET );
    //memory to file mapping
    fileMemory = mmap( 0, FILE_SIZE, PROT_WRITE, MAP_SHARED, fileDescriptor, 0 );
    close( fileDescriptor );
    
    string buffer = { "12345" };
    sprintf( ( char* )fileMemory, "%f\n", float(0.156f) ); //length o formatted float: 8chars + EOL
    sprintf( ( char* )fileMemory + 7 + 2, buffer.c_str(), buffer.size() ); 
    sprintf( ( char* )fileMemory + 7 + 2 + buffer.size(), "\n" ); //file EOL

    munmap( fileMemory, FILE_SIZE );
    
    return 0;
}
