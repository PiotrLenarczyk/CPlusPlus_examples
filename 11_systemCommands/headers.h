//STL
#include <iostream>
#include <stdlib.h> //system
#include <stdio.h>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

struct Procs
{
    int procsTH;
    Procs( int uC ) :procsTH( uC ) { }
};

bool fileExists(const char *filename)
{
    ifstream ifile(filename);
    if ( ifile )
        return true;
    else 
        return false;
}
