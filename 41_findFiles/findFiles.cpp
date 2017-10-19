/*
https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
*/
//STL
#include <iostream>
#include <string>
#include "dirent.h"

using namespace std;

void getFilenames( char* dirPath )
{
    DIR *dir;
    struct dirent *ent;
    string fileName;
    if ( ( dir = opendir ( dirPath ) ) != NULL )
    {
        while ( ( ent = readdir ( dir ) ) != NULL ) /* print all the files and directories within directory */
        {
            fileName = ent->d_name;
            if ( fileName.size() > 2 )
                printf ( "%s\n", fileName.c_str() );
        }
        closedir( dir );
    } 
    else 
        perror ( "ERROR: Could not open directory!" );/* could not open directory */
}

int main( void )
{
    getFilenames( "/home" );

    
    return 0;
}
