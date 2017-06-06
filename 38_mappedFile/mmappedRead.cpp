/* https://techoverflow.net/2013/08/21/a-simple-mmap-readonly-example/ */
#include <sys/mman.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/stat.h>
#include <assert.h>
#include <iostream>
#include <string>

using namespace std;

size_t getFilesize( const char* filename ) 
{
    struct stat st;
    stat( filename, &st );
    return st.st_size;
}

int main( int argc, char** argv ) 
{
    size_t filesize = getFilesize( argv[ 1 ] );
    //Open file
    int fd = open( argv[ 1 ], O_RDONLY, 0 );
    assert( fd != -1 );
    //Execute mmap
    void* mmappedData = mmap( NULL, filesize, PROT_READ, MAP_PRIVATE | MAP_POPULATE, fd, 0 );
    assert( mmappedData != MAP_FAILED );
    //Write the mmapped data to stdout (= FD #1)
//     write( 1, mmappedData, filesize );
    unsigned char *mmapPtr = ( unsigned char* )mmappedData;
    unsigned char mmapByte = mmapPtr[ 0 ];
    cout << "mmapSize: " << sizeof( mmappedData ) - 1 << endl; //file EOL
    for ( unsigned i = 0; i < sizeof( mmappedData ) - 1; i++  )
        cout << "mmap[ " << i << " ]: " << *( ( unsigned char* )mmappedData + i ) << endl;
    //Cleanup
    int rc = munmap( mmappedData, filesize );
    assert( rc == 0 );
    close( fd );
    
    return 0;
}
