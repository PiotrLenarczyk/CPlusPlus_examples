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
        while ( ( ent = readdir ( dir ) ) != NULL ) /* print all the files and directories within directory */
        {
            printf ( "%s\n", ent->d_name );
        }
        closedir( dir );
    } 
    else 
    {
        perror ( "" );/* could not open directory */
        return EXIT_FAILURE;
    }
    
    return 0;
}
