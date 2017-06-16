/*
https://stackoverflow.com/questions/612097/how-can-i-get-the-list-of-files-in-a-directory-using-c-or-c
*/
//STL
#include <iostream>
#include "dirent.h"

using namespace std;

int main( void )
{
    DIR *dir;
    struct dirent *ent;
    if ( ( dir = opendir ( "/home" ) ) != NULL ) 
    {
        /* print all the files and directories within directory */
        while ( ( ent = readdir ( dir ) ) != NULL ) 
        {
            printf ( "%s\n", ent->d_name );
        }
        closedir( dir );
    } 
    else 
    {
        /* could not open directory */
        perror ( "" );
        return EXIT_FAILURE;
    }
    
    return 0;
}
